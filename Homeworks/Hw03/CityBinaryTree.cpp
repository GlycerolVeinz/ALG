//
// Created by glycerolveinz on 20.11.23.
//

#include "CityBinaryTree.h"

vector<int> getLeftSubtree(const vector<int>& inorder, int rootId){
    vector<int> leftSubtree;
    for (auto id : inorder) {
        leftSubtree.push_back(id);
        if (id == rootId){
            break;
        }
    }
    return leftSubtree;
}

vector<int> getRightSubtree(const vector<int>& inorder, int rootId){
    vector<int> rightSubtree;
    bool foundRoot = false;
    for (auto id : inorder) {
        if (foundRoot){
            rightSubtree.push_back(id);
        }
        if (id == rootId){
            foundRoot = true;
        }
    }
    return rightSubtree;
}

vector<int> getSlice(const vector<int>& v, int start, int end){
    vector<int> slice;
    for (int i = start; i < end; ++i) {
        slice.push_back(v.at(i));
    }
    return slice;
}

void calculateLeftBranchMaxDepth(City *city){
    if (city->left == nullptr){
        city->leftBranchMaxDepth = 0;
        return;
    }
    city->leftBranchMaxDepth = std::max(city->left->leftBranchMaxDepth, city->left->rightBranchMaxDepth) + 1;
}

void calculateRightBranchMaxDepth(City *city){
    if (city->right == nullptr){
        city->rightBranchMaxDepth = 0;
        return;
    }
    city->rightBranchMaxDepth = std::max(city->right->leftBranchMaxDepth, city->right->rightBranchMaxDepth) + 1;
}

City *recursiveBuildHelper(vector<int> preorder, const vector<int> &inorder, City *parent) {
    if (preorder.empty() || inorder.empty()){
        return nullptr;
    }

    int rootId = preorder.at(0);
    City *currentCity = createCity(rootId, parent);
    if (preorder.size() == 1){
        return currentCity;
    }

//    split inorder into left and right subtrees
    vector<int> leftInorder = getLeftSubtree(inorder, rootId);
    vector<int> rightInorder = getRightSubtree(inorder, rootId);
//    split preorder into left and right subtrees
    vector<int> leftPreorder = getSlice(preorder, 1, static_cast<int>(leftInorder.size()));
    vector<int> rightPreorder = getSlice(preorder, static_cast<int>(leftInorder.size()), static_cast<int>(preorder.size()));

    currentCity->leftSubtreeSize = static_cast<int>(leftInorder.size());
    currentCity->rightSubtreeSize = static_cast<int>(rightInorder.size());

    currentCity->left = recursiveBuildHelper(leftPreorder, leftInorder, currentCity);
    currentCity->right = recursiveBuildHelper(rightPreorder, rightInorder, currentCity);

    calculateLeftBranchMaxDepth(currentCity);
    calculateRightBranchMaxDepth(currentCity);

    return currentCity;
}

void buildCityBinaryMap(CityBinaryMap *tree){
    City *rootCity = recursiveBuildHelper(tree->citiesPreorder, tree->citiesInorder, nullptr);
    tree->root = rootCity;
}

CityBinaryMap *readInput(){
    int numberOfCities;
    std::cin >> numberOfCities;
    vector<int> citiesInorder;
    vector<int> citiesPreorder;

    for (int i = 1; i <= numberOfCities; ++i) {
        int cityId;
        std::cin >> cityId;
        citiesPreorder.push_back(cityId);
        citiesInorder.push_back(i);
    }

    return createCityBinaryTree(citiesInorder, citiesPreorder);
}

CityBinaryMap *createCityBinaryTree(vector<int> citiesInorder, vector<int> citiesPreorder){
    auto *tree = new CityBinaryMap;

    tree->citiesInorder = std::move(citiesInorder);
    tree->citiesPreorder = std::move(citiesPreorder);
    tree->root = nullptr;
    tree->result = 0;

    return tree;
}

City *createCity(int id, City *parent){
    auto *city = new City;

    city->id = id;
    city->left = nullptr;
    city->right = nullptr;
    city->parent = parent;
    city->leftBranchMaxDepth = 0;
    city->rightBranchMaxDepth = 0;
    city->leftSubtreeSize = 0;
    city->rightSubtreeSize = 0;

    return city;
}

void destroyCity(City *city){
    if (city == nullptr){
        return;
    }
    destroyCity(city->left);
    destroyCity(city->right);
    delete city;
}

void destroyCityBinaryTree(CityBinaryMap *tree){
    destroyCity(tree->root);
    delete tree;
}
