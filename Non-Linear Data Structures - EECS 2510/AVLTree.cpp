#include "AVLTree.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>



//Destructor
AVLTree::~AVLTree() 
{
    deleteTree(root);
}

void AVLTree::deleteTree(Node* node)
{
    // Recursively remove all nodes in the BST (used by the destructor). 
    // By doing this recursively, we start removing nodes from the bottom
    // of the tree (leaf nodes), which is most efficiently because it does
    // not require replacing any nodes.

    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void AVLTree::updateHeight(Node* node)
{
    if (node == nullptr)
        return;

    int leftHeight = (node->left != nullptr) ? node->left->height : -1;  // Change from 0 to -1
    int rightHeight = (node->right != nullptr) ? node->right->height : -1; // Change from 0 to -1
    node->height = 1 + std::max(leftHeight, rightHeight);

    // Recursively update the height of the parent
    updateHeight(node->parent);
}


int AVLTree::getBalance(Node* node)
{
    int leftHeight = (node->left != nullptr) ? node->left->height : -1;
    int rightHeight = (node->right != nullptr) ? node->right->height : -1;
    return leftHeight - rightHeight;
}

Node* AVLTree::rebalance(Node* node)
{
    updateHeight(node);
    int balance = getBalance(node);

    if (balance == -2)
    {
        if (getBalance(node->right) == 1)
        {
            // Double rotation case: Right-Left
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    else if (balance == 2)
    {
        if (getBalance(node->left) == -1)
        {
            // Double rotation case: Left-Right
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    return node;
}

Node* AVLTree::rotateLeft(Node* node)
{
    // Get the right child and its left child
    Node* rightChild = node->right;
    Node* rightLeftChild = rightChild->left;

    // If the node has a parent, replace the node with the right child
    if (node->parent != nullptr)
    {
        replaceChild(node->parent, node, rightChild);
    }
    else
    {
        // The node is the root, update the root
        root = rightChild;
        rightChild->parent = nullptr;
    }

    // Set the right child's left child to be the original node
    setChild(rightChild, "left", node);

    // Set the original node's right child to be the rightLeftChild
    setChild(node, "right", rightLeftChild);

    // Update heights after rotation
    updateHeight(node);
    updateHeight(rightChild);

    return rightChild;
}

Node* AVLTree::rotateRight(Node* node)
{
    // Get the left child and its right child
    Node* leftChild = node->left;
    Node* leftRightChild = leftChild->right;

    // If the node has a parent, replace the node with the left child
    if (node->parent != nullptr)
    {
        replaceChild(node->parent, node, leftChild);
    }
    else
    {
        // The node is the root, update the root
        root = leftChild;
        leftChild->parent = nullptr;
    }

    // Set the left child's right child to be the original node
    setChild(leftChild, "right", node);

    // Set the original node's left child to be the leftRightChild
    setChild(node, "left", leftRightChild);

    // Update heights after rotation
    updateHeight(node);
    updateHeight(leftChild);

    return leftChild;
}

bool AVLTree::setChild(Node* parent, const std::string& whichChild, Node* child) 
{
    if (whichChild != "left" && whichChild != "right") 
    {
        return false; // Invalid child identifier
    }

    if (whichChild == "left") 
    {
        parent->left = child;
    }
    else {
        parent->right = child;
    }

    if (child != nullptr) 
    {
        child->parent = parent;
    }

    updateHeight(parent);

    return true;
}

void AVLTree::replaceChild(Node* parent, Node* currentChild, Node* newChild) 
{
    if (parent->left == currentChild) 
    {
        setChild(parent, "left", newChild);
    }
    else if (parent->right == currentChild)
    {
        setChild(parent, "right", newChild);
    }
}

void AVLTree::insert(Node* node) 
{
    if (root == nullptr) 
    {
        root = node;
        node->parent = nullptr;
    }
    else 
    {
        Node* cur = root;
        Node* parent = nullptr; // Initialize parent pointer

        while (cur != nullptr) 
        {
            parent = cur; // Update parent pointer before moving to the next node

            if (node->key < cur->key) 
            {
                cur = cur->left;
            }
            else 
            {
                cur = cur->right;
            }
        }

        if (node->key < parent->key) 
        {
            parent->left = node;
        }
        else 
        {
            parent->right = node;
        }

        node->parent = parent;

        // Rebalance starting from the parent
        Node* rebalanceNode = parent;
        while (rebalanceNode != nullptr) 
        {
            rebalanceNode = rebalance(rebalanceNode);
            rebalanceNode = rebalanceNode->parent;
        }
    }
}

void AVLTree::insertWithoutRebalance(Node* node) 
{
    if (root == nullptr) 
    {
        root = node;
        node->parent = nullptr;
    }
    else 
    {
        Node* cur = root;
        while (cur != nullptr) 
        {
            if (node->key < cur->key) 
            {
                if (cur->left == nullptr) 
                {
                    cur->left = node;
                    node->parent = cur;
                    break; // Inserted, so exit the loop
                }
                else 
                {
                    cur = cur->left;
                }
            }
            else 
            {
                if (cur->right == nullptr) 
                {
                    cur->right = node;
                    node->parent = cur;
                    break; // Inserted, so exit the loop
                }
                else 
                {
                    cur = cur->right;
                }
            }
        }
    }
}


//Added Functions for finding height and clearing tree

int AVLTree::getHeight() 
{
    return getHeight(root); 
}

int AVLTree::getHeight(Node* node) 
{
    if (node == nullptr) 
    {
        return -1; 
    }
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return 1 + std::max(leftHeight, rightHeight);
}

void AVLTree::clear() 
{
    clear(root);
    root = nullptr; 
}

void AVLTree::clear(Node* node) 
{
    if (node == nullptr) 
    {
        return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
}

// Single rotate left
int main() 
{
    AVLTree b;
    Node* bRoot = new Node(2);
    b.insert(bRoot);
    b.insert(new Node(1));
    b.insert(new Node(3));
    b.insert(new Node(4));
    b.insert(new Node(5));
    std::cout << bRoot->key << std::endl;
    std::cout << bRoot->left->key << " " << bRoot->right->key << std::endl;
    std::cout << bRoot->right->left->key << " " << bRoot->right->right->key
        << std::endl;
    // Rotate left then right
    AVLTree c;
    Node* cRoot = new Node(4);
    c.insert(cRoot);
    c.insert(new Node(3));
    c.insert(new Node(5));
    c.insert(new Node(1));
    c.insert(new Node(2));
    std::cout << cRoot->key << std::endl;
    std::cout << cRoot->left->key << " " << cRoot->right->key << std::endl;
    std::cout << cRoot->left->left->key << " " << cRoot->left->right->key <<
        std::endl;
}

/*
* TO CHECK IF THE ORIGINAL MAIN WORKS PLEASE
* UNCOMMENT THIS AND COMMENT OUT THE OTHER
* MAIN FUNCTION!
*/

//int main() 
//{
//    // Initialize random number generator
//    std::srand(static_cast<unsigned>(std::time(nullptr)));
//
//    // Values of n to test (10^2, 10^3, 10^4, 10^5)
//    std::vector<int> n_values = { 100, 1000, 10000, 100000 };
//
//    for (int n : n_values) 
//    {
//        int numIterations = 10;
//        std::vector<int> bstHeights, avlHeights;
//
//        for (int iter = 0; iter < numIterations; ++iter) 
//        {
//            AVLTree avlTree;
//            AVLTree bstWithoutBalancing;
//
//            for (int i = 0; i < n; ++i) 
//            {
//                double randomValue = static_cast<double>(std::rand()) / RAND_MAX;
//                Node* avlNode = new Node(randomValue);
//                Node* bstNode = new Node(randomValue);
//
//                // Insert nodes into AVL tree and BST without balancing
//                avlTree.insert(avlNode);
//                bstWithoutBalancing.insertWithoutRebalance(bstNode);
//            }
//            // Record the height of both AVL and BST
//            int avlHeight = avlTree.getHeight();
//            int bstHeight = bstWithoutBalancing.getHeight();
//
//            // Store the heights for this iteration
//            avlHeights.push_back(avlHeight);
//            bstHeights.push_back(bstHeight);
//
//            // Clear both trees for the next iteration
//            avlTree.clear();
//            bstWithoutBalancing.clear();
//        }
//
//        // Calculate minimum, average, and maximum heights for this n
//        int minBstHeight = *std::min_element(bstHeights.begin(), bstHeights.end());
//        int sumBstHeight = 0;
//        for (int height : bstHeights) 
//        {
//            sumBstHeight += height;
//        }
//        int avgBstHeight = sumBstHeight / numIterations;
//        int maxBstHeight = *std::max_element(bstHeights.begin(), bstHeights.end());
//
//        //============================================================================//
//
//        int minAvlHeight = *std::min_element(avlHeights.begin(), avlHeights.end());
//        int sumAvlHeight = 0;
//        for (int height : avlHeights) 
//        {
//            sumAvlHeight += height;
//        }
//        int avgAvlHeight = sumAvlHeight / numIterations;
//        int maxAvlHeight = *std::max_element(avlHeights.begin(), avlHeights.end());
//
//        // Print the results for this n
//        std::cout << "For n = " << n << ":\n";
//        std::cout << "BST Height: Min = " << minBstHeight << ", Avg = " << avgBstHeight << ", Max = " << maxBstHeight << "\n";
//        std::cout << "AVL Tree Height: Min = " << minAvlHeight << ", Avg = " << avgAvlHeight << ", Max = " << maxAvlHeight << "\n";
//
//        }
//}