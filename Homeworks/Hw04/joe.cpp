//
// Created by glycerolveinz on 28.11.23.
//

#include "joe.h"

int main() {

    GameField *gameField = readGameField();
    int result = findPath(gameField);


    return 0;
}

int findPath(GameField *gameField) {
    int pathLength = 0;
//  find path using BFS algorithm

    Coord *currentCoord = gameField->joe->currentCoord;
    Coord *goalCoord = gameField->joe->goalCoord;
    int curKey = gameField->joe->curKey;

    auto *queue = new std::queue<Coord *>;

    queue->push(currentCoord);

    while (!queue->empty()) {
        Coord *current = queue->front();
        queue->pop();

//        END of algorithm
        if (areEqualCoords(current, goalCoord)) {
            break;
        }

        Tile *currentTile = getTile(gameField, current, curKey);
        currentTile->wasVisited = true;



    }

    return pathLength;
}
