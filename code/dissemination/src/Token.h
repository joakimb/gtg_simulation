#pragma once

#include <string>
#include <list>
#include <map>
#include <vector>
extern "C" {
    #include <sss.h>
    #include <randombytes.h>
}

typedef std::array<uint8_t, sizeof(sss_Share)> Share;

class Token {
public:
    Token(const std::vector<uint8_t>& pseudonym, int numShares, int numReconstruct);
    virtual ~Token();
    Share getNextShare();
    void putReceipt(std::string receipt);
    bool isDisseminated();

    static std::vector<uint8_t> genRandomPseud();
private:
    std::vector<uint8_t> pseudonym;
    std::vector<Share> shares;
    std::map<std::string, std::string> recipts;
    uint nextShare = 0;
};
