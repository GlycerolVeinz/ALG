//
// Created by glycerolveinz on 24.12.23.
//

#include "lazyAvlTreeUtil.h"

void rotate(std::pair<int,int> directions, AvlTree *tree, Node *node) {
    if (directions.first == WAS_LEFT_CHILD){
        if (directions.second == WAS_LEFT_CHILD){
            rotateR(tree, node);
        } else {
            rotateLR(tree, node);
        }
    } else {
        if (directions.second == WAS_LEFT_CHILD){
            rotateRL(tree, node);
        } else {
            rotateL(tree, node);
        }
    }
}

void rotateR(AvlTree *tree, Node *node) {
    Node *startingRootNode = node;
    Node *startingParentNode = node->parent;
    Node *startingLeftChild = node->left;
    Node *startingLeftChildRightChild = startingLeftChild->right;

    if (startingParentNode != nullptr){
        if (startingRootNode->isLeftChild){
            startingParentNode->left = startingLeftChild;
            startingLeftChild->isLeftChild = true;
        } else {
            startingParentNode->right = startingLeftChild;
            startingLeftChild->isLeftChild = false;
        }
    } else {
        tree->root = startingLeftChild;
        startingLeftChild->isLeftChild = false;
    }

    startingLeftChild->parent = startingParentNode;
    startingLeftChild->right = startingRootNode;
    ++startingLeftChild->rightTreeDepth;
    ++startingLeftChild->depth;

    startingRootNode->parent = startingLeftChild;
    startingRootNode->isLeftChild = false;
    startingRootNode->left = startingLeftChildRightChild;
    startingRootNode->leftTreeDepth = startingRootNode->leftTreeDepth - 2;
    --startingRootNode->depth;

    if (startingLeftChildRightChild != nullptr) {
        startingLeftChildRightChild->parent = startingRootNode;
        startingLeftChildRightChild->isLeftChild = true;
    }
}

void rotateL(AvlTree *tree, Node *node) {
    Node *startingRootNode = node;
    Node *startingParentNode = node->parent;
    Node *startingRightChild = node->right;
    Node *startingRightChildLeftChild = startingRightChild->left;

    if (startingParentNode != nullptr){
        if (startingRootNode->isLeftChild){
            startingParentNode->left = startingRightChild;
            startingRightChild->isLeftChild = true;
        } else {
            startingParentNode->right = startingRightChild;
            startingRightChild->isLeftChild = false;
        }
    } else {
        tree->root = startingRightChild;
        startingRightChild->isLeftChild = true;
    }

    startingRightChild->parent = startingParentNode;
    startingRightChild->left = startingRootNode;
    ++startingRightChild->leftTreeDepth;

    startingRootNode->parent = startingRightChild;
    startingRootNode->isLeftChild = true;
    startingRootNode->right = startingRightChildLeftChild;
    startingRootNode->rightTreeDepth = startingRootNode->rightTreeDepth - 2;

    if (startingRightChildLeftChild != nullptr) {
        startingRightChildLeftChild->parent = startingRootNode;
        startingRightChildLeftChild->isLeftChild = false;
    }
}

void rotateLR(AvlTree *tree, Node *node) {
    rotateL(tree, node->left);
    rotateR(tree, node);
}

void rotateRL(AvlTree *tree, Node *node) {
    rotateR(tree, node->right);
    rotateL(tree, node);
}

void addRoot(AvlTree *tree, Node *node) {
    tree->root = node;
    ++tree->size;
    node->depth = 0;
    tree->maxDepth = 0;
}

void recalculateDepths(AvlTree *tree, Node *node, int action){
    Node *currentNode = node;

//    also need to check for rotations
    std::pair<int,int> previousChildrenDirection = std::make_pair(0,0);
    while (currentNode->parent != nullptr){
        if (currentNode->isLeftChild){
            previousChildrenDirection.first = previousChildrenDirection.second;
            previousChildrenDirection.second = WAS_LEFT_CHILD;
            currentNode->parent->leftTreeDepth += action;
        } else {
            previousChildrenDirection.first = previousChildrenDirection.second;
            previousChildrenDirection.second = WAS_RIGHT_CHILD;
            currentNode->parent->rightTreeDepth += action;
        }
        int depthDifference = currentNode->parent->leftTreeDepth - currentNode->parent->rightTreeDepth;
        if (depthDifference > 1 || depthDifference < -1){
            rotate(previousChildrenDirection, tree, currentNode->parent);
            ++tree->rotationsCount;
        }

        currentNode = currentNode->parent;
    }

    tree->root->leftTreeDepth < tree->root->rightTreeDepth ?
        tree->maxDepth = tree->root->rightTreeDepth : tree->maxDepth = tree->root->leftTreeDepth;
}

void addChild(AvlTree *tree, Node *parent, Node *child) {
    child->isLeftChild ? addLeftChild(parent, child) : addRightChild(parent, child);
    ++tree->size;
    recalculateDepths(tree, child, INSERT_RECALCULATE);
}

void addLeftChild(Node *parent, Node *child) {
    parent->left = child;
    child->parent = parent;
    child->depth = parent->depth + 1;
}

void addRightChild(Node *parent, Node *child) {
    parent->right = child;
    child->parent = parent;
    child->depth = parent->depth + 1;
}

AvlTree *initTree(){
    auto *tree = new AvlTree;
    tree->root = nullptr;
    tree->size = 0;
    tree->maxDepth = -1;
    return tree;
}

Node *initNode(int key){
    auto *node = new Node;
    node->key = key;
    node->depth = 0;
    node->isDeleted = false;

    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;

    node->leftTreeDepth = -1;
    node->rightTreeDepth = -1;

    return node;
}

Node *findHighestKeyNode(Node *node){
    Node *currentNode = node;
    while (currentNode->right != nullptr){
        currentNode = currentNode->right;
    }
    return currentNode;
}

Node *findLowestKeyNode(Node *node){
    Node *currentNode = node;
    while (currentNode->left != nullptr){
        currentNode = currentNode->left;
    }
    return currentNode;
}

int maxDeletedNodesTillEnd(int currentDeletedNodesCount, Node *node){
    if (node->isDeleted) ++currentDeletedNodesCount;
    if (node->left == nullptr && node->right == nullptr){
        return currentDeletedNodesCount;
    }
    else if (node->left == nullptr){
        return maxDeletedNodesTillEnd(currentDeletedNodesCount, node->right);
    }
    else if (node->right == nullptr){
        return maxDeletedNodesTillEnd(currentDeletedNodesCount, node->left);
    }
    else{
        int leftResult = maxDeletedNodesTillEnd(currentDeletedNodesCount, node->left);
        int rightResult = maxDeletedNodesTillEnd(currentDeletedNodesCount, node->right);
        return leftResult > rightResult ? leftResult : rightResult;
    }
}

