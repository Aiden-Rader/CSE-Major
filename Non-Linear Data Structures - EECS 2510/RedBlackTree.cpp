#include "RedBlackTree.h"
#include "AVLTree.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

RedBlackTree::~RedBlackTree() 
{
    deleteTree(root);
}

void RedBlackTree::deleteTree(RBTNode* node) 
{
    // Recursively remove all nodes in the BST (used by the destructor). 
    // By doing this recursively, we start removing nodes from the bottom
    // of the tree (leaf nodes), which is most efficiently because it does
    // not require replacing any nodes.

    if (node == nullptr)
    {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}


// Set Child
bool RedBlackTree::setChild(RBTNode* parent, const std::string& whichChild, RBTNode* child) 
{
    if (whichChild != "left" && whichChild != "right") 
    {
        return false;
    }

    if (whichChild == "left") 
    {
        parent->left = child;
    }
    else 
    {
        parent->right = child;
    }

    if (child != nullptr) 
    {
        child->parent = parent;
    }

    return true;
}

// Replace Child
bool RedBlackTree::replaceChild(RBTNode* parent, RBTNode* currentChild, RBTNode* newChild)
{
    if (parent->left == currentChild) 
    {
        return setChild(parent, "left", newChild);
    }
    else if (parent->right == currentChild) 
    {
        return setChild(parent, "right", newChild);
    }

    return false;
}

// Aditional getHeight function
int RedBlackTree::getHeight(RBTNode* node)
{
    if (node == nullptr) 
    {
        return 0;
    }

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return 1 + std::max(leftHeight, rightHeight);
}

// Rotate Left 
void RedBlackTree::rotateLeft(RBTNode* node)
{
    RBTNode* rightLeftChild = node->right->left;

    if (node->parent != nullptr)
    {
        replaceChild(node->parent, node, node->right);
    }
    else
    {
        root = node->right;
        root->parent = nullptr;
    }

    setChild(node->right, "left", node);
    setChild(node, "right", rightLeftChild);
}


// Rotate Right 
void RedBlackTree::rotateRight(RBTNode* node)
{
    RBTNode* leftRightChild = node->left->right;

    if (node->parent != nullptr)
    {
        replaceChild(node->parent, node, node->left);
    }
    else
    {
        root = node->left;
        root->parent = nullptr;
    }

    setChild(node->left, "right", node);
    setChild(node, "left", leftRightChild);
}


// Get Grandparent
RBTNode* RedBlackTree::getGrandparent(RBTNode* node)
{
    if (node != nullptr && node->parent != nullptr)
    {
        return node->parent->parent;
    }

    return nullptr;
}


// Get Uncle
RBTNode* RedBlackTree::getUncle(RBTNode* node)
{
    RBTNode* grandparent = nullptr;

    if (node != nullptr && node->parent != nullptr)
    {
        grandparent = node->parent->parent;
    }

    if (grandparent == nullptr)
    {
        return nullptr;
    }

    if (grandparent->left == node->parent)
    {
        return grandparent->right;
    }
    else
    {
        return grandparent->left;
    }
}


// Balance
void RedBlackTree::balance(RBTNode* node)
{
    if (node->parent == nullptr) 
    {
        // If the node is the root, color it black
        node->red = false;
        return;
    }

    if (node->parent->red == false) 
    {
        // If the parent is black, the tree is still valid
        return;
    }

    RBTNode* parent = node->parent;
    RBTNode* grandparent = getGrandparent(node);
    RBTNode* uncle = getUncle(node);

    if (uncle != nullptr && uncle->red == true) 
    {
        // Case 1: Recolor nodes if uncle is red
        parent->red = false;
        uncle->red = false;
        grandparent->red = true;
        balance(grandparent);
        return;
    }

    if (node == parent->right && parent == grandparent->left) 
    {
        // Case 2: Left-right situation, rotate left
        rotateLeft(parent);
        node = parent;
        parent = node->parent;
    }
    else if (node == parent->left && parent == grandparent->right) 
    {
        // Case 3: Right-left situation, rotate right
        rotateRight(parent);
        node = parent;
        parent = node->parent;
    }

    // Case 4: Final rotation and recoloring
    parent->red = false;
    grandparent->red = true;

    if (node == parent->left) 
    {
        rotateRight(grandparent);
    }
    else 
    {
        rotateLeft(grandparent);
    }
}

// RBT Insert
void RedBlackTree::insert(RBTNode* node)
{
    insertBST(node);

    // Set the color of the newly inserted node to red
    node->red = true;

    // Balance the Red-Black Tree after insertion
    balance(node);
}


// BST Insert (CORMEN BOOK)
void RedBlackTree::insertBST(RBTNode* node) {
    RBTNode* x = root;
    RBTNode* y = nullptr;

    while (x != nullptr) 
    {
        y = x;
        if (node->key < x->key) 
        {
            x = x->left;
        }
        else 
        {
            x = x->right;
        }
    }
    node->parent = y;

    if (y == nullptr) 
    {
        root = node;
    }
    else if (node->key < y->key) 
    {
        y->left = node;
    }
    else 
    {
        y->right = node;
    }
}

/*
*  UN-COMMENT Second main for average times and final height!
*/


int main()
{
    RedBlackTree a;
    RBTNode* aRoot = new RBTNode(22);
    a.insert(aRoot);
    a.insert(new RBTNode(11));
    a.insert(new RBTNode(33));
    a.insert(new RBTNode(55));
    a.insert(new RBTNode(44));
    std::cout << aRoot->key << std::endl;
    std::cout << aRoot->left->key << " " << aRoot->right->key << std::endl;
    std::cout << aRoot->right->left->key << " " << aRoot->right->right -> key << std::endl;

    return 0;
}

//int main()
//{
//    vector<int> vectorLengths = { 100, 1000, 10000, 100000 };
//
//    for (int length : vectorLengths)
//    {
//        cout << "Vector Length: " << length << endl;
//
//        // Experiment parameters
//        const int numTrials = 10;
//        double totalRBTime = 0.0;
//        double totalAVLTime = 0.0;
//        int totalRBHeight = 0;
//        int totalAVLHeight = 0;
//
//
//        for (int trial = 0; trial < numTrials; ++trial) 
//        {
//            // Create a random vector
//            vector<int> randomVector(length);
//
//            // Fill vector with random values between 0 and 1
//            generate(randomVector.begin(), randomVector.end(), []() 
//                {
//                return rand() % 100;  // Adjust range as needed
//                });
//
//            // Sort the vector with C++ Library Sort
//            sort(randomVector.begin(), randomVector.end());
//
//
//            
//            RedBlackTree rbTree;
//
//            auto startRB = chrono::high_resolution_clock::now();
//            for (int value : randomVector)
//            {
//                rbTree.insert(new RBTNode(value));
//            }
//            auto endRB = chrono::high_resolution_clock::now();
//
//            // Calculate durration of each trial
//            chrono::duration<double> rbDuration = endRB - startRB;
//
//            //==========================================================/
//
//            totalRBTime += rbDuration.count();
//            totalRBHeight += rbTree.getHeight();
//
//             //Insert into AVL Tree (you need to implement AVL Tree)
//             AVLTree avlTree;
//             auto startAVL = std::chrono::high_resolution_clock::now();
//             for (int value : randomVector) 
//             {
//                 avlTree.insert(new Node(value));
//             }
//             auto endAVL = std::chrono::high_resolution_clock::now();
//
//
//             std::chrono::duration<double> avlDuration = endAVL - startAVL;
//             totalAVLTime += avlDuration.count();
//             totalAVLHeight += avlTree.getHeight();
//
//        }
//
//        // Calculate averages
//        double avgRBTime = totalRBTime / numTrials;
//        double avgAVLTime = totalAVLTime / numTrials;
//        int avgRBHeight = totalRBHeight / numTrials;
//        int avgAVLHeight = totalAVLHeight / numTrials;
//
//        // Output results
//        std::cout << "Red-Black Tree:" << std::endl;
//        std::cout << "  Average Wall Clock Time: " << avgRBTime << " seconds" << std::endl;
//        std::cout << "  Average Final Height: " << avgRBHeight << std::endl;
//
//        std::cout << "AVL Tree:" << std::endl;
//        std::cout << "  Average Wall Clock Time: " << avgAVLTime << " seconds" << std::endl;
//        std::cout << "  Average Final Height: " << avgAVLHeight << std::endl << std::endl;
//    }
//
//    return 0;
//
//}