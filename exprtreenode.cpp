/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type = "";
    num = 0;
    left = nullptr;
    right = nullptr;
    id="";
}

ExprTreeNode::ExprTreeNode(string t,int v) {
    type = t;
    num = v;
    left = nullptr;
    right = nullptr;
    id="";
}

ExprTreeNode::~ExprTreeNode(){
    delete left;
    delete right;
}

