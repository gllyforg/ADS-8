// Copyright 2021 NNTU-CS
#include  "bst.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File error: cannot open " << filename << std::endl;
        return;
    }

    std::string word;
    char ch;

    while (file.get(ch)) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            word += std::tolower(ch);
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> freqList;
    tree.getNodesSortedByCount(freqList);

    for (const auto& pair : freqList) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cout << "Cannot create result/freq.txt" << std::endl;
        return;
    }

    for (const auto& pair : freqList) {
        outFile << pair.first << ": " << pair.second << std::endl;
    }

    outFile.close();
    std::cout << "\nResults saved to result/freq.txt" << std::endl;
}
