/*
 * ShareMessage.cc
 *
 *  Created on: Feb 28, 2019
 *      Author: root
 */

#include "ShareMessage.h"

ShareMessage::ShareMessage(std::vector<unsigned char> _pubKey, std::vector<unsigned char> _signedData) {
    type = "GTG_SHARE",
    pubKey = _pubKey,
    signedData = _signedData;
}


std::string ShareMessage::getEncoded(){

    json cborStruct;
    cborStruct["gtg_type"] = type;
    cborStruct["gtg_share"] = {{"key",pubKey},{"data",signedData}};


    return encodeStruct(cborStruct);
}
