//
// Created by glycerolveinz on 21.12.23.
//

#include "avlTreeSolver.h"

int main (){
    int numOfOperations;
    std::cin >> numOfOperations;
    AvlTree *tree = initTree();

    int currentOperation;
    Node *currentNode;
    int deletedNodes = 0;
    for (int i = 0; i < numOfOperations; ++i) {
        std::cin >> currentOperation;
        if (currentOperation > 0){
            currentNode = initNode(currentOperation);
            deletedNodes = insertNode(tree, currentNode);
        } else {
            deletedNodes = deleteNode(tree, -currentOperation);
        }
        if (deletedNodes > ( 1 + (tree->maxDepth / 2) ) ){
            consolidate(tree, tree->root);
            ++tree->consolidationsCount;
        }
    }

    std::cout << std::max(tree->root->leftTreeDepth, tree->root->rightTreeDepth) + 1 << " " << tree->rotationsCount << " " << tree->consolidationsCount << "\n" << std::endl;

    return 0;
}


int insertNode(AvlTree *tree, Node *node) {
    int deletedNodes = 0;

    if (tree->root == nullptr){
        addRoot(tree, node);
        return deletedNodes;
    }

    Node *currentNode = tree->root;
    Node *parentNode = nullptr;
    bool isLeftChild = false;
//    runs through a tree, to place a new node
    while (currentNode != nullptr){
        if (currentNode->isDeleted)
            ++deletedNodes;
        parentNode = currentNode;

        if (node->key < currentNode->key){
            currentNode = currentNode->left;
            isLeftChild = true;
        } else if (node->key > currentNode->key){
            currentNode = currentNode->right;
            isLeftChild = false;
        } else {
//            if node is already in a tree
            if (currentNode->isDeleted){
                currentNode->isDeleted = false;
                --deletedNodes;
                delete node;
            }
            return maxDeletedNodesTillEnd(deletedNodes, currentNode);
        }
    }
    node->isLeftChild = isLeftChild;
    addChild(tree, parentNode, node);
    recalculateDepths(tree, node);
    return deletedNodes;
}

int deleteNode(AvlTree *tree, int key) {
    Node *currentNode = tree->root;
    int deletedNodes = 0;

    while (currentNode != nullptr){
        if (currentNode->isDeleted)
            ++deletedNodes;

        if (key < currentNode->key){
            currentNode = currentNode->left;
        } else if (key > currentNode->key){
            currentNode = currentNode->right;
        } else {
            currentNode->isDeleted = true;
            break;
        }
    }

    if (currentNode == nullptr)
        return deletedNodes;
    return maxDeletedNodesTillEnd(deletedNodes, currentNode);
}

void removeNode(AvlTree *tree, Node *node) {
    if(node->left != nullptr){
        Node *lNode = findHighestKeyNode(node->left);
        node->key = lNode->key;
        node->isDeleted = false;
        removeNode(tree, lNode);
    }
    else if(node->right != nullptr){
        Node *rNode = findLowestKeyNode(node->right);
        node->key = rNode->key;
        node->isDeleted = false;
        removeNode(tree, rNode);
    }
//    else (is leaf)
    else {
        --tree->size;
        if (node->parent == nullptr){
            tree->root = nullptr;
            tree->maxDepth = -1;
            delete node;
            return;
        }
        node->isLeftChild ? node->parent->leftTreeDepth = -1 : node->parent->rightTreeDepth = -1;
        node->isLeftChild ? node->parent->left = nullptr : node->parent->right = nullptr;
        recalculateDepths(tree, node);
        delete node;
    }
//    check for rotations
}

void consolidate(AvlTree* tree, Node *node) {
    if (node != nullptr){
        consolidate(tree,node->left);
        consolidate(tree,node->right);
        if (node->isDeleted) removeNode(tree, node);
    }
}
