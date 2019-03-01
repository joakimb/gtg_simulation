#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/GTGMessage.h"
#include "../src/PseudMessage.h"
#include "../src/ShareMessage.h"
#include <string>
#include <vector>

TEST_CASE("PseudReturnsCorrectTypeTest"){

	std::string pseudString = "dummypseud";
    std::vector<unsigned char> pseud (pseudString.begin(), pseudString.end());

	PseudMessage msg (pseud);
    REQUIRE(msg.getType() == "GTG_PSEUD");
}

TEST_CASE("ShareReturnsCorrectTypeTest"){

	std::string shareString = "dummypseud";
    std::vector<unsigned char> share (shareString.begin(), shareString.end());

	ShareMessage msg (share);
    REQUIRE(msg.getType() == "GTG_SHARE");
}