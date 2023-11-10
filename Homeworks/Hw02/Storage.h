//
// Created by glycerolveinz on 5.11.23.
//

#ifndef HW02_STORAGE_H
#define HW02_STORAGE_H

#include <vector>
#include <cmath>
#include <algorithm>


class Room;

class Storage {
public:
#define INVALID_ROOM_IN_CALCULATION (-1)
//  first: weight second: time
    std::pair<int, int> bestPackageDelivery;
    Room *mainRoom;
    std::vector<Room *> allRooms;
    int totalWeight;
    std::vector<int> packages;

    static Room createRoom(int id, int transportTime);
    explicit Storage(Room *);
    void makeConnection(int parentId, int childId, int transportTime);
    int calculateWeight(Room *parent, Room *child);
};

class Room {
public:
    friend class Storage;

    int Id;
    std::vector<int> packages;
    Room *previous;
    Room *left;
    Room *right;
    int transportTime;
    int totalTime;
    int curWeight;

    Room(int id, int transportTime);
    void placePackage(int weight);
    void removePackage(int weight);
    bool isLeaf() const;
    bool willBlock() const;
};


#endif //HW02_STORAGE_H
