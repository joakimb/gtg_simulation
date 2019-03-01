#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/GTGMessage.h"
#include "../src/PseudMessage.h"
#include "../src/ShareMessage.h"
#include "../src/base64.h"
#include <string>
#include <vector>

TEST_CASE("PseudReturnsCorrectTypeTest"){

	std::string pseudString = "dummypseud";
    std::vector<unsigned char> pseud (pseudString.begin(), pseudString.end());

	PseudMessage msg (pseud);
    REQUIRE(msg.getType() == "GTG_PSEUD");
}

TEST_CASE("PseudMessageEncodesCorrectlyTest"){

	std::string pseudString = "dummypseud";
    std::vector<unsigned char> pseud (pseudString.begin(), pseudString.end());

	PseudMessage msg (pseud);
	std::string encodedMessage = msg.getEncoded();

    std::string cborData = base64_decode(encodedMessage);
	json json = json::from_cbor(cborData);
    std::string type = json.at("gtg_type");
    std::vector<unsigned char> pseudVectDecoded = json.at("gtg_pseud");
    std::string pseudStringDecoded(pseudVectDecoded.begin(), pseudVectDecoded.end());

    REQUIRE(type == "GTG_PSEUD");
    REQUIRE(pseudStringDecoded == pseudString);
}

TEST_CASE("ShareReturnsCorrectTypeTest"){

	std::string shareString = "dummypseud";
    std::vector<unsigned char> share (shareString.begin(), shareString.end());

	ShareMessage msg (share);
    REQUIRE(msg.getType() == "GTG_SHARE");
}