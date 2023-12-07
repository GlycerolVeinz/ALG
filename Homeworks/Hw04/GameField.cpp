//
// Created by glycerolveinz on 29.11.23.
//

#include "GameField.h"

GameField *readGameField() {
    int m, n, c;
    cin >> m >> n >> c;

    GameField *gameField = initGameField(m, n, c);

    for (int y = 0; y < m; ++y) {
        for (int x = 0; x < n; ++x) {
            int color;
            cin >> color;
            for (int col = 0; col < c; ++col) {
                Tile *tile = initTile(x, y, color);
                addTileToColoredTiles(gameField, tile, col);

            }
        }
    }

    return gameField;
}

bool areEqualCoords(Coord *coord1, Coord *coord2) {
    return (coord1->x == coord2->x && coord1->y == coord2->y);
}

int calculateHeuristic(GameField *gameField, Tile *tile) {
    int heuristic = 0;
    if (!areEqualCoords(tile->coord, gameField->joe->goalCoord)) {
        heuristic = abs(tile->coord->x - gameField->joe->goalCoord->x) +
                    abs(tile->coord->y - gameField->joe->goalCoord->y);
    }
    return heuristic;
}

Tile *initTile(int x, int y, int color) {
    auto tile = new Tile;
    auto coord = new Coord;
    auto algValues = new DStarLiteValues;

    tile->coord = coord;
    tile->algValues = algValues;

    tile->coord->x = x;
    tile->coord->y = y;
    tile->color = color;

    tile->algValues->gCost = std::numeric_limits<int>::max();
    tile->algValues->rhEstimate = std::numeric_limits<int>::max();
    tile->algValues->heuristic = std::numeric_limits<int>::max();

    return tile;
}

void initJoe(GameField *gameField, int maxX, int maxY) {
    auto joe = new Joe;
    auto currentCoord = new Coord;
    auto goalCoord = new Coord;
    joe->currentCoord = currentCoord;
    joe->goalCoord = goalCoord;

    joe->curKey = 0;
    joe->currentCoord->x = 0;
    joe->currentCoord->y = maxY - 1;
    joe->goalCoord->x = maxX - 1;
    joe->goalCoord->y = 0;
    gameField->joe = joe;
}

GameField *initGameField(int maxY, int maxX, int c) {
    auto gameField = new GameField;
    gameField->width = maxX;
    gameField->height = maxY;
    gameField->colorCount = c;

    initJoe(gameField, maxX, maxY);

    gameField->allTiles->resize(c + 1);
    return gameField;
}

void addTileToColoredTiles(GameField *gameField, Tile *tile, int curCol) {
    if (tile->color < 0) {
        tile->isKey = true;
        tile->isWalkable = true;
    } else if (tile->color == curCol) {
        tile->isKey = false;
        tile->isWalkable = true;
    } else {
        tile->isKey = false;
        tile->isWalkable = false;
    }

    gameField->allTiles->at(curCol).push_back(tile);
}

