//
// Created by safor on 26.1.24.
//

#include "BinTree.h"

namespace MyADTs {
    namespace Trees{
        namespace BinaryTree{

            template<typename T>
            Node<T>::Node(Node *par, T *data) {
                this->parent = par;
                this->data = data;
                this->left = nullptr;
                this->right = nullptr;
            }

            template<typename T>
            Node<T>::~Node() {
                delete this->data;
                delete this->left;
                delete this->right;
            }


            template<typename T>
            BinTree<T>::~BinTree() {
                deleteTree(this->root);
            }

            template<typename T>
            BinTree<T>::BinTree(Node<T> *root) {
                this->root = root;
            }

            template<typename T>
            void BinTree<T>::deleteTree(Node<T> *node) {
                if ( !node ) return;
                deleteTree(node->left);
                deleteTree(node->right);
                delete node;
            }

            template<typename T>
            void BinTree<T>::postorder(Node<T> *node, void (*func)(Node<T>*)) {
                if ( !node ) return;
                postorderPrint(node->left);
                postorderPrint(node->right);
                func(node);
            }

            template<typename T>
            void BinTree<T>::preorder(Node<T> *node, void (*func)(Node<T>*)) {
                if ( !node ) return;
                func(node);
                preorderPrint(node->left);
                preorderPrint(node->right);
            }

            template<typename T>
            void BinTree<T>::inorder(Node<T> *node, void (*func)(Node<T>*)) {
                if ( !node ) return;
                inorderPrint(node->left);
                func(node);
                inorderPrint(node->right);
            }

            template<typename T>
            size_t depthHelper(Node<T> *node, size_t curDepth) {
                if (!node) return curDepth;
                size_t l = depthHelper(node->left, curDepth + 1);
                size_t r = depthHelper(node->right, curDepth + 1);
                return l > r ? l : r;
            }

            template<typename T>
            size_t BinTree<T>::depth() const {
                if ( !this->root ) return -1;
                return depthHelper(this->root, 0);
            }
        }
    }
} // MyADTs