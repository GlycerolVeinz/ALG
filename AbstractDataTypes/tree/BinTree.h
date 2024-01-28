//
// Created by safor on 26.1.24.
//

#ifndef ABSTRACTDATATYPES_BINTREE_H
#define ABSTRACTDATATYPES_BINTREE_H

#include <iostream>
#include <queue>

namespace MyADTs {
    namespace Trees {
        namespace BinaryTree {

            class Node{
            public:
                void *data;

                Node *parent;
                Node *left;
                Node *right;

                Node(Node *par, void *data);
                ~Node();
            };

            class BinTree {
            public:
                Node *root;

                explicit BinTree(Node *root);
                ~BinTree();
                void deleteTree(Node *node);

                void insert(void *data);
                size_t depth() const;

                void inorder (Node *node,void (*func)(Node *));
                void preorder (Node *node,void (*func)(Node *));
                void postorder (Node *node,void (*func)(Node *));
            };
        }
    }
} // MyADTs

#endif //ABSTRACTDATATYPES_BINTREE_H
