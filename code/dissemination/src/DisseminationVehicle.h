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

#ifndef DisseminationVehicle_H
#define DisseminationVehicle_H

#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "NeighbourMemory.h"

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
		void sendShares();
		simtime_t sentForEpoch = -1;
		const int PSEUD_PERIOD = 10;
        NeighbourMemory neighbours{3};
        simsignal_t sendSharesSignal;
};

#endif
