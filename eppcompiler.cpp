/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){
    memory_size = 0;
    output_file = "";
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit) {
    memory_size = mem_limit;
    output_file = out_file;
    for (int i=0;i< mem_limit;i++){
        mem_loc.push_back(i);
    }
}
void targrecursive(ExprTreeNode* node, Parser& targ,vector<string>&res){
    if(node==NULL){
        return;
    }
    targrecursive(node->right,targ,res);
    targrecursive(node->left,targ,res);
     if (node->type == "VAL") {
        res.push_back("PUSH " + to_string(node->num));
     }else if(node->type=="VAR"){
        int address= targ.symtable->search(node->id);
          if (address==-2){
                address = targ.last_deleted;
            }
            res.push_back("PUSH mem[" + to_string(address) + "]");
     }else if (node->type == "ADD") {
        res.push_back("ADD");
    } else if (node->type == "SUB") {
        res.push_back("SUB");
    } else if (node->type == "MUL") {
        res.push_back("MUL");
    } else if (node->type == "DIV") {
        res.push_back("DIV");
    }

}
void EPPCompiler::compile(vector<vector<string>> code){
           // Assuming outfile is a member variable
    ofstream outfile(output_file, ios::app);

    for (const vector<string>& expression : code) {
        targ.parse(expression);
        ExprTreeNode* n = targ.expr_trees.back();

        if (n->left->type == "VAR") {
            if (targ.symtable->search(n->left->id) == -1) {
                int address = mem_loc.back();
                mem_loc.pop_back();
                targ.symtable->assign_address(n->left->id, address);
            }
        }

        if (targ.expr_trees.back()->left->type == "DEL") {
            mem_loc.push_back(targ.last_deleted);
        }

        vector<string> result;
        targrecursive(targ.expr_trees.back()->right, targ,result);
        string target;
        if (targ.expr_trees.back()->left->type == "DEL") {
            int address = targ.last_deleted;
            target = "DEL = mem[" + to_string(address) + "]";
        }else if(targ.expr_trees.back()->left->type == "RET"){
            target = "RET = POP";
        }else if (targ.expr_trees.back()->left->type == "VAR"){
               int address = targ.symtable->search(targ.expr_trees.back()->left->id);
               target= "mem[" + to_string(address) + "] = POP" ;
        }
        result.push_back(target);

        write_to_file(result);
    }
    outfile.close();
}

vector<string> EPPCompiler::generate_targ_commands() {
    
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream outfile(output_file,ios::app);
    for (const auto& command : commands) {
        outfile << command << endl;
    }
    outfile.close();
}

EPPCompiler::~EPPCompiler(){
    // clearParserState(targ);
}
// #include <iostream>
// #include "parser.cpp"
// #include "symtable.cpp"
// #include "exprtreenode.cpp"
// #include "symnode.cpp"
// #include "minheap.cpp"
// #include "heapnode.cpp"
// using namespace std;
// int main(){
//     string out="hello.txt";
//     int m=100;
//     EPPCompiler E=EPPCompiler(out,m);
//     vector<string> s1={"x",":=","3"};
//     vector<string> s2={"y",":=","2"};
//     vector<string> s3={"z",":=","(","x","-","y",")"};
//     vector<string> s8={"ret",":=","z"};
//     vector<string> s4={"del",":=","x"};
//     vector<string> s5={"del",":=","y"};
//     vector<string> s6={"w",":=","(","5","+","(","z","/","2",")",")"};
//     vector<string> s7={"ret",":=","v"};
//     vector<vector<string>> v={s1,s2,s3,s8};
//     E.compile(v);
//     cout<<"ok";
// }