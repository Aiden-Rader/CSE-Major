#include <string>
#ifndef AVLTREE_H
#define AVLTREE_H

// A node in the AVL tree that stores a double
class Node {
public:
    double key;
    int height = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    Node(double nodeKey) {
        key = nodeKey;
    }
};

// An AVL tree that can insert with and without rebalancing
class AVLTree
{
public:
    AVLTree() {};
    ~AVLTree();

    // Insert a new element and rebalance the tree
    void insert(Node* node);
    // Insert a new element without rebalancing the tree
    void insertWithoutRebalance(Node* node);

    int getHeight();
    int getHeight(Node* node);
    void clear();
    void clear(Node* node);

private:
    Node* root = nullptr;

    void deleteTree(Node* node);
    void updateHeight(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    int getBalance(Node* node);
    Node* rebalance(Node* node);
    bool setChild(Node* parent, const std::string& whichChild, Node* child);
    void replaceChild(Node* parent, Node* currentChild, Node* newChild);
};

#endif