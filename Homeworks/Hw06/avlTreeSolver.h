//
// Created by glycerolveinz on 21.12.23.
//

#ifndef HW06_AVLTREESOLVER_H
#define HW06_AVLTREESOLVER_H

#include <iostream>
#include "lazyAvlTreeUtil.h"

int insertNode(AvlTree *tree, Node *node);
int deleteNode(AvlTree *tree, int key);
void removeNode(AvlTree *tree, Node *node);
void consolidate(AvlTree* tree, Node *node);

#endif //HW06_AVLTREESOLVER_H

