// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
    
    if (!file) {
        std::cout << "File error: cannot open " << filename << std::endl;
        return;
    }
    
    std::string word;
    char ch;
    
    while (file.get(ch)) {
        // проверяем, является ли символ латинской буквой (ASCII)
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            // преобразуем к нижнему регистру и добавляем к текущему слову
            word += std::tolower(ch);
        } else {
            // если символ не буква и слово не пустое, добавляем его в дерево
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    
    // проверяем последнее слово, если файл не заканчивается разделителем
    if (!word.empty()) {
        tree.insert(word);
    }
    
    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> freqList;
    tree.getNodesSortedByCount(freqList);
    
    // выводим в консоль
    for (const auto& pair : freqList) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    // сохраняем в файл result/freq.txt
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
