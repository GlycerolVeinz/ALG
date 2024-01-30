//
// Created by safor on 30.1.24.
//

#ifndef ABSTRACTDATATYPES_BST_H
#define ABSTRACTDATATYPES_BST_H

#include "BinTree.h"

namespace MyADTs {
    namespace Trees {
        namespace BinarySearchTree {
            using BinaryTree::Node;

            class BST : public BinaryTree::BinTree {
            public :
                void insert(void *data);
                void changeCur(Node *cur, Node *newCur);
                void createNewAt(Node *at, Node *newNode);
            };

        }
    }
} // MyADTs


#endif //ABSTRACTDATATYPES_BST_H
