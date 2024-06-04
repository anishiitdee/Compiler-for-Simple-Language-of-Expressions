/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

int getHeight1(SymNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int getBalance(SymNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight1(node->left) - getHeight1(node->right);
}

SymNode* leftRotate(SymNode* x) {
    SymNode* y = x->right;
    SymNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight1(x->left), getHeight1(x->right)) + 1;
    y->height = max(getHeight1(y->left), getHeight1(y->right)) + 1;
    y->par = x->par;
    x->par = y;
    if (T2 != nullptr) {
        T2->par = x;
    }

    return y;
}

SymNode* rightRotate(SymNode* y) {
    SymNode* x = y->left;
    SymNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight1(y->left), getHeight1(y->right)) + 1;
    x->height = max(getHeight1(x->left), getHeight1(x->right)) + 1;
    x->par = y->par;
    y->par = x;
    if (T2 != nullptr) {
        T2->par = y;
    }
    return x;
}
SymNode* balance (SymNode* node) {
    if (node == nullptr) {
        return nullptr;
    }

    node->height = max(getHeight1(node->left), getHeight1(node->right)) + 1;

    int balance = getBalance(node);

    if (balance > 1) {
        if (getBalance(node->left) >= 0) {
            return rightRotate(node);
        } else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    if (balance < -1) {
        if (getBalance(node->right) <= 0) {
            return leftRotate(node);
        } else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}
SymNode* findMin(SymNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

SymNode* recursiveRemove(SymNode* node, string k) {
    if (node == nullptr) {
        return nullptr;
    }

    if (k < node->key) {
        node->left = recursiveRemove(node->left, k);
    } else if (k > node->key) {
        node->right = recursiveRemove(node->right, k);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            SymNode* temp = (node->left != nullptr) ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            SymNode* successor = findMin(node->right);
            node->key = successor->key;
            node->right = recursiveRemove(node->right, successor->key);
        }
    }

    if (node == nullptr) {
        return nullptr;
    }

    node->height = 1 + max(getHeight1(node->left), getHeight1(node->right));
    return balance(node);
}

SymNode* recursiveSearch(SymNode* node, string k) {
    if (node == nullptr || node->key == k ) {
        return node;
    }

    if (k < node->key) {
        return recursiveSearch(node->left, k);
    }

    return recursiveSearch(node->right, k);
}

SymNode* recursiveInsert(SymNode* node, string k) {
    if (node == nullptr) {
        return new SymNode(k);
    }

    if (k < node->key) {
        node->left = recursiveInsert(node->left, k);
    } else if (k > node->key) {
        node->right = recursiveInsert(node->right, k);
    }

    return balance(node);
}

void recursiveDelete(SymNode* node) {
    if (node == nullptr) {
        return;
    }
    recursiveDelete(node->left);
    recursiveDelete(node->right);
    delete node;
}

SymbolTable::SymbolTable() {
    size = 0;
    root = nullptr;
}

SymbolTable::~SymbolTable() {
    recursiveDelete(root);
    size = 0;
    root = nullptr;
}

void SymbolTable::insert(string k) {
    root = recursiveInsert(root, k);
    size++;
}

void SymbolTable::remove(string k) {
    root = recursiveRemove(root, k);
    size--;
}

int SymbolTable::search(string k) {
    SymNode* result = recursiveSearch(root, k);
    return (result != nullptr) ? result->address : -2;
}

int SymbolTable::get_size() {
    return size;
}

SymNode* SymbolTable::get_root() {
    return root;
}

void SymbolTable::assign_address(string k, int idx) {
    SymNode* node = recursiveSearch(root, k);
    if (node != nullptr) {
        node->address = idx;
    }
}



