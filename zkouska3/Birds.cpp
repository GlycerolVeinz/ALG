//
// Created by safor on 7.2.24.
//

#include "Birds.h"

Node *readVal(int y, int x) {
    auto *n = new Node;
    cin >> n->val;
    n->coord.first = y;
    n->coord.second = x;
    return n;
}

Field *Field::readField() {
    auto *f = new Field;

    cin >> f->height >> f->width;
    f->res = -1;

    vector<vector<Node *>> fNodes;
    vector<BirdSector *> sectors;

    for (int y = 0; y < f->height; ++y) {
        bool sectorMaking = false;
        vector<Node *> row;

        for (int x = 0; x < f->width; ++x) {
//          read val
            Node *n = readVal(y, x);

//          make partial summs
//            look to the left, and add n.val + prev.partialSumHorizontal
            if (n->coord.second != 0) {
                n->dangerSumHorizontal = row.at(x - 1)->dangerSumHorizontal + n->val;
                n->sectorsSumHorizontal = row.at(x - 1)->sectorsSumHorizontal;
                n->sectorNodesSumHorizontal = row.at(x - 1)->sectorNodesSumHorizontal;
            } else {
                n->dangerSumHorizontal = 0;
                n->sectorsSumHorizontal = 0;
                n->sectorNodesSumHorizontal = 0;
            }
//            look up, and add n.val + prev.partialSumVertical
            if (n->coord.first != 0) {
                n->dangerSumVertical = fNodes.at(y - 1).at(x)->dangerSumVertical + n->val;
                n->sectorsSumVertical = fNodes.at(y - 1).at(x)->sectorsSumVertical;
                n->sectorNodesSumVertical = fNodes.at(y - 1).at(x)->sectorNodesSumVertical;
            } else {
                n->dangerSumVertical = 0;
                n->sectorsSumVertical = 0;
                n->sectorNodesSumVertical = 0;
            }
//          if val == 0 -> start marking a new sector
//              remember pointer to sector, and all Y values
            if (n->val == 0) {
                BirdSector *currentSector;

                if (sectorMaking) {
//                adding to prev sector in row
                    currentSector = sectors.back();
                    ++currentSector->width;
                } else {
//                look up for sector
                    if ((n->coord.first != 0) && (fNodes.at(y - 1).at(x)->val == 0)) {
                        currentSector = fNodes.at(y - 1).at(x)->inSector;

                        currentSector->height = currentSector->height < y - currentSector->leftCorner.first + 1 ?
                                                y - currentSector->leftCorner.first + 1 : currentSector->height;
                    } else {
//                new sector
                        currentSector = new BirdSector(n);
                        sectors.push_back(currentSector);
                        sectorMaking = true;
                    }
                }

//                assign node to sector, and vice versa
                n->inSector = currentSector;
                currentSector->nodes.push_back(n);

                ++n->sectorNodesSumHorizontal;
                ++n->sectorNodesSumVertical;
            } else {
                sectorMaking = false;
            }

            row.push_back(n);
        }

        fNodes.push_back(row);
    }

    f->sectors = sectors;
    f->nodes = fNodes;
    return f;
}

void Field::printField() {
    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            cerr << this->nodes.at(y).at(x)->val << " ";
        }
        cerr << "\n";
    }
}

bool Field::coordOutOfBounds(Coord coord) {
    return (coord.first < 0) || (coord.first >= this->height) ||
           (coord.second < 0) || (coord.second >= this->width);
}

Node *Field::getNode(Coord coord) {
    Node *ret = nullptr;
    if (!this->coordOutOfBounds(coord)) {
        ret = this->nodes.at(coord.first).at(coord.second);
    }
    return ret;
}


BirdSector::BirdSector(Node *n) {
    this->width = 1;
    this->height = 1;
    this->leftCorner.first = n->coord.first;
    this->leftCorner.second = n->coord.second;
    ++n->sectorsSumVertical;
    ++n->sectorsSumHorizontal;
}
