//
// Created by safor on 31.1.24.
//

#include "frog.h"

Field *readField() {
    int height, length;
    SpeedVal maxSpeed;
    cin >> height >> length >> maxSpeed;

    auto *f = new Field(height, length, maxSpeed);

    f->map.resize(4);
    f->map.at(0).resize(height);
    for (int y = 0; y < height; ++y) {
        f->map.at(0).at(y).resize(length);
        for (int x = 0; x < length; ++x) {
            SpeedVal input;
            cin >> input;

            Node *current = makeNode(y, x, 1, input);
            f->map.at(0).at(y).at(x) = current;
        }
    }

    for (int dir = 1; dir <= 3; ++dir) {
        vector<vector<Node *>> fieldCopy;
        for (int y = 0; y < height; ++y) {
            vector<Node *> row;
            for (int x = 0; x < length; ++x) {
                Node *n = f->map.at(0).at(y).at(x);
                row.push_back(
                        makeNode(n->coord.first, n->coord.second, dir, n->height));
            }
            fieldCopy.push_back(row);
        }
        f->map.at(dir) = fieldCopy;
    }

    return f;
}

Node *makeNode(int y, int x, SpeedVal dir, SpeedVal h) {
    auto *n = new Node;
    n->height = h;
    n->jumpDir = dir;
    n->coord.first = y;
    n->coord.second = x;

    n->visited = false;
    n->minPathLen = std::numeric_limits<size_t>::max();
    return n;
}

Field::Field(int height, int length, SpeedVal maxSpeed) {
    this->height = height;
    this->length = length;
    this->maxSpeed = maxSpeed;
    this->res = 0;
}

bool Field::isOutOfBounds(Coord coord) const {
    return coord.first < 0 ||
           coord.second < 0 ||
           coord.first >= this->height ||
           coord.second >= this->length;
}

Node *Field::getNode(Coord coord, SpeedVal dir) {
    if (isOutOfBounds(coord))
        return nullptr;
    return this->map.at(dir).at(coord.first).at(coord.second);
}

bool Frog::isValidJump(Jump jump) const {
    if (this->field->isOutOfBounds(jump.to))
        return false;

    bool validHeight = true;
    for (int i = 1; i <= jump.speed * 2; ++i){
        Coord pathCoord = jumpPath(jump.from->coord,dirNumToDelta(jump.direction),i);

        Node *pathNode = this->field->getNode(pathCoord,jump.direction);

//        TODO fix weird jumps
        auto aha = (abs(i) % jump.speed) + 1;
        if (pathNode->height > (aha)) {
            validHeight = false;
            break;
        }

        if (pathNode->height > jump.speed){
            validHeight = false;
            break;
        }
    }

    return validHeight;
}

Frog::Frog(Field *field, Coord start, Coord end) {
    this->start = start;
    this->end = end;
    this->field = field;
}

void Frog::addDestinations(std::queue<Jump> *q, Node *currentNode, Jump currentJump) const {
    for (auto dir : ALL_DIR_NUM){
        if (dir != currentJump.direction){
//            jump of speed 1 in all other directions
            Coord jumpDestSpeed1 = jumpCoord(currentNode->coord, dirNumToDelta(dir), 1);
            if (this->field->isOutOfBounds(jumpDestSpeed1))
                continue;

            Jump nJ = newJump(currentNode, jumpDestSpeed1, dir, 1);
            nJ.pathLen = currentJump.pathLen + 1;
            q->push(nJ);

        } else {
//            in main dir make jump of speed 1, and S+1, and S, and S-1
//            Coord jumpDestSpeed1 = std::make_pair(-1, -1);
            Coord jumpDestSpeed2 = std::make_pair(-1, -1);
            Coord jumpDestSpeed3 = std::make_pair(-1, -1);
            Coord jumpDestSpeed4 = std::make_pair(-1, -1);

//            jumpDestSpeed1 = jumpCoord(currentNode->coord, dirNumToDelta(dir), 1);

            if (currentJump.speed > 0) {
                jumpDestSpeed2 = jumpCoord(currentNode->coord, dirNumToDelta(dir), currentJump.speed - 1);
                jumpDestSpeed3 = jumpCoord(currentNode->coord, dirNumToDelta(dir), currentJump.speed);
            }

            if ((currentJump.speed + 1) <= (this->field->maxSpeed))
                jumpDestSpeed4 = jumpCoord(currentNode->coord, dirNumToDelta(dir), currentJump.speed + 1);

//            if (!this->field->isOutOfBounds(jumpDestSpeed1)) {
//                Jump nJ = newJump(currentNode, jumpDestSpeed1, dir, 1);
//                nJ.pathLen = currentJump.pathLen + 1;
//                q->push(nJ);
//            }

            if (!this->field->isOutOfBounds(jumpDestSpeed2)) {
                Jump nJ = newJump(currentNode, jumpDestSpeed2, dir, currentJump.speed - 1);
                nJ.pathLen = currentJump.pathLen + 1;
                q->push(nJ);
            }

            if (!this->field->isOutOfBounds(jumpDestSpeed3)) {
                Jump nJ = newJump(currentNode, jumpDestSpeed3, dir, currentJump.speed);
                nJ.pathLen = currentJump.pathLen + 1;
                q->push(nJ);
            }

            if (!this->field->isOutOfBounds(jumpDestSpeed4)) {
                Jump nJ = newJump(currentNode, jumpDestSpeed4, dir, currentJump.speed + 1);
                nJ.pathLen = currentJump.pathLen + 1;
                q->push(nJ);
            }
        }
    }
}

Jump newJump(Node *from, Coord to, SpeedVal direction, SpeedVal speed){
    Jump j;
    j.from = from;
    j.direction = direction;
    j.to = to;
    j.speed = speed;
    j.pathLen = 0;
    return j;
}

bool areEqualCords(Coord c1, Coord c2){
    return (c1.first == c2.first) &&
           (c1.second == c2.second);
}

pair<int,int> dirNumToDelta(int dirNum){
    pair<int,int> ret;

    switch (dirNum) {
        case UP_DIR_NUM:
            ret = UP_DIRECTION;
            break;
        case DOWN_DIR_NUM:
            ret = DOWN_DIRECTION;
            break;
        case LEFT_DIR_NUM:
            ret = LEFT_DIRECTION;
            break;
        case RIGHT_DIR_NUM:
            ret = RIGHT_DIRECTION;
            break;
        default:
            cerr << "something went wrong";
            ret = std::make_pair(0,0);
    }

    return  ret;
}

Coord jumpCoord(Coord cur, pair<int,int> dir, SpeedVal speed){
    return std::make_pair(cur.first + dir.first * 2 * speed,
                          cur.second + dir.second * 2 * speed);
}

Coord jumpPath(Coord cur, pair<int, int> movementDir, SpeedVal delta){
    return std::make_pair(cur.first + movementDir.first * delta,
                          cur.second + movementDir.second * delta);
}
