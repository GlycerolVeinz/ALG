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
                Tile *tile = getTile(gameField, coord, col);

                if (tile->isKey) {
                    cout << tile->color << " ";
                } else if (tile->isWalkable) {
                    cout << "_ ";
                } else {
                    cout << "# ";
                }
            }
            cout << "\n";
        }
    }
    cout << std::endl;
}

int main() {

    GameField gameField = readGameField();
//    printGameField(&gameField);

    int result = findPath(&gameField);
    cout << result << std::endl;

    return 0;
}

int findPath(GameField *gameField) {
//  find path using BFS algorithm

    Coord startCoord = gameField->joe.currentCoord;
    Coord goalCoord = gameField->joe.goalCoord;
    auto startTile = getTile(gameField, startCoord, gameField->joe.curKey);
    startTile->algValues.gCost = 0;

    std::priority_queue<Tile *, std::vector<Tile *>, TileComparator> queue;
    queue.push(startTile);

    Tile *currentTile;
    while (!queue.empty()) {
        currentTile = queue.top();
        queue.pop();

//        END of algorithm
        if (areEqualCoords(currentTile->coord, goalCoord)){
//            cout << "\nFound goal!" << std::endl;
            break;
        }

        currentTile->wasVisited = true;

        for (auto neighbourTile : getNeighbours(gameField, currentTile)) {
            if (neighbourTile->wasVisited) continue;
            if (!neighbourTile->isWalkable) continue;
//            printMove(currentTile, neighbourTile);
            if (neighbourTile->isKey) {
                neighbourTile = getTile(gameField, neighbourTile->coord, neighbourTile->color);
            }

            neighbourTile->algValues.gCost = currentTile->algValues.gCost + 1;
            queue.push(neighbourTile);
        }
    }

    int pathLength = currentTile->algValues.gCost;
    return pathLength;
}

void printMove(Tile *from, Tile *to){
    cout << "Current: " << from->coord.x << " " << from->coord.y << " " << from->colorPlain;
    cout << " -> ";
    cout << "Next: " << to->coord.x << " " << to->coord.y << " " << to->colorPlain << "\n";
}

