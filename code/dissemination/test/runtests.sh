#g++ -std=c++11 -Wall -ICatch2/catch.h -I../src/ChannelService.h -o ChannelServiceTest ChannelServiceTest.cc ../src/ChannelService.cc && ./ChannelServiceTest --success
g++ -std=c++11 -Wall -ICatch2/catch.h -I../../json/single_include -I../src -o GTGTest GTGTest.cc ../src/PseudMessage.cc ../src/ShareMessage.cc ../src/GTGMessage.cc ../src/base64.cc && ./GTGTest --success
