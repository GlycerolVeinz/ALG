//
// Created by safor on 31.1.24.
//

#ifndef ZKOUSKA_FROG_H
#define ZKOUSKA_FROG_H

#include <iostream>
#include <vector>
#include <limits>
#include <queue>

#define UP_DIR_NUM 0
#define DOWN_DIR_NUM 1
#define LEFT_DIR_NUM 2
#define RIGHT_DIR_NUM 3
#define ALL_DIR_NUM {0, 1, 2, 3}

#define UP_DIRECTION {-1, 0}
#define DOWN_DIRECTION {1, 0}
#define LEFT_DIRECTION {0, -1}
#define RIGHT_DIRECTION {0, 1}
#define ALL_DIRECTIONS {UP_DIRECTION, DOWN_DIRECTION, LEFT_DIRECTION, RIGHT_DIRECTION};

using std::vector;
using std::pair;
using std::cin;
using std::cout;
using std::cerr;

typedef unsigned short SpeedVal;

/*
 * first = y, second = x
 * */
typedef pair<int,int> Coord;

typedef struct {
    Coord coord;
    SpeedVal jumpDir;

    SpeedVal height;

    bool visited;
    size_t minPathLen;
    vector<Coord> path;
} Node;

typedef struct Jump {
    Node *from;
    Coord to;
    SpeedVal direction;

    SpeedVal wasSpeed;
    SpeedVal currentSpeed;

    size_t pathLen;
    bool changedDir;
} Jump;

typedef vector<vector<vector<Node *>>> map_t;

class Field {
public:
    int height, length;
    SpeedVal maxSpeed;

    map_t map;
    size_t res;

    Field(int height, int length, SpeedVal maxSpeed);

    bool isOutOfBounds(Coord coord) const;

    Node *getNode(Coord coord, SpeedVal dir);
};

class Frog{
public:
    Field *field;
    Coord start;
    Coord end;

    Frog(Field *field, Coord start, Coord end);
    void addDestinations(std::queue<Jump> *q, Node *currentNode , Jump currentJump) const;
    bool isValidJump(Jump jump) const;
};

Field *readField();

Node *makeNode(int y, int x, SpeedVal dir, SpeedVal h);

Jump newJump(Node *from, Coord to, SpeedVal direction, SpeedVal speed, bool was1);

bool areEqualCords(Coord c1, Coord c2);

pair<int,int> dirNumToDelta(int dirNum);

Coord jumpCoord(Coord cur, pair<int,int> dir, SpeedVal speed);

Coord jumpPath(Coord cur, pair<int, int> movementDir, SpeedVal delta);

#endif //ZKOUSKA_FROG_H
