//
// Created by glycerolveinz on 5.11.23.
//

#include "storageUtils.h"

Storage readInput(){
    int numberOfRooms, boxesCount;

    cin >> numberOfRooms >> boxesCount;

    std::vector<int> packages = readPackages(boxesCount);

    return readRooms(numberOfRooms, packages);
}

std::vector<int> readPackages(int boxesCount){
    std::vector<int> packages;
    for (int i = 0; i < boxesCount; ++i) {
        int package;
        cin >> package;
        packages.push_back(package);
    }
    return packages;
}

Storage readRooms(int numberOfRooms, std::vector<int> packages){
    Room mainRoom = Storage::createRoom(0, 0);

    Storage storage(&mainRoom);
    for (int i = 0; i < numberOfRooms - 1; ++i) {
        int parent, child, transportTime;
        cin >> parent >> child >> transportTime;
        storage.makeConnection(parent, child, transportTime);
    }

    storage.setPackages(packages);

    return storage;
}

void recursivePlace(Storage *storage, int curPackageId, int curTime){
    if (curPackageId + 1 == storage->getPackages().size()){
        int totalWeight = 0;
        int totalTime = curTime;

        for (auto curRoom : storage->getAllRooms()){
            totalWeight += curRoom->getCurWeight();
        }

        if (totalWeight < storage->getBestPackageDelivery().first){
            storage->getBestPackageDelivery().first = totalWeight;
            storage->getBestPackageDelivery().second = totalTime;
        }
        else if (totalWeight == storage->getBestPackageDelivery().first){
            if (totalTime < storage->getBestPackageDelivery().second){
                storage->getBestPackageDelivery().second = totalTime;
            }
        }
    }
    else{
        int curPackage = storage->getPackages().at(curPackageId);

        for (auto curRoom : storage->getAllRooms()) {
            if(!curRoom->isLeaf() || curRoom->willBlock()) continue;

            curRoom->placePackage(curPackage);
            curTime += curRoom->getTotalTime();
            if (storage->calculateWeight(curRoom, curRoom->getPrevious()) == -1){
                throw std::invalid_argument("ERROR: Invalid rooms");
            }

            // check all possibilities
            recursivePlace(storage, ++curPackageId, curTime);

            // backtrack
            curRoom->removePackage(curPackage);
        }
    }
}

void printResult(Storage *storage){
    cout << storage->getBestPackageDelivery().first << " " << storage->getBestPackageDelivery().second << endl;
}
