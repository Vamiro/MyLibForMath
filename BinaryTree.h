#ifndef MYLIBFORMATH_BINARYTREE_H
#define MYLIBFORMATH_BINARYTREE_H

#include <iostream>
#include <stdexcept>
#include <queue>
#include <string>

enum class Color {RED, BLACK};

template<typename TKey, typename TValue>
class BinaryTree {
public:
    BinaryTree();
    BinaryTree(const BinaryTree &other);
    BinaryTree(BinaryTree &&other) noexcept ;
    ~BinaryTree();

    virtual void Insert(const TKey &key, const TValue &value); // key < ||- > Node.key ? goLeft : goRight
    virtual void Delete(const TKey &key);
    TValue *Search(const TKey &key);

    TValue *getMin();
    TValue *getMax();
    void PrintTree();
protected:
    struct Node {
        Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
        Color color = Color::RED;
        TKey key;
        TValue* value;
    };

    Node *root = nullptr;

    Node*& FindNode(const TKey &key);
    Node* InsertNode(const TKey &key, const TValue &value);
    int GetTreeHeight(Node *node);

    void DeleteTree();
    void CopyTree();
};

template<typename TKey, typename TValue>
BinaryTree<TKey, TValue>::BinaryTree()= default;

template<typename TKey, typename TValue>
BinaryTree<TKey, TValue>::BinaryTree(const BinaryTree& other){

}

template<typename TKey, typename TValue>
BinaryTree<TKey, TValue>::BinaryTree(BinaryTree&& other) noexcept{

}

template<typename TKey, typename TValue>
BinaryTree<TKey, TValue>::~BinaryTree()= default;

template<typename TKey, typename TValue>
BinaryTree<TKey, TValue>::Node *BinaryTree<TKey, TValue>::InsertNode(const TKey &key, const TValue &value) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->value = new TValue(value);
    if (!root) {
        root = newNode;
        return newNode;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            throw std::logic_error("Key already exists");
        }
    }

    if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    newNode->parent = parent;

    return newNode;
}

template<typename TKey, typename TValue>
void BinaryTree<TKey, TValue>::Insert(const TKey &key, const TValue &value) {
    InsertNode(key, value);
}

template<typename TKey, typename TValue>
void BinaryTree<TKey, TValue>::Delete(const TKey &key) {
    Node *&nodeToDelete = FindNode(key);

    if(!nodeToDelete){
        throw std::invalid_argument("Key does not exist.");
    }
    Node *tmp = nodeToDelete;

    if(!nodeToDelete->left && !nodeToDelete->right){
        nodeToDelete = (nodeToDelete->left) ? nodeToDelete->left : nodeToDelete->right;
    } else{
        Node *min = nodeToDelete->right;

        if(min->left){
            while(min->left){
                min = min->left;
            }
            min->parent->left = min->right;
            min->right = nodeToDelete->right;
        }
        min->left = nodeToDelete->left;
        nodeToDelete = min;
    }
    delete tmp->value;
    delete tmp;
}

template<typename TKey, typename TValue>
TValue *BinaryTree<TKey, TValue>::Search(const TKey &key) {
    return FindNode(key)->value;
}

template<typename TKey, typename TValue>
TValue *BinaryTree<TKey, TValue>::getMin() {
    return 0;
}

template<typename TKey, typename TValue>
TValue *BinaryTree<TKey, TValue>::getMax() {
    return 0;
}

template<typename TKey, typename TValue>
int BinaryTree<TKey, TValue>::GetTreeHeight(Node* node) {
    if (!node) {
        return 0;
    }

    int leftHeight = GetTreeHeight(node->left);
    int rightHeight = GetTreeHeight(node->right);

    return 1 + std::max(leftHeight, rightHeight);
}

template<typename TKey, typename TValue>
void BinaryTree<TKey, TValue>::PrintTree() {
    if (!root) {
        std::cout << "Tree is empty." << std::endl;
        return;
    }

    std::queue<Node*> nodeQueue;
    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        int levelSize = nodeQueue.size();
        for (int i = 0; i < levelSize; ++i) {
            Node* current = nodeQueue.front();
            nodeQueue.pop();

            // Print the key and value
            std::cout << current->key << ": ";
            if (current->color == Color::RED) {
                std::cout << "RED";
            }
            else{
                std::cout << "BLACK";
            }
            std::cout << "   ";

            // Enqueue children for the next level
            if (current->left) {
                nodeQueue.push(current->left);
            }
            if (current->right) {
                nodeQueue.push(current->right);
            }
        }
        std::cout << std::endl;
    }
}

template<typename TKey, typename TValue>
void BinaryTree<TKey, TValue>::DeleteTree() {

}

template<typename TKey, typename TValue>
void BinaryTree<TKey, TValue>::CopyTree() {

}

template<typename TKey, typename TValue>
BinaryTree<TKey, TValue>::Node*& BinaryTree<TKey, TValue>::FindNode(const TKey &key) {
    Node** current = &root;
    while (*current) {
        if ((*current)->key == key) {
            return *current;
        } else if (key < (*current)->key) {
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }
    return *current;
}

#endif //MYLIBFORMATH_BINARYTREE_H
