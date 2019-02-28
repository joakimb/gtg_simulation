/*
 * ShareMessage.cc
 *
 *  Created on: Feb 28, 2019
 *      Author: root
 */

#include "ShareMessage.h"

ShareMessage::ShareMessage(std::vector<unsigned char> _data) {
    type = "GTG_SHARE",
    data = _data;
}


std::string ShareMessage::getEncoded(){

    json cborStruct;
    cborStruct["gtg_type"] = type;
    cborStruct["gtg_share"] = data;

    return encodeStruct(cborStruct);
}
