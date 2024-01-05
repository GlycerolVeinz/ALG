#ifndef HW08_GARDEN_H
#define HW08_GARDEN_H

#include <iostream>
#include <vector>
#include <limits>

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
    unsigned int plantValue;
    bool isPlant;

    unsigned int cost;
    long bestCostPerRoute;
    long shortestPathLength;
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

Coord getNeighbourCoord(Tile *tile, std::pair<int,int> delta);
bool isOutOfBounds(Garden *garden, Coord *coord);
Tile *getTile(Garden *garden, Coord *coord);
vector<Tile*> getAllNeighbours(Garden *garden, Tile *tile);
Tile *readCurrentTile(size_t y, size_t x);
void updateMyCost(Garden* garden, Tile* tile);
Garden *readInput();

#endif //HW08_GARDEN_H
