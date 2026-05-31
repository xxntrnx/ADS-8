// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

template<typename T>
class BST {
private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;

        Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, const T& key) {
        if (node == nullptr) {
            return new Node(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            node->count++;
        }
        return node;
    }

    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    int getDepth(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + std::max(getDepth(node->left), getDepth(node->right));
    }

    int findCount(Node* node, const T& key) const {
        if (node == nullptr) return 0;
        if (key == node->key) return node->count;
        if (key < node->key) return findCount(node->left, key);
        return findCount(node->right, key);
    }

    void collectNodes(Node* node, std::vector<std::pair<T, int>>& nodes) const {
        if (node == nullptr) return;
        collectNodes(node->left, nodes);
        nodes.push_back({node->key, node->count});
        collectNodes(node->right, nodes);
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void insert(const T& key) {
        root = insert(root, key);
    }

    int depth() const {
        return getDepth(root);
    }

    int search(const T& key) const {
        return findCount(root, key);
    }

    std::vector<std::pair<T, int>> getSortedByKey() const {
        std::vector<std::pair<T, int>> result;
        collectNodes(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
