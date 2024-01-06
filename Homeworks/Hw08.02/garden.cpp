#include "garden.h"

Garden readGarden(){
    Garden g;
    cin >> g.width >> g.height;

    for (size_t i = 0; i < g.height; ++i){
        vector<size_t> mapRow;
        vector<size_t> costsRow;
        vector<size_t> shortestPathsRow;
        vector<size_t> bestCostsRow;

        for (size_t j = 0; j < g.width; ++j){
            size_t cost;
            cin >> cost;
            mapRow.push_back(cost);
            costsRow.push_back(0);
            shortestPathsRow.push_back(std::numeric_limits<size_t>::max());
            bestCostsRow.push_back(0);
        }

        g.map.push_back(mapRow);
        g.costs.push_back(costsRow);
        g.shortestPaths.push_back(shortestPathsRow);
        g.bestCosts.push_back(bestCostsRow);
    }

    return g;
}

bool isOutOfBounds(Garden *g, Coord tile){
    bool ret = true;
    if (tile.first < g->height && tile.second < g->width
    && tile.first >= 0 && tile.second >= 0)
        ret = false;

    return ret;
}

vector<Coord> getNeighbors(Garden *g, Coord tile){
    vector<Coord> neighbors;
    for ( Coord delta : ALL_NEIGHBOURS ) {
        Coord neighbor = getTile(tile, delta);
        if (!isOutOfBounds(g, neighbor)){
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

void updateCost(Garden *g, Coord tile){
    for (Coord neighbor: getNeighbors(g, tile)) {
        g->costs[tile.first][tile.second] += g->map[neighbor.first][neighbor.second];
    }
}

bool isPlant(Garden *g, Coord tile){
    bool ret = false;
    if (g->map[tile.first][tile.second] != 0)
        ret = true;

    return ret;
}

bool isBetterPath(Garden *g, Coord prev, Coord next){
    bool ret = false;
    if (g->bestCosts[next.first][next.second] < g->bestCosts[prev.first][prev.second] + g->costs[next.first][next.second]){
        ret = true;
    }

    return ret;
}

bool isShorterPath(Garden *g, Coord prev, Coord next){
    bool ret = false;
    if (g->bestCosts[next.first][next.second] == g->bestCosts[prev.first][prev.second] + g->costs[next.first][next.second]
    && g->shortestPaths[next.first][next.second] > g->shortestPaths[prev.first][prev.second] + 1){
        ret = true;
    }
    return ret;
}

void setShorterPath(Garden *g, Coord prev, Coord next){
    g->shortestPaths[next.first][next.second] = g->shortestPaths[prev.first][prev.second] + 1;
}

void setBetterPath(Garden *g, Coord prev, Coord next){
    g->bestCosts[next.first][next.second] = g->bestCosts[prev.first][prev.second] + g->costs[next.first][next.second];
    g->shortestPaths[next.first][next.second] = g->shortestPaths[prev.first][prev.second] + 1;
}

void initTile(Garden *g, Coord tile){
    updateCost(g, tile);
    g->shortestPaths[tile.first][tile.second] = 1;
    g->bestCosts[tile.first][tile.second] = g->costs[tile.first][tile.second];
}

Coord getTile(Coord tile, pair<size_t, size_t> delta){
    return std::make_pair(tile.first + delta.first, tile.second + delta.second);
}
