/*
 * Crypto.cpp
 *
 *  Created on: Feb 26, 2019
 *      Author: root
 */

#include "Crypto.h"


Crypto::Crypto() {
    //make sure sodium is initialized
    if (sodium_init() < 0) {
        throw "Sodium not initialized";
    }
}

std::string Crypto::encryptShare(Share share, std::vector<unsigned char> myPrivKey, std::vector<unsigned char> recipientPubKey){
    //todo
    return "DUMMYMESSAGE";
}






