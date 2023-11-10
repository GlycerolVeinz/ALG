//
// Created by glycerolveinz on 5.11.23.
//


#include "Storage.h"

// ROOM CLASS ==========================================================================================================
Room::Room(int id, int transportTime){
    this->Id = id;
    this->transportTime = transportTime;
    this->totalTime = transportTime;
    this->curWeight = 0;
    this->previous = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}


void Room::placePackage(int weight) {
    this->packages.push_back(weight);
    this->curWeight += weight;
}

bool Room::isLeaf() const {
    return (this->left == nullptr) && (this->right == nullptr);
}

bool Room::willBlock() const {
    bool ret = false;
    if (this->left != nullptr){
        ret = this->left->curWeight == 0;
    }
    if (this->right != nullptr){
        ret = this->right->curWeight == 0;
    }
    return ret;
}

void Room::removePackage(int weight) {
    this->curWeight -= weight;
    packages.erase(std::remove(packages.begin(), packages.end(), weight), packages.end());
}

// STORAGE CLASS =======================================================================================================
int maxIntValue(){
    double sizeInBits = sizeof(int) * 8;
    return static_cast<int>(std::pow(2, sizeInBits - 1) - 1);
}

Storage::Storage(Room *mainRoom) {
    this->mainRoom = mainRoom;
    this->totalWeight = 0;
    this->allRooms.push_back(mainRoom);
    this->bestPackageDelivery.first = maxIntValue();
    this->bestPackageDelivery.second = maxIntValue();
}

void Storage::makeConnection(int parentId, int childId, int transportTime) {
    Room *parent = allRooms.at(parentId);

    Room child = createRoom(childId, transportTime);
    child.previous = parent;

    if(parent->left == nullptr){
        parent->left = &child;
    } else {
        parent->right = &child;
    }

    allRooms.push_back(&child);
    child.totalTime += parent->totalTime;
}

Room Storage::createRoom(int id, int transportTime) {
    Room room(id, transportTime);
    return room;
}

int Storage::calculateWeight(Room *parent, Room *child) {
    int weight = INVALID_ROOM_IN_CALCULATION;

    if(parent != nullptr && child != nullptr){
        weight = std::abs(parent->curWeight - child->curWeight);
        this->totalWeight += weight;
    }

    return weight;
}


