/*
 * ShareMessage.h
 *
 *  Created on: Feb 28, 2019
 *      Author: root
 */

#pragma once
#include "GTGMessage.h"

class ShareMessage : public ::GTGMessage {
public:
    ShareMessage(std::vector<unsigned char> data);
    std::string getEncoded();
};


