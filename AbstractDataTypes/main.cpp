#include <iostream>
#include <random>

#include "tree/BinTree.h"
using std::vector;
#define LEN 15

void printNode(MyADTs::Trees::BinaryTree::Node *node) {
    std::cout << * (int *)node->data << " ";
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);

    auto *tree = new MyADTs::Trees::BinaryTree::BinTree(nullptr);

    for (size_t i = 0; i < LEN; i++) {
        int *value = new int;
        *value = dis(gen);
        tree->insert(value);
        std::cerr << *value << " \n";
    }

    std::cout << "Inorder :\n";
    tree->inorder(tree->root, printNode);

    std::cout << "\nPreorder :\n";
    tree->preorder(tree->root, printNode);

    std::cout << "\nPostorder :\n";
    tree->postorder(tree->root, printNode);
    std::cout << std::endl;

    return 0;
}
