// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>

template<typename T>
class BST {
 private:
    struct Node {
        T data;
        int freq;
        Node* left;
        Node* right;
        explicit Node(const T& val) : data(val), freq(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void addNode(Node*& node, const T& val) {
        if (node == nullptr) {
            node = new Node(val);
        } else if (val < node->data) {
            addNode(node->left, val);
        } else if (val > node->data) {
            addNode(node->right, val);
        } else {
            node->freq++;
        }
    }

    int calcDepth(Node* node) const {
        if (node == nullptr) return 0;
        int leftDepth = calcDepth(node->left);
        int rightDepth = calcDepth(node->right);
        return 1 + std::max(leftDepth, rightDepth);
    }

    int findValue(Node* node, const T& val) const {
        if (node == nullptr) return 0;
        if (val == node->data) return node->freq;
        if (val < node->data) return findValue(node->left, val);
        return findValue(node->right, val);
    }

    void destroyTree(Node* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    void gatherNodes(Node* node, Node** arr, int& pos) const {
        if (node == nullptr) return;
        gatherNodes(node->left, arr, pos);
        arr[pos++] = node;
        gatherNodes(node->right, arr, pos);
    }

    int countNodes(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

 public:
    BST() : root(nullptr) {}

    ~BST() {
        destroyTree(root);
    }

    void insert(const T& val) {
        addNode(root, val);
    }

    int depth() const {
        return calcDepth(root);
    }

    int search(const T& val) const {
        return findValue(root, val);
    }

    int size() const {
        return countNodes(root);
    }

    void collectNodes(Node** arr, int& pos) const {
        gatherNodes(root, arr, pos);
    }

    using NodeType = Node;
};

#endif  // INCLUDE_BST_H_
