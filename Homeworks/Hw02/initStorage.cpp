//
// Created by glycerolveinz on 5.11.23.
//

#include "initStorage.h"

using std::cin;
using std::cout;

Storage readInput(){
    int numberOfRooms, boxesCount;

    cin >> numberOfRooms >> boxesCount;

    std::queue<int> packages = readPackages(boxesCount);

    return readRooms(numberOfRooms);
}

std::queue<int> readPackages(int boxesCount){
    std::queue<int> packages;
    for (int i = 0; i < boxesCount; ++i) {
        int box;
        cin >> box;
        packages.push(box);
    }
    return packages;
}

Storage readRooms(int numberOfRooms){
    Room mainRoom = Storage::createRoom(0, 0);
    Storage storage(&mainRoom);
    for (int i = 0; i < numberOfRooms; ++i) {
        int parent, child, transportTime;
        cin >> parent >> child >> transportTime;
        storage.makeConnection(parent, child, transportTime);
    }

    return storage;
}