#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/GTGMessage.h"
#include "../src/PseudMessage.h"
#include "../src/ShareMessage.h"
#include "../src/base64.h"
#include "../src/NeighbourMemory.h"
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

TEST_CASE("ShareMessageEncodesCorrectlyTest"){

	std::string shareString = "dummyshare";
    std::vector<unsigned char> share (shareString.begin(), shareString.end());

	ShareMessage msg (share);
	std::string encodedMessage = msg.getEncoded();

    std::string cborData = base64_decode(encodedMessage);
	json json = json::from_cbor(cborData);
    std::string type = json.at("gtg_type");
    std::vector<unsigned char> shareVectDecoded = json.at("gtg_share");
    std::string shareStringDecoded(shareVectDecoded.begin(), shareVectDecoded.end());

    REQUIRE(type == "GTG_SHARE");
    REQUIRE(shareStringDecoded == shareString);
}

TEST_CASE("AddOneNeighbourTest"){
	std::string carAS = "carA";
    std::vector<unsigned char> carA (carAS.begin(), carAS.end());

	NeighbourMemory mem (10);
	mem.newNeighbour(carA,1);
	std::vector<std::vector<unsigned char>> neighbours = mem.getNeighbours();
	REQUIRE(neighbours.size() == 1);
}

TEST_CASE("AddSeveralNeighboursTest"){
	std::string carAS = "carA";
    std::vector<unsigned char> carA (carAS.begin(), carAS.end());

	std::string carBS = "carB";
    std::vector<unsigned char> carB (carBS.begin(), carBS.end());

	std::string carCS = "carC";
    std::vector<unsigned char> carC (carCS.begin(), carCS.end());

	NeighbourMemory mem (10);
	mem.newNeighbour(carA,1);
	mem.newNeighbour(carB,1);
	mem.newNeighbour(carC,1);
	std::vector<std::vector<unsigned char>> neighbours = mem.getNeighbours();
	REQUIRE(neighbours.size() == 3);
}

TEST_CASE("DuplicatelNeighboursIgnoredTest"){
	std::string carAS = "carA";
    std::vector<unsigned char> carA (carAS.begin(), carAS.end());

	std::string carBS = "carB";
    std::vector<unsigned char> carB (carBS.begin(), carBS.end());

	NeighbourMemory mem (10);
	mem.newNeighbour(carA,1);
	mem.newNeighbour(carB,1);
	mem.newNeighbour(carA,1);
	std::vector<std::vector<unsigned char>> neighbours = mem.getNeighbours();
	REQUIRE(neighbours.size() == 2);
}

