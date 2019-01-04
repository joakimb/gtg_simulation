/*
 * NeighbourMemory.h
 *
 *  Created on: Dec 14, 2018
 *      Author: root
 */
#pragma once

#include "omnetpp/simtime_t.h"
#include <list>
#include <vector>

struct neighbour_node {
    int id;
    omnetpp::simtime_t time;
};

//keeps track of latest sightings of closest neighbours
class NeighbourMemory {
public:
    NeighbourMemory(int memSize);
    void newNeighbour(int id, omnetpp::simtime_t time);
    std::vector<int> getNeighbours() const;
    void deleteExpired(omnetpp::simtime_t time);
private:
    int memSize;
    omnetpp::simtime_t cutOff = 1; //forget neighbours after one second
    std::list<neighbour_node> neighbours;
    void deleteDuplicates(int id);
};
