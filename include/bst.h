// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
template <typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;

        explicit Node(const T& val) : key(val), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int nodeCount;

    Node* insert(Node* node, const T& value) {
        if (node == nullptr) {
            nodeCount++;
            return new Node(value);
        }

        if (value < node->key) {
            node->left = insert(node->left, value);
        } else if (value > node->key) {
            node->right = insert(node->right, value);
        } else {
            node->count++;
        }
        return node;
    }

    Node* search(Node* node, const T& value) const {
        if (node == nullptr || node->key == value) {
            return node;
        }

        if (value < node->key) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    int depth(Node* node) const {
        if (node == nullptr) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return 1 + std::max(leftDepth, rightDepth);
    }

    void inorder(Node* node) const {
        if (node != nullptr) {
            inorder(node->left);
            std::cout << node->key << ": " << node->count << std::endl;
            inorder(node->right);
        }
    }

    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void collectNodes(Node* node, std::vector<Node*>& nodes) const {
        if (node != nullptr) {
            collectNodes(node->left, nodes);
            nodes.push_back(node);
            collectNodes(node->right, nodes);
        }
    }

 public:
    BST() : root(nullptr), nodeCount(0) {}

    ~BST() {
        clear(root);
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

    Node* search(const T& value) const {
        return search(root, value);
    }

    int depth() const {
        return depth(root);
    }

    int size() const {
        return nodeCount;
    }

    bool empty() const {
        return root == nullptr;
    }

    void printInorder() const {
        inorder(root);
    }

    void getNodesSortedByCount(std::vector<std::pair<T, int>>& result) const {
        std::vector<Node*> nodes;
        collectNodes(root, nodes);

        std::sort(nodes.begin(), nodes.end(),
            [](Node* a, Node* b) { return a->count > b->count; });

        for (Node* node : nodes) {
            result.push_back({node->key, node->count});
        }
    }
};

#endif  // INCLUDE_BST_H_
