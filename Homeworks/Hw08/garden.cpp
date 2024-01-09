#include "garden.h"

Coord getNeighbourCoord(Tile *tile, std::pair<size_t ,size_t> delta){
    Coord neighbourCoord;
    neighbourCoord.y = tile->coord->y + delta.first;
    neighbourCoord.x = tile->coord->x + delta.second;
    neighbourCoord.dir = tile->coord->dir;

    return neighbourCoord;
}

Tile *getNeighbourTile(Garden *garden, Tile *tile, std::pair<size_t, size_t> delta){
    return getTile(garden, getNeighbourCoord(tile, delta));
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

    return garden->gardenMap.at(coord.dir).at(coord.y).at(coord.x);
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

Tile *readCurrentTile(char dir, size_t y, size_t x, unsigned short val){
    auto *coord = new Coord;
    coord->dir = dir;
    coord->y = y;
    coord->x = x;

    Tile *tile = new Tile;
    tile->coord = coord;

    tile->plantValue = val;
    tile->isPlant = (val > 0);

    tile->cost = 0;
    tile->bestCost = std::numeric_limits<long>::min();
    tile->shortestPath = std::numeric_limits<long>::min();

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

    garden->gardenMap.resize(DIRECTIONS_COUNT);

    garden->gardenMap.at(LEFT_DIR).resize(garden->height);
    for (size_t y = 0; y < garden->height; ++y){

        garden->gardenMap.at(LEFT_DIR).at(y).resize(garden->width);
        for (size_t x = 0; x < garden->width; ++x){
            int val;
            cin >> val;
            Tile *curTile = readCurrentTile(LEFT_DIR, y, x, val);
            garden->gardenMap[LEFT_DIR][y][x] = curTile;
        }
    }

    garden->gardenMap.at(RIGHT_DIR).resize(garden->height);
    for (const auto& row : garden->gardenMap.at(LEFT_DIR)){
        garden->gardenMap.at(RIGHT_DIR).at(row.at(0)->coord->y).resize(garden->width);
        for (auto tile : row){
            updateMyCost(garden, tile);
            Tile *copyTile = readCurrentTile(RIGHT_DIR, tile->coord->y, tile->coord->x, tile->plantValue);
            copyTile->cost = tile->cost;
            garden->gardenMap[RIGHT_DIR][tile->coord->y][tile->coord->x] = copyTile;
        }
    }

    return garden;
}

Coord coord(char dir, size_t y, size_t x){
    Coord c;
    c.dir = dir;
    c.y = y;
    c.x = x;
    return c;
}
