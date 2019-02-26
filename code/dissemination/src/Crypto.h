/*
 * Crypto.h
 *
 *  Created on: Feb 26, 2019
 *      Author: root
 */

#pragma once
#include <sodium.h>
#include <vector>
#include <string>
#include "Token.h"


class Crypto {
public:
    Crypto();
    std::string encryptShare(Share share, std::vector<unsigned char> myPrivKey, std::vector<unsigned char> recipientPubKey);
};


