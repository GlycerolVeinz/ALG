//
// Created by safor on 7.2.24.
//

#ifndef ZKOUSKA3_BIRDS_H
#define ZKOUSKA3_BIRDS_H

#include <iostream>
#include <vector>
#include <limits>

using std::pair;
using std::vector;
using std::cin;
using std::cout;
using std::cerr;

typedef pair<int, int> Coord;

class BirdSector;

class Node{
public:
    Coord coord;
    int val;

    int dangerSumHorizontal;
    int dangerSumVertical;

    int sectorsSumVertical;
    int sectorsSumHorizontal;

    int sectorNodesSumVertical;
    int sectorNodesSumHorizontal;

    BirdSector *inSector;

    Node() = default;
};

class BirdSector {
public:
    Coord leftCorner;
    int width;
    int height;
    vector<Node *>nodes;

    explicit BirdSector(Node *n);
};

class Field{
public:
    vector<vector<Node *>> nodes;
    vector<BirdSector *> sectors;
    int height;
    int width;
    int res;

    Field() = default;

    static Field *readField();
    void printField();
    bool coordOutOfBounds(Coord coord);
    Node *getNode(Coord coord);
};
#endif //ZKOUSKA3_BIRDS_H
