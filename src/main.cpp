// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <chrono>
#include <string>

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> tree;

    std::cout << "Analyzing 'War and Peace' by Leo Tolstoy..." << std::endl;
    std::cout << "Loading and building BST..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    makeTree(tree, "war_peace.txt");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "\n--- Statistics ---" << std::endl;
    std::cout << "Unique words: " << tree.size() << std::endl;
    std::cout << "Tree depth: " << tree.depth() << std::endl;
    std::cout << "Build time: " << duration.count() << " ms" << std::endl;

    std::cout << "\n--- Word Frequency (descending order) ---" << std::endl;
    printFreq(tree);

    return 0;
}
