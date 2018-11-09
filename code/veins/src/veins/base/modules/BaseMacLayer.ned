package org.car2x.veins.base.modules;

// Base module for every mac layer module
simple BaseMacLayer extends BaseLayer like IWirelessMac
{
    parameters:
        @class(BaseMacLayer);
        bool   coreDebug = default(false);          // debug switch
        
        // patched according to (https://github.com/sommer/veins/commit/493f8a3f514bd8ffd7fb5d9666a952a4446ab177 and https://stackoverflow.com/questions/49967052/error-while-running-example-of-the-veins-in-the-last-step-of-the-installation?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa)
        //double headerLength @unit(bit);           // length of the MAC packet header (in bits)
        int headerLength @unit(bit);           // length of the MAC packet header (in bits)
        
        string address = default("auto");         // MAC address as hex string (12 hex digits), or
                                                  // "auto". "auto" values will be replaced by
                                                  // a generated MAC address in init stage 1.
}
