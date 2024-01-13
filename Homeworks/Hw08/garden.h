#ifndef HW08_GARDEN_H
#define HW08_GARDEN_H

#include <iostream>
#include <vector>
#include <limits>

using std::vector;
using std::cin;
using std::cout;
using std:: cerr;

#define DIRECTIONS_COUNT 2

#define LEFT_DIR 0
#define RIGHT_DIR 1

typedef struct {
    char dir;
    size_t x;
    size_t y;
} Coord;

typedef struct {
    Coord *coord;
    unsigned short plantValue;
    bool isPlant;

    unsigned short cost;
    size_t bestCost;
    size_t shortestPath;
} Tile;

typedef vector<vector<vector<Tile *>>> GardenMap;

typedef struct {
    GardenMap gardenMap;
    size_t width, height;
} Garden;

#define UP_NEIGHBOUR std::pair<int,int>(-1, 0)
#define DOWN_NEIGHBOUR std::pair<int,int>(1, 0)
#define LEFT_NEIGHBOUR std::pair<int,int>(0, -1)
#define RIGHT_NEIGHBOUR std::pair<int,int>(0, 1)
#define ALL_NEIGHBOURS {UP_NEIGHBOUR, DOWN_NEIGHBOUR, LEFT_NEIGHBOUR, RIGHT_NEIGHBOUR}

Coord makeCoord(char dir, size_t y, size_t x);

Coord getNeighbourCoord(Tile *tile, char dir, std::pair<size_t ,size_t> delta);

Tile *getNeighbourTile(Garden *garden, Tile *tile, std::pair<size_t, size_t> delta);

bool isOutOfBounds(Garden *garden, Coord coord);

Tile *getTile(Garden *garden, Coord coord);

vector<Tile*> getAllNeighbours(Garden *garden, Tile *tile);

Tile *readCurrentTile(char dir, size_t y, size_t x, unsigned short val);

void updateMyCost(Garden* garden, Tile* tile);

Garden *readInput();

#endif //HW08_GARDEN_H
