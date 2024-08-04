#include "IndexedBST.h"

Node* IndexedBST::search(double desiredKey) 
{
    Node* cur = root;
    while (cur != nullptr) 
    {
        // Return the node if the key matches
        if (cur->key == desiredKey) 
        {
            return cur;
        }

        // Navigate to the left if the search key is 
        // less than the node's key.
        else if (desiredKey < cur->key) 
        {
            cur = cur->left;
        }

        // Navigate to the right if the search key is 
        // greater than the node's key.
        else 
        {
            cur = cur->right;
        }
    }

    // The key was not found in the tree.
    return nullptr;
}

Node* IndexedBST::at(int index) 
{
    Node* cur = root;
    while (cur != nullptr) 
    {
        if (index == cur->leftSize)
            return cur;     // Found
        else if (index < cur->leftSize)
            cur = cur->left;    // index is in left subtree
        else 
        {
            // index is in right subtree
            index = index - cur->leftSize - 1;
            cur = cur->right;
        }
    }

    return nullptr;
}


//=======================================================//

//WORKS!
void IndexedBST::insert(Node* node)
{
    //If the tree is empty, make the node the root and return
    if (root == nullptr) 
    {
        root = node;
        return;
    }

    Node* cur = root;
    while (true)
    {
        //If the key of the node to insert is less than the current node's key
        if (node->key < cur->key)
        {
            //Increment the leftSize property of the current node
            cur->leftSize++;

            //If the left child of the current node is empty, insert the node here
            if (cur->left == nullptr)
            {
                cur->left = node;

                //Set the parent of the inserted node
                node->parent = cur;
                return;
            }
            //Else, move to the left child and continue
            cur = cur->left;
        }

        //If the key is greater than or equal to the current node's key
        else
        {
            //If the right child of the current node is empty, insert the node here
            if (cur->right == nullptr)
            {
                cur->right = node;

                //Set the parent of the inserted node
                node->parent = cur;
                return;
            }

            //Else, move to the right child and continue
            cur = cur->right;
        }
    }
}

//DEBUG
bool IndexedBST::remove(double key)
{
    Node* nodeToRemove = search(key);

    if (nodeToRemove == nullptr)
    {
        return false; // Key not found in the tree
    }

    // CASE 1: Node has no children
    if (nodeToRemove->left == nullptr && nodeToRemove->right == nullptr)
    {
        //Check if the node to remove is the root
        if (nodeToRemove == root)
        {
            //Set the root to null, as the tree becomes empty
            root = nullptr;
        }
        else {
            Node* parent = nodeToRemove->parent;

            // Check if the node to remove is a left or right child of its parent
            if (parent->left == nodeToRemove)
            {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
        }
    }

    // CASE 2: Node has one child
    else if (nodeToRemove->left == nullptr || nodeToRemove->right == nullptr)
    {
        // Determine which child (left or right) exists and set 'child' accordingly
        Node* child = (nodeToRemove->left != nullptr) ? nodeToRemove->left : nodeToRemove->right;

        // Check if the node to remove is the root, if so update the root to the child & set the child's parent to null.
        if (nodeToRemove == root)
        {
            root = child;
            child->parent = nullptr;
        }
        else
        {
            Node* parent = nodeToRemove->parent;

            //Check if the node to remove is a left or right child of its parent
            if (parent->left == nodeToRemove)
            {
                //Update the parent's left child
                parent->left = child;
            }
            else
            {
                //Update the parent's right child
                parent->right = child;
            }

            //Update the child's parent
            child->parent = parent;
        }
    }

    // CASE 3: Node has two children
    else 
    {
        // Find the in-order successor (the smallest node in the right subtree)
        Node* successor = nodeToRemove->right;
        
        while (successor->left != nullptr) 
        {
            successor = successor->left;
        }


        // Now, we remove the successor node (which can only be in Case 1 or Case 2)
        // Note: No recursive call here
        if (successor == successor->parent->left) 
        {
            successor->parent->left = successor->right;
        }
        else 
        {
            successor->parent->right = successor->right;
        }

        // Handle the case where the successor's right child exists
        if (successor->right != nullptr) 
        {
            successor->right->parent = successor->parent;
        }

        //Update the left size of the nodes between parent and successor
        Node* current = successor->parent;
        while (current != nullptr) {
            current->leftSize--;
            current = current->parent;
        }

        delete successor; // Delete the successor node
    }

    return true; // Successfully removed the key


}



//=======================================================//


//main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "IndexedBST.h"
using namespace std;

void testSearch(IndexedBST* tree, double key);
void testAt(IndexedBST* tree, int index);

int main()
{
    // Test insert
    double numbers[] = { 9, 4, 11, 2, 6, 15, 1, 3, 5, 8 };
    IndexedBST* tree = new IndexedBST();
    for (double number : numbers) {
        tree->insert(new Node(number));
    }

    double key;
    cout << "Enter key to search for: ";
    cin >> key;
    testSearch(tree, key);

    int index;
    cout << "Enter index: ";
    cin >> index;
    testAt(tree, index);

    // Test remove
    double keyToRemove;
    cout << endl << "Enter key to remove: ";
    cin >> keyToRemove;

    bool keyRemoved = tree->remove(keyToRemove);

    cout << "Removed key " << keyToRemove << "?: " << keyRemoved << endl;
    testSearch(tree, key);
    testAt(tree, index);

    return 0;
}

void testSearch(IndexedBST* tree, double key) {
    Node* foundNode = tree->search(key);
    if (foundNode != nullptr) {
        cout << "Found node with key = " << foundNode->key << endl;
        cout << "Left size = " << foundNode->leftSize << endl;
        if (foundNode->parent != nullptr) {
            cout << "Parent node key = " << foundNode->parent->key << endl;
            cout << "Left size = " << foundNode->parent->leftSize << endl;
        }
        if (foundNode->left != nullptr) {
            cout << "Left child node key = " << foundNode->left->key << endl;
            cout << "Left size = " << foundNode->left->leftSize << endl;
        }
        if (foundNode->right != nullptr) {
            cout << "Right child node key = " << foundNode->right->key << endl;
            cout << "Left size = " << foundNode->right->leftSize << endl;
        }
    }
    else
        cout << "Key " << key << " not found." << endl;
}

void testAt(IndexedBST* tree, int index) {
    Node* foundNode = tree->at(index);
    if (foundNode != nullptr) {
        cout << "Found node with key = " << foundNode->key << endl;
        cout << "Left size = " << foundNode->leftSize << endl;
    }
    else
        cout << "Index " << index << " not found." << endl;
}