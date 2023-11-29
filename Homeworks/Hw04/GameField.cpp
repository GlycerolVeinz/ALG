//
// Created by glycerolveinz on 29.11.23.
//

#include "GameField.h"

GameField readGameField() {
    int m, n, c;
    cin >> m >> n >> c;

    GameField gameField;
    initGameField(&gameField, m, n, c);

    for (int y = 0; y < m; ++y) {
        for (int x = 0; x < n; ++x) {
            Tile tile;
            initTile(&tile, x, y);

            tile.algValues.heuristic = calculateHeuristic(&tile, &gameField);

            gameField.allTiles.push_back(tile);
            addTileToColoredTiles(tile, &gameField);
        }
    }

    return gameField;
}

bool areEqualCoords(Coord coord1, Coord coord2) {
    return (coord1.x == coord2.x && coord1.y == coord2.y);
}

int calculateHeuristic(Tile *tile, GameField *gameField) {
    int heuristic = 0;
    if (!areEqualCoords(tile->coord, gameField->joe.goalCoord)) {
        heuristic = abs(tile->coord.x - gameField->joe.goalCoord.x) + abs(tile->coord.y - gameField->joe.goalCoord.y);
    }
    return heuristic;
}

void initTile(Tile *tile, int x, int y) {
    tile->coord.x = x;
    tile->coord.y = y;
    cin >> tile->color;

    tile->algValues.gCost = std::numeric_limits<int>::max();
    tile->algValues.rhEstimate = std::numeric_limits<int>::max();
    tile->algValues.heuristic = std::numeric_limits<int>::max();
}

void initJoe(GameField *gameField, int maxX, int maxY){
    gameField->joe.curKey = 0;
    gameField->joe.currentCoord.x = 0;
    gameField->joe.currentCoord.y = maxY - 1;
    gameField->joe.goalCoord.x = maxX - 1;
    gameField->joe.goalCoord.y = 0;

}

void initGameField(GameField *gameField, int maxY, int maxX, int c) {
    gameField->width = maxX;
    gameField->height = maxY;
    gameField->colorCount = c;

    initJoe(gameField, maxX, maxY);

    gameField->coloredTiles.resize(c + 1);
}

void addTileToColoredTiles(Tile tile, GameField *gameField) {
    if (tile.color < 0){
        tile.isWalkable = true;
        tile.isKey = true;
        tile.color = -tile.color;
    } else if (tile.color == 0) {
        tile.isWalkable = true;
        tile.isKey = false;
    } else {
        tile.isWalkable = false;
        tile.isKey = false;
    }


    gameField->coloredTiles.at(tile.color).push_back(tile);
}

