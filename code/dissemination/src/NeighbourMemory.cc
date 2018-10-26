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

NeighbourMemory::NeighbourMemory(int memSize) :
    memSize    (memSize),
    //oldest     (0),
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

void NeighbourMemory::deleteDuplicates(int id){

    neighbours.remove_if([&](const neighbour_node& neighbour) {
        if(neighbour.id == id){
            return true;
        } else {
            return false;
        }
    });

}

void NeighbourMemory::newNeighbour(int id, simtime_t time) {

    deleteExpired(time);
    deleteDuplicates(id);
    neighbours.push_back({id, time});

}

vector<int> NeighbourMemory::getNeighbours() const {
    vector<int> ret;

    for (const auto& neighbour : neighbours) {
        ret.push_back(neighbour.id);
    }

    return ret;
}
