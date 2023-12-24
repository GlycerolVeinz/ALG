//
// Created by glycerolveinz on 24.12.23.
//

#include "lazyAvlTreeUtil.h"

void rotate(AvlTree *tree, Node *node) {
    int depthDifference = node->leftTreeDepth - node->rightTreeDepth;
    if (depthDifference > 1){
        if (node->left->leftTreeDepth >= node->left->rightTreeDepth){
            rotateR(tree, node);
        } else {
            rotateLR(tree, node);
        }
    } else if (depthDifference < -1){
        if (node->right->rightTreeDepth >= node->right->leftTreeDepth){
            rotateL(tree, node);
        } else {
            rotateRL(tree, node);
        }
    }
    ++tree->rotationsCount;
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

void recalculateDepths(AvlTree *tree, Node *node){
    Node *currentNode = node;

    while (currentNode->parent != nullptr){
        if (currentNode->isLeftChild){
            int leftDepth = currentNode->left == nullptr ? -1 : currentNode->left->depth - currentNode->depth;
            int rightDepth = currentNode->right == nullptr ? -1 : currentNode->right->depth - currentNode->depth;
            if (leftDepth == -1 && rightDepth == -1){
                currentNode->parent->leftTreeDepth = 0;
            } else {
                leftDepth > rightDepth ?
                    currentNode->parent->leftTreeDepth = leftDepth + 1 : currentNode->parent->leftTreeDepth = rightDepth + 1;
            }
        } else {
            int leftDepth = currentNode->left == nullptr ? -1 : currentNode->left->depth - currentNode->depth;
            int rightDepth = currentNode->right == nullptr ? -1 : currentNode->right->depth - currentNode->depth;
            if (leftDepth == -1 && rightDepth == -1){
                currentNode->parent->rightTreeDepth = 0;
            } else {
                leftDepth > rightDepth ?
                    currentNode->parent->rightTreeDepth = leftDepth + 1 : currentNode->parent->rightTreeDepth = rightDepth + 1;
            }
        }
        int depthDifference = currentNode->parent->leftTreeDepth - currentNode->parent->rightTreeDepth;
        if (depthDifference > 1 || depthDifference < -1){
            rotate(tree, currentNode->parent);
        }

        currentNode = currentNode->parent;
    }

    tree->root->leftTreeDepth < tree->root->rightTreeDepth ?
        tree->maxDepth = tree->root->rightTreeDepth : tree->maxDepth = tree->root->leftTreeDepth;
}

void addChild(AvlTree *tree, Node *parent, Node *child) {
    child->isLeftChild ? addLeftChild(parent, child) : addRightChild(parent, child);
    ++tree->size;
//    recalculateDepths(tree, child);
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

