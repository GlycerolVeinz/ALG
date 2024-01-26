#include "garden.h"

void checkAllPathsRecursively(Garden *g, Tile *t);
void updateTileBelow(Garden *g, Tile *t);
void checkForBetterPath(Tile *prev, Tile *next);
void goRecursive(Garden *g, Tile *t, Tile *(*nextTile)(Garden*, Tile*));

// MAIN ================================================================================================================
int main(){
    Garden *g = readInput();

    for (Tile *t : g->gardenMap.at(0)){
        updateMyCost(g, t);
        t->shortestPathLength = 1;
        t->bestCostPerRoute = t->cost;

        checkAllPathsRecursively(g, t);
    }

//   get the best result
    size_t resCost = 0;
    size_t resLength = std::numeric_limits<long>::max();
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

void checkAllPathsRecursively(Garden *g, Tile *t) {
    goRecursive(g, t, getLeftNeighbour);
    goRecursive(g, t, getRightNeighbour);
    updateTileBelow(g, t);
}

void goRecursive(Garden *g, Tile *t, Tile *(*nextTile)(Garden*, Tile*)) {
    if (!t || t->isPlant){
        return;
    }

    Tile *next = nextTile(g, t);
    if (next && !next->isPlant){
        updateMyCost(g, next);
        checkForBetterPath(next, t);
        goRecursive(g, next, nextTile);
    }
}

void updateTileBelow(Garden *g, Tile *t) {
    if (!t || t->isPlant){
        return;
    }

    Tile *below = getLowerNeighbour(g, t);
    if (below && !below->isPlant){
        updateMyCost(g, below);
        checkForBetterPath(t, below);
        checkAllPathsRecursively(g, below);
    }
}

void checkForBetterPath(Tile *prev, Tile *next) {
    if (next->bestCostPerRoute < prev->bestCostPerRoute + next->cost){
        next->bestCostPerRoute = prev->bestCostPerRoute + next->cost;
        next->shortestPathLength = prev->shortestPathLength + 1;

    } else if (next->bestCostPerRoute == prev->bestCostPerRoute + next->cost){
        if (next->shortestPathLength > prev->shortestPathLength + 1){
            next->shortestPathLength = prev->shortestPathLength + 1;
        }

    } else {
        return;
    }
}
