//
// Created by glycerolveinz on 30.10.23.
//

#ifndef HW03_TRAINSYSTEM_H
#define HW03_TRAINSYSTEM_H

#include <iostream>
#include <vector>

struct City {
    int id;
    City *leftCity;
    City *rightCity;
};

struct CityBinaryTree {
    City *root;
    int maxId;
    int maxDepth;
};

void recordCities(std::vector<int> *cityIds, unsigned int numOfCities);

CityBinaryTree *createCityBinaryTree(std::vector<int> *cityIds, unsigned int numOfCities);

#endif //HW03_TRAINSYSTEM_H
