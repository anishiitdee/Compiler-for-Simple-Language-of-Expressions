/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

void destroyHeap(HeapNode* node) {
    if (node != nullptr) {
        destroyHeap(node->left);
        destroyHeap(node->right);
        delete node;
    }
}
HeapNode* merge(HeapNode* h1, HeapNode* h2) {
    if (h1 == nullptr) return h2;
    if (h2 == nullptr) return h1;
    
    if (h1->val > h2->val) {
        std::swap(h1, h2);
    }

    h1->right = merge(h1->right, h2);

    std::swap(h1->left, h1->right);

    return h1;
}
MinHeap::MinHeap() {
    size = 0;
    root = nullptr;
}

void MinHeap::push_heap(int num){
    HeapNode* newNode = new HeapNode(num);
    root = merge(root, newNode);
    size++;
}

int MinHeap::get_min(){
    if (root == nullptr) {
        return -1; 
    }

    return root->val;
}

void MinHeap::pop(){
    if (root == nullptr) {
        return;
    }
    HeapNode* oldRoot = root;
    root = merge(root->left, root->right);
    delete oldRoot;
    size--;
}

MinHeap::~MinHeap(){
    destroyHeap(root);
}