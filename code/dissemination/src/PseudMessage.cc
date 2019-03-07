/*
 * PseudMessage.cc
 *
 *  Created on: Feb 28, 2019
 *      Author: root
 */

#include "PseudMessage.h"

PseudMessage::PseudMessage(std::vector<unsigned char> _data) {
    type = "GTG_PSEUD";
    data = _data;
}


std::string PseudMessage::getEncoded(){

    json cborStruct;
    cborStruct["gtg_type"] = type;
    cborStruct["gtg_pseud"] = data;

    return encodeStruct(cborStruct);
}
