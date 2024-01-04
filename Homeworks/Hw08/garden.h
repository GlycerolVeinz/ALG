#ifndef HW08_GARDEN_H
#define HW08_GARDEN_H

#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std:: cerr;

typedef struct {
    size_t x;
    size_t y;
} Coord;

typedef struct {
    Coord *coord;
    int plantValue;
    bool isPlant;

    int cost;
} Tile;

typedef struct {
    vector<vector<Tile *>> gardenMap;
    size_t width, height;
} Garden;

#define UP_NEIGHBOUR std::pair<int,int>(0, -1)
#define DOWN_NEIGHBOUR std::pair<int,int>(0, 1)
#define LEFT_NEIGHBOUR std::pair<int,int>(-1, 0)
#define RIGHT_NEIGHBOUR std::pair<int,int>(1, 0)
#define ALL_NEIGHBOURS {UP_NEIGHBOUR, DOWN_NEIGHBOUR, LEFT_NEIGHBOUR, RIGHT_NEIGHBOUR}

bool isOutOfBounds(Garden *garden, Coord *coord);
Tile *getTile(Garden *garden, Coord *coord);
vector<Tile*> getAllNeighbours(Garden *garden, Tile *tile);
Tile *readCurrentTile(size_t y, size_t x);
void updateNeighbourCosts(Garden* garden, Tile* tile);
void updateCosts(Garden *garden);
Garden *readInput();

#endif //HW08_GARDEN_H
