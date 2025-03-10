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
} AlgValues;

typedef struct {
    Coord coord;
    int color;
    int colorPlain;

    bool isWalkable;
    bool isKey;
    bool wasVisited;

//    int gCost;
    AlgValues algValues;
} Tile;

typedef struct {
    int width;
    int height;
    int colorCount;

    std::vector<std::vector<Tile>> allTiles;
    Joe joe;
} GameField;

#define UP_NEIGHBOUR {0, -1}
#define DOWN_NEIGHBOUR {0, 1}
#define LEFT_NEIGHBOUR {-1, 0}
#define RIGHT_NEIGHBOUR {1, 0}

/*
 * Gets the neighbour of the given tile in the given direction.
 * */
Tile *getNeighbour(GameField *gameField, Tile *tile, Coord delta);

/*
 * Gets all neighbours of the given tile.
 * */
std::vector<Tile *> getNeighbours(GameField *gameField, Tile *tile);

/*
 * Checks if the given coordinates are out of bounds.
 */
bool isOutOfBounds(GameField *gameField, Coord coord);

/*
 * Translates the given coordinates to the index in the allTiles vector.
 */
int coordToIndex(GameField *gameField, Coord coord);

/*
 * Returns the tile at the given coordinates and color.
 */
Tile *getTile(GameField *gameField, Coord coord, int color);

/*
 * Reads the game field from the input stream.
 * Returns the game field struct allocated.
 */
GameField readGameField();

/*
 * Checks if the given coordinates are equal.
 */
bool areEqualCoords(Coord coord1, Coord coord2);

/*
 * Calculates the heuristic for the given tile.
 * The heuristic is the manhattan distance between the tile and the goal.
 * use only in A* algorithm
 */
int calculateHeuristic(GameField *gameField, Tile *tile);

/*
 * Initializes a tile with the given x and y coordinates
 * and the color, that it reads from the input stream.
 */
Tile initTile(int x, int y, int color);

/*
 * Initializes the Joe struct with the given maxX and maxY values,
 * puts him on start position and sets the goal position.
 */
Joe initJoe(int maxX, int maxY);

/*
 * Initializes the gameField and its main attributes.
 * Also initializes Joe, and prepares colorTiles vector.
 * */
GameField initGameField(int maxY, int maxX, int c);

/*
 * Adds the given tile to the coloredTiles vector,
 * sets is walkable and is key.
 */
void addTileToColoredTiles(GameField *gameField, Tile tile, int curCol);


#endif //HW04_GAMEFIELD_H
