//
// Created by safor on 30.1.24.
//

#include "BST.h"

namespace MyADTs {
    namespace Trees {
        namespace BinarySearchTree {

            void BST::insert(void *data) {
                if (!this->root) {
                    this->root = new Node(nullptr, data);
                    return;
                }

                Node *cur = this->root;
                while (true) {
                    if ( *(int *)data < *(int *)cur->data) {
                        if (cur->left) {
                            changeCur(cur, cur->left);
                        } else {
                            createNewAt(cur->left, new Node(cur, data));
                            return;
                        }

                    } else {
                        if (cur->right) {
                            changeCur(cur, cur->right);
                        } else {
                            createNewAt(cur->right, new Node(cur, data));
                            return;
                        }
                    }
                }
            }

            void BST::changeCur(Node *cur, Node *newCur) {
                cur = newCur;
            }

            void BST::createNewAt(Node *at, Node *newNode) {
                at = newNode;
            }

        } // BinarySearchTree
    } // Trees
} // MyADTs
