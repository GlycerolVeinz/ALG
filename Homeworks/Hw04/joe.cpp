//
// Created by glycerolveinz on 28.11.23.
//


#include "joe.h"

void printGameField(GameField *gameField) {
    for (int col = 0; col <= gameField->colorCount; ++col) {
        cout << "\nColor: " << col << "\n";
        for (int y = 0; y < gameField->height; ++y) {
            for (int x = 0; x < gameField->width; ++x) {
                Coord coord;
                coord.x = x;
                coord.y = y;
                Tile *tile = getTile(gameField, &coord, col);

                if (tile->isKey) {
                    cout << "K ";
                } else if (tile->isWalkable) {
                    cout << "_ ";
                } else {
                    cout << tile->color << " ";
                }
            }
            cout << std::endl;
        }
    }
}

int main() {

    GameField *gameField = readGameField();
//    printGameField(gameField);

    int result = findPath(gameField);
    cout << result << std::endl;
    return 0;
}

void recursiveHelper(){

}

int findPathRecursive(GameField *gameField){
    Coord *currentCoord = gameField->joe->currentCoord;
    Coord *goalCoord = gameField->joe->goalCoord;
    int curKey = gameField->joe->curKey;

    auto *queue = new std::queue<Coord *>;
    auto *visited = new std::set<Coord *>;

}

int findPath(GameField *gameField) {
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

        for (auto neighbourCoord : getNeighbourCoords(gameField, current)) {
            Tile *neighbourTile = getTile(gameField, neighbourCoord, curKey);

            if (neighbourTile->wasVisited) continue;
            if (!neighbourTile->isWalkable) continue;
            if (neighbourTile->isKey) {
                curKey = neighbourTile->color;
                neighbourTile = getTile(gameField, neighbourCoord, curKey);
            }

            neighbourTile->algValues->gCost = currentTile->algValues->gCost + 1;
            queue->push(neighbourCoord);
        }
    }

    pathLength = getTile(gameField, goalCoord, curKey)->algValues->gCost;
    return pathLength;
}
