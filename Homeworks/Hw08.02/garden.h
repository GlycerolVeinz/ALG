#ifndef HW08_02_GARDEN_H
#define HW08_02_GARDEN_H

#include <iostream>
#include <vector>
#include <limits>

using std::cin;
using std::cout;
using std::vector;
using std::pair;

/*
 * first == Y, second == X
 * */
typedef pair<size_t, size_t> Coord;

#define UP_NEIGHBOUR Coord(-1, 0)
#define DOWN_NEIGHBOUR Coord(1, 0)
#define LEFT_NEIGHBOUR Coord(0, -1)
#define RIGHT_NEIGHBOUR Coord(0, 1)
#define ALL_NEIGHBOURS {UP_NEIGHBOUR, DOWN_NEIGHBOUR, LEFT_NEIGHBOUR, RIGHT_NEIGHBOUR}

typedef struct {
    size_t width;
    size_t height;
    vector<vector<size_t>> map;
    vector<vector<size_t>> costs;
    vector<vector<size_t>> shortestPaths;
    vector<vector<size_t>> bestCosts;
} Garden;

Garden readGarden();

bool isOutOfBounds(Garden *g, Coord tile);
bool isPlant(Garden *g, Coord tile);

bool isBetterPath(Garden *g, Coord prev, Coord next);
bool isShorterPath(Garden *g, Coord prev, Coord next);
void setBetterPath(Garden *g, Coord prev, Coord next);
void setShorterPath(Garden *g, Coord prev, Coord next);

Coord getTile(Coord tile, pair<size_t, size_t> delta);

/*
 * Only for the first row of tiles
 * */
void initTile(Garden *g, pair<size_t, size_t> coord);
void updateCost(Garden *g, Coord tile);

#endif //HW08_02_GARDEN_H
