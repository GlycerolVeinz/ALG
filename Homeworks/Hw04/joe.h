//
// Created by glycerolveinz on 28.11.23.
//

#ifndef HW04_JOE_H
#define HW04_JOE_H

#include <queue>
#include <set>
#include "GameField.h"

int findPath(GameField *gameField);
void printMove(Tile *from, Tile *to);

struct TileComparator {
    bool operator()(const Tile *a, const Tile *b) const {
        return a->algValues.gCost > b->algValues.gCost;
    }
};

#endif //HW04_JOE_H
