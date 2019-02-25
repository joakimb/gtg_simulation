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

#pragma once

#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "NeighbourMemory.h"
#include <queue>
#include <vector>
#include "Token.h"
#include "PseudCred.h"

#define BEACON_SELF_MSG 1000


class DisseminationVehicle : public BaseWaveApplLayer {
	public:
		virtual void initialize(int stage);

	protected:
		int currentSubscribedServiceId;

	protected:
        virtual void onWSM(WaveShortMessage* wsm);
        virtual void onWSA(WaveServiceAdvertisment* wsa);
        virtual void onBSM(BasicSafetyMessage* bsm);
        virtual void handleSelfMsg(cMessage* msg);
		virtual void handlePositionUpdate(cObject* obj);

	private:
		void sendBeacon();
	    std::vector<uint8_t> intToArr(int i);
	    std::vector<unsigned char> decodeBeacon(std::string b64Data);



	private:
		simtime_t sentForEpoch = -1;
		simtime_t pseudPeriod;
        std::unique_ptr<NeighbourMemory> neighbours;
        simsignal_t sendSharesSignal;
        simtime_t cutOff;
        int numShares;
        int numReconstruct;
        std::unique_ptr<Token> disseminating;
        std::queue<Token> disseminated;
        simtime_t beaconOffset;
        cMessage* beaconMsg;
};

