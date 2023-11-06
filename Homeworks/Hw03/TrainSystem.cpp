//
// Created by glycerolveinz on 30.10.23.
//

#include "TrainSystem.h"


int main() {
    unsigned int numOfCities;
    std::cin >> numOfCities;
    std::vector<int> cityIdsPre;

    recordCities(&cityIdsPre, numOfCities);

    CityBinaryTree *CBT = createCityBinaryTree(&cityIdsPre, numOfCities);

    return 0;
}

void recordCities(std::vector<int> *cityIds, unsigned int numOfCities){
    for (int i = 0; i < numOfCities; i++) {
        int temp;
        std::cin >> temp;
        cityIds->push_back(temp);
    }
}

CityBinaryTree *createCityBinaryTree(std::vector<int> *cityIds, unsigned int numOfCities){
    CityBinaryTree CBT;
    CBT.maxId = 0;
    CBT.maxDepth = 0;
    CBT.root = new City;
    CBT.root->id = cityIds->at(0);
    CBT.root->leftCity = nullptr;
    CBT.root->rightCity = nullptr;
    for (int i = 1; i < cityIds->size(); i++) {
        City *temp = CBT.root;
        while (true) {
            if (cityIds->at(i) < temp->id) {
                if (temp->leftCity == nullptr) {
                    temp->leftCity = new City;
                    temp->leftCity->id = cityIds->at(i);
                    temp->leftCity->leftCity = nullptr;
                    temp->leftCity->rightCity = nullptr;
                    break;
                } else {
                    temp = temp->leftCity;
                }
            } else {
                if (temp->rightCity == nullptr) {
                    temp->rightCity = new City;
                    temp->rightCity->id = cityIds->at(i);
                    temp->rightCity->leftCity = nullptr;
                    temp->rightCity->rightCity = nullptr;
                    break;
                } else {
                    temp = temp->rightCity;
                }
            }
        }
    }
    return &CBT;
}
