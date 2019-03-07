/*
 * PseudMessage.h
 *
 *  Created on: Feb 28, 2019
 *      Author: root
 */

#pragma once
#include "GTGMessage.h"

class PseudMessage : public ::GTGMessage {
public:
    PseudMessage(std::vector<unsigned char> data);
    std::string getEncoded();
};
