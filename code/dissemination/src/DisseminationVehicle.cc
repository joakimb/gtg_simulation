//
// Copyright (C) 2006-2011 Christoph Sommer <christoph.sommer@uibk.ac.at>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "DisseminationVehicle.h"
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>

using std::vector;

Define_Module(DisseminationVehicle);

void DisseminationVehicle::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        currentSubscribedServiceId = -1;
    }
    sendSharesSignal = registerSignal("sendshares");

    cutOff = par("cutOff").intValue();
    neighbours.reset(new NeighbourMemory(cutOff));
}

void DisseminationVehicle::onWSA(WaveServiceAdvertisment* wsa) {
    std::cout << "receiveWSA at " << getFullName() << endl;
}

void DisseminationVehicle::onWSM(WaveShortMessage* wsm) {
    std::cout << "receiveWSM at " << getFullName() << endl;
}


void DisseminationVehicle::onBSM(BasicSafetyMessage* bsm){
    int me = getId() - 1;
    int sender = bsm->getSenderAddress();
    assert(neighbours);
    neighbours->newNeighbour(sender, simTime());
    vector<int> current_neighbours = neighbours->getNeighbours();

    std::stringstream result;
    std::copy(current_neighbours.begin(), current_neighbours.end(), std::ostream_iterator<int>(result, " : "));

    //std::cout << "I am: " << me << " and I know: " << result.str() <<endl;
}

void DisseminationVehicle::handleSelfMsg(cMessage* msg) {

        BaseWaveApplLayer::handleSelfMsg(msg);

}

void DisseminationVehicle::sendShares(){
    std::cout << "sendWSM at " << getFullName() << endl;

    WaveShortMessage* wsm = new WaveShortMessage();
    populateWSM(wsm);
    std::string msg = std::string("I am: ") + getFullName();
    const char* mc = msg.c_str();
    wsm->setWsmData(mc);
    sendDown(wsm);
}

void DisseminationVehicle::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);

    //send shares if needed
    simtime_t currentEpoch = simTime() / PSEUD_PERIOD;
    //have we disseminated shares for this epoch?
    if (currentEpoch > sentForEpoch) {

        //sendShares();

    }

    //record statistics
    assert(neighbours);
    neighbours->deleteExpired(simTime());
    emit(sendSharesSignal, neighbours->getNeighbours().size());

}
