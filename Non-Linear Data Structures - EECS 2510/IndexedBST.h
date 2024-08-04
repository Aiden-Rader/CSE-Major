#ifndef INDEXEDBST_H
#define INDEXEDBST_H

class Node 
{
public:
    double key;
    int leftSize = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    Node(double nodeKey) 
    {
        key = nodeKey;
    }
};

class IndexedBST
{
public:
    IndexedBST() {};
    Node* search(double desiredKey);
    void insert(Node* node);
    bool remove(double key);
    Node* at(int index);

private:
    Node* root = nullptr;
};

#endif // !INDEXEDBST_H