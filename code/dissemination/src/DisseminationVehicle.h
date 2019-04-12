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
#include "Crypto.h"
#include "GTGMessage.h"

#define BEACON_SELF_MSG 1000
#define SEND_SHARES_SELF_MSG 1001
#define STATISTICS_MSG 1002

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
        void sendShares();
        void recStats();
        void sendShare(std::vector<unsigned char> signedShare, std::vector<unsigned char> pubKey);
        void sendGTGMessage(GTGMessage& msg);
	    std::vector<uint8_t> intToArr(int i);
	    void decodeBeacon(std::string b64Data);

	private:
		simtime_t sentForEpoch = -1;
		simtime_t pseudPeriod;
        std::unique_ptr<NeighbourMemory> neighbours;
        simsignal_t numNeighboursSignal;
        simtime_t cutOff;
        int numShares;
        int numReconstruct;
        std::unique_ptr<Token> disseminating;
        std::queue<Token> disseminated;
        simtime_t beaconOffset;
        simtime_t shareSendInterval;
        simtime_t statRecInterval;
        cMessage* beaconMsg;
        cMessage* shareMsg;
        cMessage* statMsg;
        bool sendGTGBeacons;
        bool sendGTGShares;
};

