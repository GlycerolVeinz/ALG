#include "garden.h"

void updateTileBasedOnUpper(Garden *garden, Tile *tile){
    if (!tile->isPlant){
        updateMyCost(garden, tile);
        tile->bestCostPerRoute = tile->cost;

        Coord upperCoord = getNeighbourCoord(tile, UP_NEIGHBOUR);
        Tile* upperTile = getTile(garden, &upperCoord);

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


int main(){
    Garden *garden = readInput();

//    4. repeat 2. and 3. until you get to the last row
//    5. get the best result

    for (const vector<Tile *>& row : garden->gardenMap){
        for (Tile *tile : row){
            updateTileBasedOnUpper(garden, tile);

//          2. for each tile iterate left and right
//              go all the way left
//              go all the way right

        }
    }

    delete garden;
    return 0;
}
