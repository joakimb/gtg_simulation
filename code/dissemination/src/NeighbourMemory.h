/*
 * NeighbourMemory.h
 *
 *  Created on: Dec 14, 2018
 *      Author: root
 */
#pragma once

//#include "omnetpp/simtime_t.h"
#include <list>
#include <vector>

struct neighbour_node {
    std::vector<unsigned char> pseud;
    int time;
};

//keeps track of latest sightings of closest neighbours
class NeighbourMemory {
public:
    NeighbourMemory(int cutOff);
    void newNeighbour(std::vector<unsigned char> pseud, int time);
    std::vector<std::vector<unsigned char>> getNeighbours() const;
    void deleteExpired(int time);
private:
    int memSize;
    int cutOff; //forget neighbours after defined time (in omnetpp.ini)
    std::list<neighbour_node> neighbours;
    void deleteDuplicates(std::vector<unsigned char> pseud);
};
