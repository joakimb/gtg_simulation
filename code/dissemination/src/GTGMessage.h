/*
 * GTGMessage.h
 *
 *  Created on: Feb 28, 2019
 *      Author: root
 */

#pragma once

#include "veins/modules/messages/BasicSafetyMessage_m.h"
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define GTG_MSG_TYPE_PSEUD "GTG_PSEUD"
#define GTG_MSG_TYPE_SHARE "GTG_SHARE"

class GTGMessage {
public:
    std::string getType();
    virtual std::string getEncoded() =0;
    std::vector<unsigned char> getData();
protected:
    std::string encodeStruct(json cborStruct);

protected:
    std::string type;
    std::vector<unsigned char> data;
};

