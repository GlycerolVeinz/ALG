//
// Created by glycerolveinz on 29.11.23.
//

#ifndef HW04_GAMEFIELD_H
#define HW04_GAMEFIELD_H

#include <iostream>
#include <vector>
#include <limits>

using std::cout;
using std::cin;


typedef struct{
    int x;
    int y;
} Coord;

typedef struct {
    Coord currentCoord;
    Coord goalCoord;
    int curKey;
} Joe;

typedef struct{
    int gCost;
    int rhEstimate;
    int heuristic;
} DStarLiteValues;

typedef struct {
    Coord coord;
    int color;

    bool isWalkable;
    bool isKey;

    DStarLiteValues algValues;
} Tile;

typedef struct {
    int width;
    int height;
    int colorCount;

    std::vector<std::vector<Tile>> coloredTiles;
    std::vector<Tile> allTiles;

    Joe joe;
} GameField;

GameField readGameField();

/*
 * Checks if the given coordinates are equal.
 */
bool areEqualCoords(Coord coord1, Coord coord2);

/*
 * Calculates the heuristic for the given tile.
 * The heuristic is the manhattan distance between the tile and the goal.
 */
int calculateHeuristic(Tile *tile, GameField *gameField);

/*
 * Initializes a tile with the given x and y coordinates
 * and the color, that it reads from the input stream.
 */
void initTile(Tile *tile, int x, int y);

/*
 * Initializes the Joe struct with the given maxX and maxY values,
 * puts him on start position and sets the goal position.
 */
void initJoe(GameField *gameField, int maxX, int maxY);

/*
 * Initializes the gameField and its main attributes.
 * Also initializes Joe, and prepares colorTiles vector.
 * */
void initGameField(GameField *gameField, int maxY, int maxX, int c);

/*
 * Adds the given tile to the coloredTiles vector,
 * sets is walkable and is key.
 */
void addTileToColoredTiles(Tile tile, GameField *gameField);


#endif //HW04_GAMEFIELD_H
