#include "garden.h"

pair<size_t, size_t> checkAllPathsRecursive(Garden *g, Coord tile);

void goRecursive(Garden *g, Coord tile, pair<size_t, size_t> delta);

void goDown(Garden *g, Coord tile);

void checkForBetterPath(Garden *g, Coord prev, Coord next);

int main(){
    Garden g = readGarden();

    pair <size_t,size_t> bestRes = {0, std::numeric_limits<size_t>::max()};
    for (Coord tile = Coord(0, 0); tile.second < g.width; ++tile.second) {
        if (isPlant(&g, tile))
            continue;

        initTile(&g, tile);
        pair<size_t,size_t> lastRes = checkAllPathsRecursive(&g, tile);

        if (lastRes.first <= bestRes.first )
            bestRes = lastRes;
    }

    cout << bestRes.first << " " << bestRes.second << std::endl;
    return 0;
}

pair<size_t, size_t> checkAllPathsRecursive(Garden *g, Coord tile) {
    goRecursive(g, tile, LEFT_NEIGHBOUR);
    goRecursive(g, tile, RIGHT_NEIGHBOUR);
    goDown(g, tile);

//    get result
    pair<size_t, size_t> res = {0, std::numeric_limits<size_t>::max()};
    for (size_t i = 0; i < g->width; ++i) {
        if (g->bestCosts[g->height - 1][i] < res.first){
            res.first = g->bestCosts[g->height - 1][i];
            res.second = g->shortestPaths[g->height - 1][i];
        } else if (g->bestCosts[g->height - 1][i] == res.first
                   && g->shortestPaths[g->height - 1][i] < res.second){
            res.second = g->shortestPaths[g->height - 1][i];
        }
    }

    return res;
}

void goDown(Garden *g, Coord tile) {
    if (isOutOfBounds(g, tile) || isPlant(g, tile))
        return;

    Coord nextTile = getTile(tile, DOWN_NEIGHBOUR);
    if (!isOutOfBounds(g, nextTile) || !isPlant(g, nextTile)){
        if (g->costs[nextTile.first][nextTile.second] == 0)
            updateCost(g, nextTile);
        checkForBetterPath(g, tile, nextTile);
        checkAllPathsRecursive(g, nextTile);
    }
}

void goRecursive(Garden *g, Coord tile, pair<size_t, size_t> delta) {
    if (isOutOfBounds(g, tile) || isPlant(g, tile))
        return;

    Coord nextTile = getTile(tile, delta);
    if (!isOutOfBounds(g, nextTile) || !isPlant(g, nextTile)){
        if (g->costs[nextTile.first][nextTile.second] == 0)
            updateCost(g, nextTile);
        checkForBetterPath(g, tile, nextTile);
        goRecursive(g, nextTile, delta);
    }
}

void checkForBetterPath(Garden *g, Coord prev, Coord next) {
    if (isBetterPath(g, prev, next)){
        setBetterPath(g, prev, next);
    } else if (isShorterPath(g, prev, next)){
        setShorterPath(g, prev, next);
    } else {
        return;
    }
}
