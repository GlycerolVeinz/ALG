//
// Created by glycerolveinz on 20.11.23.
//

#ifndef HW03_CITYBINARYTREE_H
#define HW03_CITYBINARYTREE_H

#include <iostream>
#include <vector>

using std::vector;

struct City{
    int id;
    City *left;
    City *right;
    City *parent;
    int leftBranchMaxDepth;
    int rightBranchMaxDepth;
    int leftSubtreeSize;
    int rightSubtreeSize;
};

struct CityBinaryMap {
    City *root;
    vector<int> citiesInorder;
    vector<int> citiesPreorder;
    int result;
};

CityBinaryMap *readInput();
CityBinaryMap *createCityBinaryTree(vector<int> citiesInorder, vector<int> citiesPreorder);

void buildCityBinaryMap(CityBinaryMap *tree);
City *recursiveBuildHelper(vector<int> preorder, const vector<int>& inorder, City *parent);
City *createCity(int id, City *parent);

void destroyCity(City *city);
void destroyCityBinaryTree(CityBinaryMap *tree);


#endif //HW03_CITYBINARYTREE_H
