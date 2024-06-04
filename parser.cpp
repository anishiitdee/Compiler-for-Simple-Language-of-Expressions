/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"


// #include "symtable.cpp"
// #include "exprtreenode.cpp"
// #include "symnode.cpp"
//Write your code below this line
bool isVariable(const string& str) {
    return isalpha(str[0]);
}
Parser::Parser(){
    symtable = new SymbolTable();
    last_deleted = -1;
}

void Parser::parse(vector<string> tokens) {
    vector<ExprTreeNode*> nodeStack;
    vector<string> tokenStack;
    for (int i = 0; i < tokens.size(); ++i) {
        if (i == 0) {
            ExprTreeNode* newNode = new ExprTreeNode;
            if (tokens[i] == "ret") { 
                newNode->type = "RET";
            } else if (tokens[i] == "del") {  
                newNode->type = "DEL";
            }else{
            newNode->type = "VAR";
            newNode->id = tokens[i];
            symtable->insert(tokens[i]);
            }
            nodeStack.push_back(newNode);
            
        } else if (i == 1) {
            ExprTreeNode* newNode = new ExprTreeNode;
            newNode->type = "";
            nodeStack.push_back(newNode);
        } else if (tokens[i] == "(") {
            tokenStack.push_back("(");
        } else if (tokens[i] == ")") {
            tokenStack.pop_back();
            ExprTreeNode* newNode = nodeStack[nodeStack.size() - 2];
            newNode->right = nodeStack.back();
            newNode->left = nodeStack[nodeStack.size() - 3];
            nodeStack.pop_back();
            nodeStack.pop_back();
            nodeStack.pop_back();
            nodeStack.push_back(newNode);
        } else {
            if (tokens[i] == "+") {
                ExprTreeNode* newNode = new ExprTreeNode;
                newNode->type = "ADD";
                nodeStack.push_back(newNode);
            } else if (tokens[i] == "-") {
                ExprTreeNode* newNode = new ExprTreeNode;
                newNode->type = "SUB";
                nodeStack.push_back(newNode);
            } else if (tokens[i] == "*") {
                ExprTreeNode* newNode = new ExprTreeNode;
                newNode->type = "MUL";
                nodeStack.push_back(newNode);
            } else if (tokens[i] == "/") {
                ExprTreeNode* newNode = new ExprTreeNode;
                newNode->type = "DIV";
                nodeStack.push_back(newNode);
            } else if (tokens[i] == "%") {
                ExprTreeNode* newNode = new ExprTreeNode;
                newNode->type = "MOD";
                nodeStack.push_back(newNode);
            } else if (isVariable(tokens[i])) {
                ExprTreeNode* newNode = new ExprTreeNode;
                newNode->type = "VAR";
                newNode->id = tokens[i];
                nodeStack.push_back(newNode);
            }else {
                int intValue = stoi(tokens[i]);
                ExprTreeNode* newNode = new ExprTreeNode("VAL", intValue);
                nodeStack.push_back(newNode);
            }
        }
    }
    if (nodeStack.size() >= 3) {
      nodeStack[1]->left=nodeStack[0];
      nodeStack[1]->right=nodeStack[2];
      expr_trees.push_back(nodeStack[1]);
      if (nodeStack[0]->type == "DEL") {
                last_deleted =symtable->search(nodeStack[2]->id);
                symtable->remove(nodeStack[2]->id);
        }
      nodeStack.pop_back();
      nodeStack.pop_back();
      nodeStack.pop_back();
    }
}
    
Parser::~Parser(){
  for (ExprTreeNode* node : expr_trees) {
        delete node;
    }
    // delete symtable;
}
