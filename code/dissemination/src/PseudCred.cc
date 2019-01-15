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

std::string PseudCred::getPubKey(){
    return std::string{reinterpret_cast<char*>(pubKey), crypto_box_PUBLICKEYBYTES};
}
