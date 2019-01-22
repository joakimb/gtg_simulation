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
#include <nlohmann/json.hpp>
#include "base64.h"
using json = nlohmann::json;
using std::vector;

Define_Module(DisseminationVehicle);

void DisseminationVehicle::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        currentSubscribedServiceId = -1;

        sendSharesSignal = registerSignal("sendshares");

        //read config file values
        numShares = par("numShares").intValue();
        numReconstruct = par("numReconstruct").intValue();
        pseudPeriod = par("pseudPeriod").intValue();
        cutOff = par("cutOff").intValue();

        //initialize neighbour memory
        neighbours.reset(new NeighbourMemory(cutOff));

        //initialize token in progress for dissemination
        const std::vector<uint8_t> ltid = intToArr(getId() - 1);
        disseminating.reset(new Token(ltid, numShares, numReconstruct));

        //init pseudonyms
        for (int i = 0; i < 1000; i++){
            pseudonyms.push(PseudCred());
        }

        //schedule beaconing
        beaconMsg = new cMessage("beaconmsg", BEACON_SELF_MSG);
        beaconOffset = dblrand() * par("pubKeyBeaconInterval").doubleValue() ;
        scheduleAt(simTime() + beaconOffset, beaconMsg);
    }
}

void DisseminationVehicle::onWSA(WaveServiceAdvertisment* wsa) {
    std::cout << "receiveWSA at " << getFullName() << endl;
}

void DisseminationVehicle::onWSM(WaveShortMessage* wsm) {
    std::cout << "receiveWSM at " << getFullName() << endl;
}

void DisseminationVehicle::onBSM(BasicSafetyMessage* bsm){


    assert(neighbours);
    const char* b64Data = bsm->getWsmData();
    std::string b64String = std::string(b64Data);
    //std::cout << "incoming: " << b64String << endl;
    std::string cborData = base64_decode(b64String);



    try {
        json json = json::from_cbor(cborData);

        std::vector<unsigned char> pseudVect = json["gtg_pseud"];

        neighbours->newNeighbour(pseudVect, simTime());
        vector<std::vector<unsigned char>> currentNeighbours = neighbours->getNeighbours();

        //std::cout << "I am: " << base64_encode(pseudonyms.front().getPubKey().data(),pseudonyms.front().getPubKey().size()) << endl;
        //std::cout << " and I know: " << endl;
        for (auto it = begin (currentNeighbours); it != end (currentNeighbours); ++it) {
            std::vector<unsigned char> v = (*it);
            //std::cout << base64_encode(v.data(), v.size()) << endl;
        }


    } catch (const json::parse_error& e){

        //todo, do we accidentally ignore good messages here? there are messages coming in

        std::cout << "exception: " << e.what() << endl;
    }
 }

std::vector<uint8_t> DisseminationVehicle::intToArr(int in) {
    uint8_t hexBuffer[4]={0};

    memcpy((uint8_t*)hexBuffer,(uint8_t*)&in,sizeof(int));
    std::vector<uint8_t> out{};
    for (int i = sizeof(int) - 1; i >= 0; i--){
        out.push_back(hexBuffer[i]);
    }
    return out;
}

void DisseminationVehicle::handleSelfMsg(cMessage* msg) {


        switch (msg->getKind()) {
               case BEACON_SELF_MSG: {
                   sendBeacon();
                   scheduleAt(simTime() + beaconOffset, beaconMsg);
                   break;
               }
               default: {
                    BaseWaveApplLayer::handleSelfMsg(msg);
                    break;
               }
        }
}

void DisseminationVehicle::sendBeacon(){

    std::vector<unsigned char> pseud = pseudonyms.front().getPubKey();

    //std::cout << "pseu: " << base64_encode(pseud.data(), pseud.size()) << " is sending a beacon" << endl;

    BasicSafetyMessage* wsm = new BasicSafetyMessage();
    populateWSM(wsm);

    json cborStruct;
    cborStruct["gtg_pseud"] = pseud;
    std::vector<std::uint8_t> cborMsg = json::to_cbor(cborStruct);
    const unsigned char* cborMsgChar = reinterpret_cast<const unsigned char*>(cborMsg.data());//.c_str();
    std::string b64 = base64_encode(cborMsgChar, cborMsg.size());

    wsm->setWsmData(b64.c_str());
    sendDown(wsm);
}

void DisseminationVehicle::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);

    //send shares if needed
    //simtime_t currentEpoch = simTime() / pseudPeriod;
    //have we disseminated shares for this epoch?
    //if (currentEpoch > sentForEpoch) {
        //sendShares();
    //}
//    Token token{Token::genRandomPseud(), 5,4};
//    for (int i = 0; i < 5; i++){
//        std::cout << "share: " << token.getNextShare().data() << "\n";
//    }

    //record statistics
    assert(neighbours);
    neighbours->deleteExpired(simTime());
    emit(sendSharesSignal, neighbours->getNeighbours().size());

}


