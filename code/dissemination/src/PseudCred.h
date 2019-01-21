/*
 * PseudCred.h
 *
 *  Created on: Jan 15, 2019
 *      Author: root
 */

#pragma once

#include <sodium.h>

#include <vector>

class PseudCred {
public:
    PseudCred();
    std::vector<unsigned char> getPubKey();
private:
    unsigned char pubKey[crypto_box_PUBLICKEYBYTES];
    unsigned char privKey[crypto_box_SECRETKEYBYTES];
};

