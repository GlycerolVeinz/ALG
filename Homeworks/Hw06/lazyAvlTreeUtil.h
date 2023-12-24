//
// Created by glycerolveinz on 24.12.23.
//

#ifndef HW06_LAZYAVLTREEUTIL_H
#define HW06_LAZYAVLTREEUTIL_H

#include <string>

typedef struct Node{
    int key;
    int depth;
    bool isDeleted;

    Node *left;
    Node *right;

    int leftTreeDepth;
    int rightTreeDepth;

    Node *parent;
    bool isLeftChild;
} Node;

typedef struct AvlTree{
    Node *root;
    int size;
    int maxDepth;

    int rotationsCount;
    int consolidationsCount;
} AvlTree;

AvlTree *initTree();
Node *initNode(int key);

int maxDeletedNodesTillEnd(int currentDeletedNodesCount, Node *node);
void recalculateDepths(AvlTree *tree, Node *node);

void addRoot(AvlTree *tree, Node *node);
void addChild(AvlTree *tree, Node *parent, Node *child);
void addLeftChild(Node *parent, Node *child);
void addRightChild(Node *parent, Node *child);

Node *findHighestKeyNode(Node *node);
Node *findLowestKeyNode(Node *node);


void rotate(AvlTree *tree, Node *node);
void rotateL(AvlTree *tree, Node *node);
void rotateR(AvlTree *tree, Node *node);
void rotateLR(AvlTree *tree, Node *node);
void rotateRL(AvlTree *tree, Node *node);

#endif //HW06_LAZYAVLTREEUTIL_H
