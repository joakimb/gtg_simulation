
#include <CircleAppl.h>
#include <stdlib.h>

using Veins::TraCIMobilityAccess;
using Veins::AnnotationManagerAccess;

Define_Module(CircleAppl);

void CircleAppl::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        //setup veins pointers
        mobility = TraCIMobilityAccess().get(getParentModule());
        traci = mobility->getCommandInterface();
        traciVehicle = mobility->getVehicleCommandInterface();
        lastSent = simTime();
    }
}

void CircleAppl::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) {
    Enter_Method_Silent();
    if (signalID == mobilityStateChangedSignal) {
        handlePositionUpdate(obj);
    }
}

void CircleAppl::onData(WaveShortMessage* wsm) {
    //Receive a message with a target speed, slow down to that speed
    float message_speed = atof(wsm->getWsmData());
    traciVehicle->slowDown(message_speed, 1000); //slow down over 1s
}

void CircleAppl::onBeacon(WaveShortMessage* wsm) {
}

void CircleAppl::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);

    //sends message every 0.1 seconds
    if (simTime() - lastSent >= 0.1) {
        std::string message = std::to_string(mobility->getSpeed());
        sendMessage(message);
        lastSent = simTime();
    }
}

void CircleAppl::sendWSM(WaveShortMessage* wsm) {
    sendDelayedDown(wsm, 1000); //message delay
}

void CircleAppl::sendMessage(std::string msg) {
    EV_TRACE << "sending CAM: " << msg << endl;
    t_channel channel = dataOnSch ? type_SCH : type_CCH;
    WaveShortMessage *wsm = new WaveShortMessage("data", channel);
    wsm->setWsmData(msg.c_str());
    sendWSM(wsm);
}
