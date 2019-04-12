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

std::vector<unsigned char> Crypto::encryptShare(Share share, std::vector<unsigned char> myPrivKey, std::vector<unsigned char> recipientPubKey){
    //todo
    std::string s = "DUMMYMESSAGE";
    std::vector<unsigned char> v( s.begin(), s.end() );
    return v;
}

std::vector<unsigned char> Crypto::signShare(Share share, std::vector<unsigned char> myPrivKey){
    //todo
    std::string s = "DUMMYSIGN";
    std::vector<unsigned char> v( s.begin(), s.end() );
    return v;
}







