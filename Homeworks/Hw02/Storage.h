//
// Created by glycerolveinz on 5.11.23.
//

#ifndef HW02_STORAGE_H
#define HW02_STORAGE_H

#include <vector>
#include <queue>

class Room;

class Storage {
private:
    Room *mainRoom;
    std::vector<Room *> allRooms;

    int totalWeight;

public:
    static Room createRoom(int id, int transportTime);

    explicit Storage(Room *);
    void makeConnection(int parentId, int childId, int transportTime);

    Room *getMainRoom() const;
    void setMainRoom(Room *mainRoom);

    const std::vector<Room *> &getAllRooms() const;
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

    Room(int id, int transportTime);
public:
    friend class Storage;

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
