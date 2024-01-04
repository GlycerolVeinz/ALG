#include "garden.h"

bool isOutOfBounds(Garden *garden, Coord *coord) {
    bool ret = false;
    if (coord->x < 0 || coord->x >= garden->width ||
        coord->y < 0 || coord->y >= garden->height)
        ret = true;

    return ret;
}

Tile *getTile(Garden *garden, Coord *coord){
    if (isOutOfBounds(garden, coord))
        return nullptr;

    return garden->gardenMap.at(coord->y).at(coord->x);
}


vector<Tile*> getAllNeighbours(Garden *garden, Tile *tile){
    vector<Tile*> neighbours;

    for (std::pair<int,int> neighbourCoord : ALL_NEIGHBOURS){
        Coord newCoord;
        newCoord.x = tile->coord->x + neighbourCoord.second;
        newCoord.y = tile->coord->y + neighbourCoord.first;

        Tile *neighbour = getTile(garden, &newCoord);
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

    return tile;
}

void updateNeighbourCosts(Garden* garden, Tile* tile){
    for (Tile *neighbour : getAllNeighbours(garden, tile)){
        neighbour->cost += tile->plantValue;
    }
}

void updateCosts(Garden *garden){
    for (const vector<Tile*>& row : garden->gardenMap){
        for (Tile *tile : row){
            if (tile->isPlant)
                updateNeighbourCosts(garden, tile);
        }
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

    updateCosts(garden);
    return garden;
}


