//
// Created by safor on 30.1.24.
//

#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node *left;
    Node *right;
    int height;

    Node(int key) : key(key), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    Node* root;

    AVLTree() : root(nullptr) {}

    // Get the height of the node
    int height(Node *N) {
        if (N == nullptr) return 0;
        return N->height;
    }

    // Get the balance factor of the node
    int getBalanceFactor(Node *N) {
        if (N == nullptr) return 0;
        return height(N->left) - height(N->right);
    }

    // Right rotate the subtree rooted with y
    Node* rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        // Return new root
        return x;
    }

    // Left rotate the subtree rooted with x
    Node* leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        // Return new root
        return y;
    }

    // Insert a key into the subtree rooted with node and returns the new root
    Node* insert(Node* node, int key) {
        // Perform normal BST insertion
        if (node == nullptr) return new Node(key);

        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node; // Equal keys are not allowed

        // Update height of this ancestor node
        node->height = 1 + max(height(node->left), height(node->right));

        // Get the balance factor to check whether this node became unbalanced
        int balance = getBalanceFactor(node);

        // If unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->key) return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key) return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // Return the unchanged node pointer
        return node;
    }

    // Inorder traversal of the tree
    void inOrder(Node *root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
        }
    }
};

int mainGpt() {
    AVLTree tree;

    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 30);
    tree.root = tree.insert(tree.root, 40);
    tree.root = tree.insert(tree.root, 50);
    tree.root = tree.insert(tree.root, 25);

    cout << "Inorder traversal of the constructed AVL tree is \n";
    tree.inOrder(tree.root);

    return 0;
}
