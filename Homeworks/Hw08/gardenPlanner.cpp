#include "garden.h"

void readFromTopTile(Garden *g, Coord coord);

void updateSideTiles(Garden *g, Coord coord);

// MAIN ================================================================================================================
int main() {
    Garden *g = readInput();

    for (size_t y = 0; y < g->height; ++y) {
        for (char direction = 0; direction < DIRECTIONS_COUNT; ++direction) {
            for (size_t x = 0; x < g->width; ++x) {
//                read from top
                readFromTopTile(g, makeCoord(direction, y, x));
//                go from the current tile all the way one direction
                updateSideTiles(g, makeCoord(direction, y, x));
            }
        }
    }

//    collect results
    std::pair<size_t, size_t> res = std::make_pair(0, std::numeric_limits<size_t>::max());
    for (char direction = 0; direction < DIRECTIONS_COUNT; ++direction) {
        for (auto tile: g->gardenMap.at(direction).at(g->height - 1)) {
            if (tile->bestCost > res.first) {
                res.first = tile->bestCost;
                res.second = tile->shortestPath;
            } else if (tile->bestCost == res.first && tile->shortestPath < res.second) {
                res.second = tile->shortestPath;
            }
        }
    }

    cout << res.first << " " << res.second << std::endl;

    delete g;
    return 0;
}
// EO MAIN =============================================================================================================

void decideValues(Tile *prev, Tile *next) {
    if (next->bestCost < prev->bestCost + next->cost) {
        next->bestCost = prev->bestCost + next->cost;
        next->shortestPath = prev->shortestPath + 1;

    } else if (next->bestCost == prev->bestCost + next->cost
               && next->shortestPath > prev->shortestPath + 1) {
        next->shortestPath = prev->shortestPath + 1;
    }
}

void readFromTopTile(Garden *g, Coord coord) {
    Tile *tile = getTile(g, coord);
    if (tile->isPlant)
        return;

    Tile *myDirUpper = getNeighbourTile(g, tile, UP_NEIGHBOUR);
    Coord oppositeDirCoord = *tile->coord;
    oppositeDirCoord.dir = tile->coord->dir == LEFT_DIR ? LEFT_DIR : RIGHT_DIR;
    Tile *oppositeDirUpper = getNeighbourTile(g, getTile(g, makeCoord(coord.dir, coord.y,coord.x)), UP_NEIGHBOUR);

    if (myDirUpper) {
//        get best value from both top directions
        decideValues(myDirUpper, tile);
        decideValues(oppositeDirUpper, tile);
    } else {
//        first row init
        if (tile->cost > tile->bestCost) {
            tile->bestCost = tile->cost;
        }
        tile->shortestPath = 1;
    }
}

void updateSideTiles(Garden *g, Coord coord) {
    Tile *tile = getTile(g, coord);
    if (tile->isPlant)
        return;

    std::pair<size_t, size_t> direction = coord.dir == LEFT_DIR ? LEFT_NEIGHBOUR : RIGHT_NEIGHBOUR;
    Tile *prev = tile;
    Tile *next = getNeighbourTile(g, tile, direction);
    while (next && !next->isPlant) {
        decideValues(prev, next);

        prev = next;
        next = getNeighbourTile(g, prev, direction);
    }
}
