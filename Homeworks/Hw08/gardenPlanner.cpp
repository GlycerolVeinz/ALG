#include "garden.h"

void decideValues(Tile *prev, Tile *next);

void readFromTop(Garden *g, Tile *t);

void readFromPrevInDir(Garden *g, Tile* t, std::pair<int,int> readFrom);

// MAIN ================================================================================================================
int main() {
    Garden *g = readInput();

    for (size_t y = 0; y < g->height; ++y) {
//        movement to right
        for (Tile *rT : g->gardenMap.at(RIGHT_DIR).at(y)) {
            if (rT->isPlant)
                continue;

            readFromTop(g, rT);
            readFromPrevInDir(g, rT, LEFT_NEIGHBOUR);
        }

        auto leftDirRow = g->gardenMap.at(LEFT_DIR).at(y);
//        movement to left
        for ( auto rIt = leftDirRow.rbegin(); rIt != leftDirRow.rend(); ++rIt){
            Tile *tile = *rIt;
            if (tile->isPlant)
                continue;

            readFromTop(g, tile);
            readFromPrevInDir(g, tile, RIGHT_NEIGHBOUR);
        }
    }

    std::pair<size_t, size_t> res = std::make_pair(0, std::numeric_limits<size_t>::max());
    for (auto dir : {LEFT_DIR, RIGHT_DIR}){
        for (auto t : g->gardenMap.at(dir).at(g->height - 1)){
            if (t->bestCost > res.first){
                res.first = t->bestCost;
                res.second = t->shortestPath;
            } else if (t->bestCost == res.first && t->shortestPath < res.second){
                res.second = t->shortestPath;
            }
        }
    }

    cout << res.first << " " << res.second << std::endl;

    delete g;
    return 0;
}
// EO MAIN =============================================================================================================

void initFirstLineTile(Tile *tile) {
    tile->bestCost = tile->cost;
    tile->shortestPath = 1;
}

void decideValues(Tile *prev, Tile *next) {
    if (next->bestCost < prev->bestCost + next->cost) {
        next->bestCost = prev->bestCost + next->cost;
        next->shortestPath = prev->shortestPath + 1;

    } else if (next->bestCost == prev->bestCost + next->cost
               && prev->shortestPath + 1 < next->shortestPath) {
        next->shortestPath = prev->shortestPath + 1;
    }
}

void readFromTop(Garden *g, Tile *t){
    Tile *lTopTile = getTile(g, getNeighbourCoord(t, LEFT_DIR, UP_NEIGHBOUR));
    Tile *rTopTile = getTile(g, getNeighbourCoord(t, RIGHT_DIR, UP_NEIGHBOUR));

    if ( !lTopTile ) {
        initFirstLineTile(t);
    } else if ( !lTopTile->isPlant ) {
        decideValues(lTopTile, t);
        decideValues(rTopTile, t);
    }
}

void readFromPrevInDir(Garden *g, Tile* t, std::pair<int,int> readFrom){
    Tile *prev = getNeighbourTile(g, t, readFrom);

    if ( prev && !prev->isPlant ){
        decideValues(prev, t);
    }
}
