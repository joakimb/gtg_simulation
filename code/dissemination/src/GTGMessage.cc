/*
 * GTGMessage.cc
 *
 *  Created on: Feb 28, 2019
 *      Author: root
 */

#include "GTGMessage.h"
#include "base64.h"

GTGMessage::GTGMessage(std::string type, std::vector<unsigned char> data) :
    type(type),
    data(data){
}

std::string GTGMessage::getType(){
    return type;
}

std::string GTGMessage::getEncoded(){

    json cborStruct;
    cborStruct["gtg_type"] = type;

    if (type == GTG_MSG_TYPE_PSEUD) {

        cborStruct["gtg_pseud"] = data;

    } else if(type == GTG_MSG_TYPE_SHARE){

        cborStruct["gtg_share"] = data;

    } else {

        throw "bad message type";

    }

    return encodeStruct(cborStruct);
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

