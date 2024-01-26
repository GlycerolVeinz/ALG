//
// Created by safor on 26.1.24.
//

#ifndef ABSTRACTDATATYPES_BINTREE_H
#define ABSTRACTDATATYPES_BINTREE_H

#include <iostream>

namespace MyADTs {
    namespace Trees {
        namespace BinaryTree {

            template<typename T>
            class Node{
            public:
                T *data;

                Node *parent;
                Node *left;
                Node *right;

                Node(Node *par, T *data);
                ~Node();
            };


            template<typename T>
            class BinTree {
            public:
                Node<T> *root;

                BinTree(Node<T>* root);
                ~BinTree();

                void deleteTree(Node<T> *node);

                size_t depth() const;

                void inorder (Node<T> *node,void (*func)(Node<T>*));
                void preorder (Node<T> *node,void (*func)(Node<T>*));
                void postorder (Node<T> *node,void (*func)(Node<T>*));
            };
        }
    }
} // MyADTs

#endif //ABSTRACTDATATYPES_BINTREE_H
