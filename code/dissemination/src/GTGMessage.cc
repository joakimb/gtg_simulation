/*
 * GTGMessage.cc
 *
 *  Created on: Feb 28, 2019
 *      Author: root
 */

#include "GTGMessage.h"
#include "base64.h"

std::string GTGMessage::getType(){
    return type;
}

std::string GTGMessage::encodeStruct(json cborStruct){

    std::vector<std::uint8_t> cborMsg = json::to_cbor(cborStruct);
    const unsigned char* cborMsgChar = reinterpret_cast<const unsigned char*>(cborMsg.data());//.c_str();
    //todo consider using sodium bin2hex instead of base64
    return base64_encode(cborMsgChar, cborMsg.size());

}


std::vector<unsigned char> GTGMessage::getData(){
    return data;
}

