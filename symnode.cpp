#include "symnode.h"

int getHeight(SymNode* node) {
    return (node == nullptr) ? 0 : node->height;
}

SymNode::SymNode() {
    left = right = par = nullptr;
    height = 1;
}

SymNode::SymNode(string k) {
    key = k;
    left = right = par = nullptr;
    height = 1;
}

SymNode* SymNode::LeftLeftRotation() {
    SymNode* newRoot = right;
    right = newRoot->left;
    newRoot->left = this;
    height = max(getHeight(left), getHeight(right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

SymNode* SymNode::RightRightRotation() {
    SymNode* newRoot = left;
    left = newRoot->right;
    newRoot->right = this;
    height = max(getHeight(left), getHeight(right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

SymNode* SymNode::LeftRightRotation() {
    right = right->RightRightRotation();
    return LeftLeftRotation();
}

SymNode* SymNode::RightLeftRotation() {
    left = left->LeftLeftRotation();
    return RightRightRotation();
}

SymNode::~SymNode() {
     if (left != nullptr) {
        delete left;
    }
    if (right != nullptr) {
        delete right;
    }
}
