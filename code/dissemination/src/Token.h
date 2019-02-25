#pragma once

#include <string>
#include <list>
#include <map>
#include <vector>
#include "PseudCred.h"
extern "C" {
    #include <sss.h>
}

typedef std::array<uint8_t, sizeof(sss_Share)> Share;

class Token {
public:
    Token(const std::vector<uint8_t>& ltid, int numShares, int numReconstruct);
    virtual ~Token();
    Share getNextShare();
    void putReceipt(std::string receipt);
    bool isDisseminated();
    PseudCred getPseud();


private:
    PseudCred pseud;
    std::vector<uint8_t> ltid;
    std::vector<Share> shares;
    std::map<std::string, std::string> recipts;
    uint nextShare = 0;
};
