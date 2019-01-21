/*
 * PseudCred.cc
 *
 *  Created on: Jan 15, 2019
 *      Author: root
 */

#include "PseudCred.h"

PseudCred::PseudCred() {
    //make sure sodium is initialized
    if (sodium_init() < 0) {
        throw "Sodium not initialized";
    }
    crypto_box_keypair(pubKey, privKey);
}

std::vector<unsigned char>PseudCred::getPubKey(){
    return std::vector<unsigned char>(pubKey, pubKey + sizeof(pubKey)/sizeof(*pubKey));
}
