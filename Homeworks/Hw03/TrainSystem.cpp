//
// Created by glycerolveinz on 30.10.23.
//

#include "TrainSystem.h"

int main() {
    CityBinaryMap *tree = readInput();
    buildCityBinaryMap(tree);

    placeRailways(tree);

    std::cout << tree->result << std::endl;

    destroyCityBinaryTree(tree);
    exit(0);
}

void placeRailwaysHelper(CityBinaryMap *tree, City *currentCity, int railwaysSize){
    if (currentCity == nullptr){
        if(railwaysSize > tree->result){
            tree->result = railwaysSize;
        }
    } else {
        int railwaySizeGoingLeft = railwaysSize + 1 + currentCity->rightBranchMaxDepth;
        int railwaySizeGoingRight = railwaysSize + 1 + currentCity->leftBranchMaxDepth;

        placeRailwaysHelper(tree, currentCity->left, railwaySizeGoingLeft);
        placeRailwaysHelper(tree, currentCity->right, railwaySizeGoingRight);

    }
}

void placeRailways(CityBinaryMap *tree) {
    City *currentCity = tree->root;
    placeRailwaysHelper(tree, currentCity, 0);
}

