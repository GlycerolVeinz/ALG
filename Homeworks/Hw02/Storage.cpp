//
// Created by glycerolveinz on 5.11.23.
//

#include "Storage.h"

// ROOM CLASS ==========================================================================================================
Room::Room(int id, int transportTime){
    this->Id = id;
    this->transportTime = transportTime;
    this->curWeight = 0;
    this->previous = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}


int Room::getId() const {
    return Id;
}

const std::vector<int> &Room::getBoxes() const {
    return boxes;
}

Room *Room::getPrevious() const {
    return previous;
}

Room *Room::getLeft() const {
    return left;
}

Room *Room::getRight() const {
    return right;
}

int Room::getTransportTime() const {
    return transportTime;
}

int Room::getCurWeight() const {
    return curWeight;
}

void Room::setId(int id) {
    Id = id;
}


void Room::setPrevious(Room *parent) {
    Room::previous = parent;
}

void Room::setLeft(Room *leftRoom) {
    Room::left = leftRoom;
}

void Room::setRight(Room *rightRoom) {
    Room::right = rightRoom;
}

void Room::setTransportTime(int t) {
    Room::transportTime = t;
}

void Room::setCurWeight(int cW) {
    Room::curWeight = cW;
}

// STORAGE CLASS =======================================================================================================
Storage::Storage(Room *mainRoom) {
    this->mainRoom = mainRoom;
    this->totalWeight = 0;
    this->allRooms.push_back(mainRoom);
}

Room *Storage::getMainRoom() const {
    return mainRoom;
}

void Storage::setMainRoom(Room *mRoom) {
    Storage::mainRoom = mRoom;
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
}

Room Storage::createRoom(int id, int transportTime) {
    Room room(id, transportTime);
    return room;
}

const std::vector<Room *> &Storage::getAllRooms() const {
    return allRooms;
}
