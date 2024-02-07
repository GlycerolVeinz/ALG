//
// Created by safor on 7.2.24.
//

#ifndef ZKOUSKA3_BIRDS_H
#define ZKOUSKA3_BIRDS_H

#include <iostream>
#include <vector>

using std::pair;
using std::vector;

typedef pair<int,int> Coord;

typedef struct {
    Coord coord;
    int value;

    int dangerSumHorizontal;
    int dangerSumVertical;
} Node;

typedef struct{
    Coord leftCorner;
    int width;
    int height;
    vector<Node*> nodes;
} BirdSector;


#endif //ZKOUSKA3_BIRDS_H
