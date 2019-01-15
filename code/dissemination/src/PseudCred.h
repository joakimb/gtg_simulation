/*
 * PseudCred.h
 *
 *  Created on: Jan 15, 2019
 *      Author: root
 */

#pragma once

#include <sodium.h>

#include <string>

class PseudCred {
public:
    PseudCred();
    std::string getPubKey();
private:
    unsigned char pubKey[crypto_box_PUBLICKEYBYTES];
    unsigned char privKey[crypto_box_SECRETKEYBYTES];
};

