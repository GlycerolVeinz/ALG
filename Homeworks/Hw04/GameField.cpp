//
// Created by glycerolveinz on 29.11.23.
//

#include "GameField.h"

GameField readGameField() {
    int m, n, c;
    cin >> m >> n >> c;

    GameField gameField = initGameField(m, n, c);

    for (int y = 0; y < m; ++y) {
        for (int x = 0; x < n; ++x) {
            int color;
            cin >> color;
            for (int col = 0; col <= c; ++col) {
                Tile tile = initTile(x, y, color);
                addTileToColoredTiles(&gameField, tile, col);
            }
        }
    }

    return gameField;
}

Tile *getNeighbour(GameField *gameField, Tile *tile, Coord delta) {
    Coord neighbourCoord = {tile->coord.x + delta.x, tile->coord.y + delta.y};
    if (isOutOfBounds(gameField, neighbourCoord)) {
        return nullptr;
    }
    Tile *neighbour = getTile(gameField, neighbourCoord, tile->colorPlain);
    return neighbour;
}

std::vector<Tile *> getNeighbours(GameField *gameField, Tile *tile) {
    std::vector<Tile *> neighbourCoords;

    Tile *left = getNeighbour(gameField, tile, LEFT_NEIGHBOUR);
    Tile *right = getNeighbour(gameField, tile, RIGHT_NEIGHBOUR);
    Tile *up = getNeighbour(gameField, tile, UP_NEIGHBOUR);
    Tile *down = getNeighbour(gameField, tile, DOWN_NEIGHBOUR);

    if (left != nullptr) {
        neighbourCoords.push_back(left);
    }
    if (right != nullptr) {
        neighbourCoords.push_back(right);
    }
    if (up != nullptr) {
        neighbourCoords.push_back(up);
    }
    if (down != nullptr) {
        neighbourCoords.push_back(down);
    }

    return neighbourCoords;
}

bool isOutOfBounds(GameField *gameField, Coord coord) {
    return (coord.x < 0 || coord.x >= gameField->width ||
            coord.y < 0 || coord.y >= gameField->height);
}

int coordToIndex(GameField *gameField, Coord coord) {
    return (coord.x + coord.y * gameField->width);
}

Tile *getTile(GameField *gameField, Coord coord, int color) {
    return &(gameField->allTiles.at(color).at(coordToIndex(gameField, coord)));
}

bool areEqualCoords(Coord coord1, Coord coord2) {
    return (coord1.x == coord2.x && coord1.y == coord2.y);
}

int calculateHeuristic(GameField *gameField, Tile *tile) {
    int heuristic = 0;
    if (!areEqualCoords(tile->coord, gameField->joe.goalCoord)) {
        heuristic = abs(tile->coord.x - gameField->joe.goalCoord.x) +
                    abs(tile->coord.y - gameField->joe.goalCoord.y);
    }
    return heuristic;
}

Tile initTile(int x, int y, int color) {
    Tile tile;

    tile.coord.x = x;
    tile.coord.y = y;
    tile.color = color;
//    tile->gCost = std::numeric_limits<int>::max();

    tile.algValues.gCost = std::numeric_limits<int>::max();
    tile.algValues.rhEstimate = std::numeric_limits<int>::max();
    tile.algValues.heuristic = std::numeric_limits<int>::max();

    return tile;
}

Joe initJoe(int maxX, int maxY) {
    Joe joe;
    joe.curKey = 0;
    joe.currentCoord.x = 0;
    joe.currentCoord.y = maxY - 1;

    joe.goalCoord.x = maxX - 1;
    joe.goalCoord.y = 0;
    return joe;
}

GameField initGameField(int maxY, int maxX, int c) {
    GameField gameField;
    gameField.width = maxX;
    gameField.height = maxY;
    gameField.colorCount = c;

    gameField.joe = initJoe(maxX, maxY);

    std::vector<std::vector<Tile>> allTiles;
    gameField.allTiles = allTiles;
    gameField.allTiles.resize(c + 1);
    return gameField;
}

void addTileToColoredTiles(GameField *gameField, Tile tile, int curCol) {
    if (tile.color < 0) {
        tile.isKey = true;
        tile.isWalkable = true;
        tile.color = abs(tile.color);
    } else if (tile.color == curCol || tile.color == 0) {
        tile.isKey = false;
        tile.isWalkable = true;
    } else {
        tile.isKey = false;
        tile.isWalkable = false;
    }

    tile.colorPlain = curCol;
    tile.wasVisited = false;
    gameField->allTiles.at(curCol).push_back(tile);
}

