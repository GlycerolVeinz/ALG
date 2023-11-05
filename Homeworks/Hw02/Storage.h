//
// Created by glycerolveinz on 5.11.23.
//

#ifndef HW02_STORAGE_H
#define HW02_STORAGE_H

#include <vector>

class Room;

class Storage {
private:
    Room *mainRoom;

    int totalWeight;

public:
    Storage(Room mainRoom);

    Room *getMainRoom() const;

    void setMainRoom(Room *mainRoom);
};

class Room {
private:
    int Id;

    std::vector<int> boxes;

    Room *previous;
    Room *left;
    Room *right;

    int transportTime;
    int curWeight;

public:
    Room(int id, int transportTime, Room *previous);

    int getId() const;

    const std::vector<int> &getBoxes() const;

    Room *getPrevious() const;
    Room *getLeft() const;
    Room *getRight() const;
    int getTransportTime() const;
    int getCurWeight() const;

    void setId(int id);
    void setPrevious(Room *parent);
    void setLeft(Room *leftRoom);
    void setRight(Room *rightRoom);
    void setTransportTime(int t);
    void setCurWeight(int cW);
};


#endif //HW02_STORAGE_H
