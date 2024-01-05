#include "garden.h"

Coord getNeighbourCoord(Tile *tile, std::pair<int,int> delta){
    Coord neighbourCoord;
    neighbourCoord.y = tile->coord->y + delta.first;
    neighbourCoord.x = tile->coord->x + delta.second;

    return neighbourCoord;
}

bool isOutOfBounds(Garden *garden, Coord coord) {
    bool ret = false;
    if (coord.x < 0 || coord.x >= garden->width ||
        coord.y < 0 || coord.y >= garden->height)
        ret = true;

    return ret;
}

/*
 * Gets Tile* from coordinates
 * if coordinates are out of bounds
 *  returns nullptr!!
 * */
Tile *getTile(Garden *garden, Coord coord){
    if (isOutOfBounds(garden, coord))
        return nullptr;

    return garden->gardenMap.at(coord.y).at(coord.x);
}

/*
 * Returns all neighbours in vector
 * accounts for out of bounds, so that vector doesn't have nullptr
 * */
vector<Tile*> getAllNeighbours(Garden *garden, Tile *tile){
    vector<Tile*> neighbours;

    for (std::pair<int,int> neighbourCoordDelta : ALL_NEIGHBOURS){
        Coord newCoord = getNeighbourCoord(tile, neighbourCoordDelta);

        Tile *neighbour = getTile(garden, newCoord);
        if ( neighbour )
            neighbours.push_back(neighbour);
    }

    return neighbours;
}

Tile *readCurrentTile(size_t y, size_t x){
    auto *coord = new Coord;
    coord->y = y;
    coord->x = x;

    Tile *tile = new Tile;
    tile->coord = coord;
    int val;
    cin >> val;
    tile->plantValue = val;

    if (val > 0)
        tile->isPlant = true;
    else
        tile->isPlant = false;

    tile->cost = 0;
    tile->bestCostPerRoute = std::numeric_limits<long>::min();
    tile->shortestPathLength = std::numeric_limits<long>::min();

    return tile;
}

void updateMyCost(Garden* garden, Tile* tile){
    for (Tile *neighbour : getAllNeighbours(garden, tile)){
        tile->cost += neighbour->plantValue;
    }
}

Garden *readInput(){
    auto *garden = new Garden;
    cin >> garden->height >> garden->width;

    for (size_t y = 0; y < garden->height; ++y){
        vector<Tile *> row;
        for (size_t x = 0; x < garden->width; ++x){
            Tile *curTile = readCurrentTile(y, x);
            row.push_back(curTile);
        }
        garden->gardenMap.push_back(row);
    }

    return garden;
}

Tile *getLeftNeighbour(Garden *garden, Tile *tile){
    return getTile(garden, getNeighbourCoord(tile, LEFT_NEIGHBOUR));
}

Tile *getRightNeighbour(Garden *garden, Tile *tile){
    return getTile(garden, getNeighbourCoord(tile, RIGHT_NEIGHBOUR));
}

