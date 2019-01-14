/*
 * Token.cpp
 *
 *  Created on: Jan 10, 2019
 *      Author: root
 */

#include "Token.h"

#include <assert.h>
#include <iostream>
#include <cstring>

Token::Token(const std::vector<uint8_t>& pseudonym, int numShares, int numReconstruct) :
    pseudonym(pseudonym),
    shares(numShares)
{

    std::vector<sss_Share> sss_shares{numShares};

    sss_create_shares(
        sss_shares.data(),
        pseudonym.data(),
        numShares,
        numReconstruct
    );

    for (size_t i = 0; i < numShares; ++i) {
        std::memcpy(shares[i].data(), sss_shares[i], sizeof(sss_Share));
    }


//======================================================
//    uint8_t data[sss_MLEN], restored[sss_MLEN];
//    sss_Share shares[5];
//    size_t idx;
//    int tmp;
//
//    /* Create a message [42, 42, ..., 42] */
//    for (idx = 0; idx < sizeof(data); ++idx) {
//        data[idx] = 42;
//    }
//
//    /* Split the secret into 5 shares (with a recombination theshold of 4) */
//    sss_create_shares(shares, data, 5, 4);
//
//    for (int i = 0; i < 5; i++){
//        std::cout << "share: " << (shares[i]) << "\n";
//    }
//
//    /* Combine some of the shares to restore the original secret */
//    tmp = sss_combine_shares(restored, shares, 4);
//    assert(tmp == 0);
//    assert(memcmp(restored, data, sss_MLEN) == 0);

}

Share Token::getNextShare(){
    if (nextShare < shares.size()){
        return shares[nextShare++];
    } else {
        throw "Attempting to take too many shares";
    }

}

void Token::putReceipt(std::string receipt){

}

bool Token::isDisseminated(){
    return false;
}

Token::~Token() {
    // TODO Auto-generated destructor stub
}

std::vector<uint8_t> Token::genRandomPseud(){
    std::vector<uint8_t> pseudonym{sss_MLEN};
    for (size_t i = 0; i < pseudonym.size(); ++i) {
        pseudonym[i] = 42;
    }
    return pseudonym;
}