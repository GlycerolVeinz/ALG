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
    int w,h;

    cin >> h >> w;

    auto *f = new Field(h, w);

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
            if (n->coord.second != 0)
                n->dangerSumHorizontal = row.at(x - 1)->dangerSumHorizontal + n->val;
//            look up, and add n.val + prev.partialSumVertical
            if (n->coord.first != 0)
                n->dangerSumVertical = fNodes.at(y - 1).at(x)->dangerSumVertical + n->val;

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
                    if (fNodes.at(y - 1).at(x)->val == 0) {
                        currentSector = fNodes.at(y - 1).at(x)->inSector;
                        ++currentSector->height;

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

Field::Field(int height, int width) {
    this->width = width;
    this->height = height;
}

BirdSector::BirdSector(Node *n) {
    this->width = 1;
    this->height = 1;
    this->leftCorner.first = n->coord.first;
    this->leftCorner.second = n->coord.second;
}
