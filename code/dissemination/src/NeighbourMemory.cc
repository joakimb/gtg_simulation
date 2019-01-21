/*
 * NeighbourMemory.cpp
 *
 *  Created on: Dec 14, 2018
 *      Author: root
 */

#include "NeighbourMemory.h"

#include <algorithm>
#include <sstream>
#include <iterator>

using omnetpp::simtime_t;
using std::vector;
using std::list;

NeighbourMemory::NeighbourMemory(simtime_t cutOff) :
    cutOff(cutOff),
    neighbours () {
}

void NeighbourMemory::deleteExpired(simtime_t time){

    neighbours.remove_if( [&](const neighbour_node& neighbour) {
        auto delta = time - neighbour.time;
        //std::cout << "delta: " << delta << "\n";
        if(delta > cutOff){
            return true;
        } else {
            return false;
        }
    });

}

void NeighbourMemory::deleteDuplicates(std::vector<unsigned char> pseud){

    //TODO does this work after moving from string to vector<char>?
    neighbours.remove_if([&](const neighbour_node& neighbour) {
        return (neighbour.pseud == pseud);
    });

}

void NeighbourMemory::newNeighbour(std::vector<unsigned char> pseud, simtime_t time) {

    deleteExpired(time);
    deleteDuplicates(pseud);
    neighbours.push_back({pseud, time});

}

std::vector<std::vector<unsigned char>>  NeighbourMemory::getNeighbours() const {
    vector<std::vector<unsigned char>> ret;

    for (const auto& neighbour : neighbours) {
        ret.push_back(neighbour.pseud);
    }

    return ret;
}
