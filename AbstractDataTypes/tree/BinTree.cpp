//
// Created by safor on 26.1.24.
//

#include "BinTree.h"

namespace MyADTs {
    namespace Trees{
        namespace BinaryTree{

            Node::Node(Node *par, void *data) {
                this->parent = par;
                this->data = data;
                this->left = nullptr;
                this->right = nullptr;
            }

            Node::~Node() {
                delete this->data;
                delete this->left;
                delete this->right;
            }

            BinTree::~BinTree() {
                deleteTree(this->root);
            }

            BinTree::BinTree(Node *root) {
                this->root = root;
            }

            void BinTree::deleteTree(Node *node) {
                if ( !node ) return;
                deleteTree(node->left);
                deleteTree(node->right);
                delete node;
            }

            void BinTree::postorder(Node *node, void (*func)(Node *)) {
                if ( !node ) return;
                postorder(node->left, func);
                postorder(node->right, func);
                func(node);
            }

            void BinTree::preorder(Node *node, void (*func)(Node *)) {
                if ( !node ) return;
                func(node);
                preorder(node->left, func);
                preorder(node->right, func);
            }

            void BinTree::inorder(Node *node, void (*func)(Node *)) {
                if ( !node ) return;
                inorder(node->left, func);
                func(node);
                inorder(node->right, func);
            }

            size_t depthHelper(Node *node, size_t curDepth) {
                if (!node) return curDepth;
                size_t l = depthHelper(node->left, curDepth + 1);
                size_t r = depthHelper(node->right, curDepth + 1);
                return l > r ? l : r;
            }

            size_t BinTree::depth() const {
                if ( !this->root ) return -1;
                return depthHelper(this->root, 0);
            }


            void BinTree::insert(void *data) {
                if ( !this->root ) {
                    this->root = new Node(nullptr, data);
                    return;
                }

                std::queue<Node *> q;
                q.push(this->root);

                while ( !q.empty() ){
                    Node *current = q.front();
                    q.pop();

                    if ( !current->left ){
                        current->left = new Node(current, data);
                        break;
                    } else {
                        q.push(current->left);
                    }

                    if ( !current->right ){
                        current->right = new Node(current, data);
                        break;
                    } else {
                        q.push(current->right);
                    }
                }
            }

        } // BinaryTree
    } // Trees
} // MyADTs