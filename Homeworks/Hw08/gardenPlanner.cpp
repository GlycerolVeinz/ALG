#include "garden.h"

void updateTileBasedOnUpper(Garden *garden, Tile *tile);
void updateNextInRowFromTile(Garden *garden, Tile *tile, Tile *(*nextTile)(Garden*, Tile*));

// MAIN ================================================================================================================
int main(){
    Garden *g = readInput();

    for (const vector<Tile *>& row : g->gardenMap) {
        for (Tile *t: row) {
            updateTileBasedOnUpper(g, t);

//          2. for each t iterate left and right
//              go all the way left
            updateNextInRowFromTile(g, t, getLeftNeighbour);
//              go all the way right
            updateNextInRowFromTile(g, t, getRightNeighbour);
        }
    }

//    5. get the best result
    long resCost = 0;
    long resLength = std::numeric_limits<long>::max();
    for (Tile *t : g->gardenMap.at(g->height - 1)){
        if (t->bestCostPerRoute > resCost){
            resCost = t->bestCostPerRoute;
            if (t->shortestPathLength < resLength)
                resLength = t->shortestPathLength;
        }
    }

    cout << resCost << " " << resLength << std::endl;

    delete g;
    return 0;
}
// EO MAIN =============================================================================================================

void updateTileBasedOnUpper(Garden *garden, Tile *tile){
    if (!tile->isPlant){
        updateMyCost(garden, tile);
        tile->bestCostPerRoute = tile->cost;

        Coord upperCoord = getNeighbourCoord(tile, UP_NEIGHBOUR);
        Tile* upperTile = getTile(garden, upperCoord);

        if ( upperTile ){
//            2. update based on previous line
            tile->shortestPathLength = upperTile->shortestPathLength + 1;
            tile->bestCostPerRoute += upperTile->bestCostPerRoute;
        } else {
//            1. initialize first row
            tile->shortestPathLength = 1;
        }
    }
}


void updateNextInRowFromTile(Garden *garden, Tile *tile, Tile *(*nextTile)(Garden*, Tile*)){
    Tile *next = nextTile(garden, tile);
    Tile *prev = tile;

    while (next && !next->isPlant){
        if (next->bestCostPerRoute == prev->bestCostPerRoute + next->cost
            && next->shortestPathLength > prev->shortestPathLength + 1)
            next->shortestPathLength = prev->shortestPathLength + 1;

        else if (next->bestCostPerRoute < prev->bestCostPerRoute + next->cost){
            next->bestCostPerRoute = prev->bestCostPerRoute + next->cost;
            next->shortestPathLength = prev->shortestPathLength + 1;
            prev = next;
            next = nextTile(garden, next);

        } else {
            break;
        }
    }
}

