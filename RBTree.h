#ifndef MYLIBFORMATH_RBTREE_H
#define MYLIBFORMATH_RBTREE_H

#include "BinaryTree.h"

template<typename TKey, typename TValue>
class RBTree : public BinaryTree<TKey, TValue> {
public:
    RBTree() : BinaryTree<TKey, TValue>() {}
    RBTree(const RBTree &other) : BinaryTree<TKey, TValue>(other) {}
    RBTree(RBTree &&other) : BinaryTree<TKey, TValue>(other) {}
    ~RBTree();

    void Insert(const TKey &key, const TValue &value) override;
    void Delete(const TKey &key) override;

private:
    typedef BinaryTree<TKey, TValue>::Node Node;

    Node* grandparent(Node *node);
    Node* uncle(Node *node);

    void TurnLeft(Node *node);
    void TurnRight(Node *node);
    void FixInsert(Node *node);
    void FixDelete(Node *node);
};

template<typename TKey, typename TValue>
RBTree<TKey, TValue>::~RBTree()= default;

template<typename TKey, typename TValue>
RBTree<TKey, TValue>::Node *RBTree<TKey, TValue>::grandparent(RBTree::Node *node) {
    if (node != nullptr && node->parent != nullptr)
        return node->parent->parent;
    else
        return nullptr;
}

template<typename TKey, typename TValue>
RBTree<TKey, TValue>::Node *RBTree<TKey, TValue>::uncle(RBTree::Node *node) {
    Node *g = grandparent(node);

    if (g == nullptr)
        return nullptr;

    if (node->parent == g->left)
        return g->right;
    else
        return g->left;
}

template<typename TKey, typename TValue>
void RBTree<TKey, TValue>::Insert(const TKey &key, const TValue &value) {
    Node *newNode = BinaryTree<TKey, TValue>::InsertNode(key, value);
    FixInsert(newNode);
}

template<typename TKey, typename TValue>
void RBTree<TKey, TValue>::FixInsert(RBTree::Node *node) {
    if (node->parent == nullptr){
        node->color = Color::BLACK;
    }
    else if (node->parent->color == Color::RED) {
        Node *g = grandparent(node);
        Node *u = uncle(node);

        if(u != nullptr && u->color == Color::RED) {
            node->parent->color = Color::BLACK;
            u->color = Color::BLACK;
            g->color = Color::RED;
            FixInsert(g);
        }
        else{
            if (node == node->parent->right && node->parent == g->left)
            {
                TurnLeft(node->parent);
                node = node->left;
            }
            else if (node == node->parent->left && node->parent == g->right)
            {
                TurnRight(node->parent);
                node = node->right;
            }
            node->parent->color = Color::BLACK;
            g->color = Color::RED;
            if (node == node->parent->left && node->parent == g->left)
            {
                TurnRight(g);
            }
            else
            {
                TurnLeft(g);
            }
        }
    }
}

template<typename TKey, typename TValue>
void RBTree<TKey, TValue>::Delete(const TKey &key) {
    BinaryTree<TKey, TValue>::Delete(key);
}


template<typename TKey, typename TValue>
void RBTree<TKey, TValue>::TurnLeft(RBTree::Node *node) {
    Node *pivot = node->right;
    pivot->parent = node->parent;

    if (node == this->root) this->root = pivot;

    if (node->parent != nullptr) {
        if (node->parent->left == node)
            node->parent->left = pivot;
        else
            node->parent->right = pivot;
    }
    node->right = pivot->left;

    if (pivot->left != nullptr)
        pivot->left->parent = node;

    node->parent = pivot;
    pivot->left = node;
}

template<typename TKey, typename TValue>
void RBTree<TKey, TValue>::TurnRight(RBTree::Node *node) {
    Node *pivot = node->left;
    pivot->parent = node->parent;

    if (node == this->root) this->root = pivot;

    if (node->parent != nullptr) {
        if (node->parent->left == node)
            node->parent->left = pivot;
        else
            node->parent->right = pivot;
    }

    node->left = pivot->right;
    if (pivot->right != nullptr)
        pivot->right->parent = node;

    node->parent = pivot;
    pivot->right = node;
}

template<typename TKey, typename TValue>
void RBTree<TKey, TValue>::FixDelete(RBTree::Node *node) {

}

#endif //MYLIBFORMATH_RBTREE_H
