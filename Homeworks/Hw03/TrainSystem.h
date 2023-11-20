//
// Created by glycerolveinz on 30.10.23.
//

#ifndef HW03_TRAINSYSTEM_H
#define HW03_TRAINSYSTEM_H

#include "CityBinaryTree.h"

void placeRailways(CityBinaryMap *tree);
void placeRailwaysHelper(CityBinaryMap *tree, City *currentCity, int railwaysSize);

#endif //HW03_TRAINSYSTEM_H
