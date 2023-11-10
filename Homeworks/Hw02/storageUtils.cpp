//
// Created by glycerolveinz on 5.11.23.
//

#include "storageUtils.h"

#include <utility>

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

    int parent, child, transportTime;
    for (int i = 0; i < numberOfRooms - 1; ++i) {
        cin >> parent >> child >> transportTime;
        storage.makeConnection(parent, child, transportTime);
    }

    storage.packages = std::move(packages);

    return storage;
}

void recursivePlace(Storage *storage, int curPackageId, int curTime){
    if (curPackageId + 1 == storage->packages.size()){
        int totalWeight = 0;
        int totalTime = curTime;

        for (auto curRoom : storage->allRooms){
            totalWeight += curRoom->curWeight;
        }

        if (totalWeight < storage->bestPackageDelivery.first){
            storage->bestPackageDelivery.first = totalWeight;
            storage->bestPackageDelivery.second = totalTime;
        }
        else if (totalWeight == storage->bestPackageDelivery.first){
            if (totalTime < storage->bestPackageDelivery.second){
                storage->bestPackageDelivery.second = totalTime;
            }
        }
    }
    else{
        int curPackage = storage->packages.at(curPackageId);

        for (auto curRoom : storage->allRooms) {
            if(!curRoom->isLeaf() || curRoom->willBlock()) continue;

            curRoom->placePackage(curPackage);
            curTime += curRoom->totalTime;
            if (storage->calculateWeight(curRoom->previous, curRoom) == -1){
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
    cout << storage->bestPackageDelivery.first << " " << storage->bestPackageDelivery.second << endl;
}
