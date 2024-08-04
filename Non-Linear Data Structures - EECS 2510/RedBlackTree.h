#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <string>

// A node in the red-black tree that stores a double
class RBTNode 
{
public:
    double key;
    // Whether the node is red (false denotes black)
    bool red = true;
    RBTNode* left = nullptr;
    RBTNode* right = nullptr;
    RBTNode* parent = nullptr;

    RBTNode(double nodeKey) 
    {
        key = nodeKey;
    }
};

// A red-black tree that can only insert
class RedBlackTree
{
public:
    RedBlackTree() 
    {

    };

    ~RedBlackTree();

    // Insert a new element and rebalance the tree
    void insert(RBTNode* node);
    // BST Insertion
    void insertBST(RBTNode* node);

    RBTNode* getGrandparent(RBTNode* node);
    RBTNode* getUncle(RBTNode* node);
    void rotateLeft(RBTNode* node);
    void rotateRight(RBTNode* node);
    void balance(RBTNode* node);
    
    //Entry Point
    int getHeight()
    {
        return getHeight(root);
    }

private:
    RBTNode* root = nullptr;
    void deleteTree(RBTNode* node);
    bool setChild(RBTNode* parent, const std::string& whichChild, RBTNode* child);
    bool replaceChild(RBTNode* parent, RBTNode* currentChild, RBTNode* newChild);
    int getHeight(RBTNode* node);

};


#endif // !REDBLACKTREE_H