#include "garden.h"

void readFromTopTile(Garden *g, Coord coord);

void updateSideTiles(Garden *g, Coord coord);

// MAIN ================================================================================================================
int main(){
    Garden *g = readInput();

    for (char direction = 0; direction < DIRECTIONS_COUNT; ++direction) {
        for (size_t y = 0; y < g->height; ++y) {
            for (size_t x = 0; x < g->width; ++x) {
//                read from top
                readFromTopTile(g, coord(direction, y, x));
//                go from the current tile all the way one direction
                updateSideTiles(g, coord(direction, y, x));
            }
        }
    }

//    collect results

    delete g;
    return 0;
}
// EO MAIN =============================================================================================================

void decideValues(Tile *prev, Tile *next){
    if (next->bestCost < prev->bestCost + next->cost){
        next->bestCost = prev->bestCost + next->cost;
        next->shortestPath = prev->shortestPath + 1;
    } else if (next->bestCost == prev->bestCost + next->cost
            && next->shortestPath > prev->shortestPath + 1){
        next->shortestPath = prev->shortestPath + 1;
    }
}

void readFromTopTile(Garden *g, Coord coord) {
    Tile *tile = getTile(g, coord);
    if (tile->isPlant)
        return;

    Tile *upperTile = getNeighbourTile(g, tile, UP_NEIGHBOUR);
    if (upperTile){
        decideValues(upperTile, tile);
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


}


