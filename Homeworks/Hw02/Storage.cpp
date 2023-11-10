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


int Room::getId() const {
    return Id;
}

const std::vector<int> &Room::getPackages(){
    return packages;
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

void Room::placePackage(int weight) {
    this->packages.push_back(weight);
    this->curWeight += weight;
}

bool Room::isLeaf() {
    return (this->left == nullptr) && (this->right == nullptr);
}

bool Room::willBlock() {
    bool ret = false;
    if (this->left != nullptr){
        ret = this->left->getCurWeight() == 0;
    }
    if (this->right != nullptr){
        ret = this->right->getCurWeight() == 0;
    }

    return ret;
}

void Room::removePackage(int weight) {
    this->curWeight -= weight;
    packages.erase(std::remove(packages.begin(), packages.end(), weight), packages.end());
}

int Room::getTotalTime() const {
    return totalTime;
}

void Room::setTotalTime(int total) {
    Room::totalTime = total;
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

Room *Storage::getMainRoom(){
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
    child.totalTime += parent->totalTime;
}

Room Storage::createRoom(int id, int transportTime) {
    Room room(id, transportTime);
    return room;
}

const std::vector<Room *> &Storage::getAllRooms() const {
    return allRooms;
}

int Storage::calculateWeight(Room *parent, Room *child) {
    int weight = INVALID_ROOM_IN_CALCULATION;

    if(parent != nullptr && child != nullptr){
        weight = std::abs(parent->getCurWeight() - child->getCurWeight());
        child->setCurWeight(weight);
        this->totalWeight += weight;
    }

    return weight;
}

std::vector<int> Storage::getPackages(){
    return packages;
}

void Storage::setPackages(const std::vector<int> &pack) {
    Storage::packages = pack;
}

std::pair<int, int> &Storage::getBestPackageDelivery(){
    return bestPackageDelivery;
}


