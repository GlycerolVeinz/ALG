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
private:
//  first: weight second: time
    std::pair<int, int> bestPackageDelivery;

    Room *mainRoom;
    std::vector<Room *> allRooms;

    int totalWeight;

    std::vector<int> packages;

public:
    #define INVALID_ROOM_IN_CALCULATION (-1)

    static Room createRoom(int id, int transportTime);

    explicit Storage(Room *);
    void makeConnection(int parentId, int childId, int transportTime);

    Room *getMainRoom();
    void setMainRoom(Room *mainRoom);

    std::pair<int, int> &getBestPackageDelivery();


    std::vector<int> getPackages();
    void setPackages(const std::vector<int> &packages);

    const std::vector<Room *> &getAllRooms() const;

    int calculateWeight(Room *parent, Room *child);
};

class Room {
private:
    int Id;

    std::vector<int> packages;

    Room *previous;
    Room *left;
    Room *right;

    int transportTime;
    int totalTime;
    int curWeight;

    Room(int id, int transportTime);

public:
    friend class Storage;

    void placePackage(int weight);
    void removePackage(int weight);

    const std::vector<int> &getPackages();
    int getId() const;
    Room *getPrevious() const;
    Room *getLeft() const;
    Room *getRight() const;
    int getTransportTime() const;
    int getTotalTime() const;

    int getCurWeight() const;
    void setId(int id);
    void setPrevious(Room *parent);
    void setLeft(Room *leftRoom);
    void setRight(Room *rightRoom);
    void setTransportTime(int t);
    void setCurWeight(int cW);
    void setTotalTime(int totalTime);

    bool isLeaf();
    bool willBlock();
};


#endif //HW02_STORAGE_H
