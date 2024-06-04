/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode() {
    val = 0;
    par = nullptr;
    left = nullptr;
    right = nullptr;
}

HeapNode::HeapNode(int _val) {
    val = _val;
    par = nullptr;
    left = nullptr;
    right = nullptr;
}

HeapNode::~HeapNode(){
    delete left;
    delete right;
}