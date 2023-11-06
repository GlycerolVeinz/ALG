//
// Created by glycerolveinz on 5.11.23.
//

#include "storageUtils.h"

using std::cin;
using std::cout;

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
    for (int i = 0; i < numberOfRooms; ++i) {
        int parent, child, transportTime;
        cin >> parent >> child >> transportTime;
        storage.makeConnection(parent, child, transportTime);
    }

    storage.setPackages(packages);

    return storage;
}

void recursivePlace(Storage *storage, int curPackageId){
    if (curPackageId + 1 == storage->getPackages().size()){

    }
    else{
        int curPackage = storage->getPackages().at(curPackageId);

        for (auto curRoom : storage->getAllRooms()) {
            if(!curRoom->isLeaf() || curRoom->willBlock()) continue;

            curRoom->placePackage(curPackage);
            if (storage->calculateWeight(curRoom, curRoom->getPrevious()) == -1){
                throw std::invalid_argument("ERROR: Invalid rooms");
            }

            // check all possibilities
            recursivePlace(storage, ++curPackageId);

            // backtrack
            curRoom->removePackage(curPackage);
        }
    }
}

//std::pair<int, int> findBestPackageDelivery(Storage *storage){
////  get a box
//    int curPackage = storage->getPackages().front();
//
//    //  place it in the furthest valid room (leaf || not blocking)
//    for (auto curRoom : storage->getAllRooms()) {
//        if(!curRoom->isLeaf() || curRoom->willBlock()) continue;
//        curRoom->placePackage(curPackage);
//        //  get time and weight
//
//
//
//        //  check all possibilities
//
//
//        //  repeat until no boxes left
//        curRoom->removePackage(curPackage);
//    }
//}

