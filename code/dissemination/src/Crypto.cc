/*
 * Crypto.cpp
 *
 *  Created on: Feb 26, 2019
 *      Author: root
 */

#include "Crypto.h"
#include <iostream>


Crypto::Crypto() {
    //make sure sodium is initialized
    if (sodium_init() < 0) {
        throw "Sodium not initialized";
    }
}

std::vector<unsigned char> Crypto::encryptShare(Share share, std::vector<unsigned char> myPrivKey, std::vector<unsigned char> recipientPubKey){

    int ciphertext_len = crypto_box_MACBYTES + share.size();
    unsigned char nonce[crypto_box_NONCEBYTES];
    unsigned char ciphertext[ciphertext_len];
    randombytes_buf(nonce, sizeof nonce);

    if (crypto_box_easy(ciphertext, share.data(), share.size(), nonce, recipientPubKey.data(), myPrivKey.data()) != 0) {
        throw "Error when encrypting share";
    }

    std::vector<unsigned char> c(ciphertext, ciphertext + ciphertext_len);
    return c;
}

std::vector<unsigned char> Crypto::signShare(std::vector<unsigned char> msg, std::vector<unsigned char> myPrivKey){

    unsigned char signed_message[crypto_sign_BYTES + msg.size()];
    unsigned long long signed_message_len;
    crypto_sign(signed_message, &signed_message_len, msg.data(), msg.size(), myPrivKey.data());

    std::vector<unsigned char> c(signed_message, signed_message + signed_message_len);
    return c;
}







