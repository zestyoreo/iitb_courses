#include "tree.hpp"
#include "assert.h"
 
bool tree::isEmpty() {
    return root==nullptr;
}

void tree::insert(int item) {
    struct node *p = new struct node;
    p->data=item;
    p->left=nullptr;
    p->right=nullptr;

    struct node *parent;
    parent=nullptr;

    if(isEmpty())
        root=p;
    else {
        struct node *ptr;
        ptr=root;
        while(ptr!=nullptr) {
            parent=ptr;
            if(item > ptr->data)        
                ptr = ptr->right;
            else
                ptr = ptr->left;
        }   
        if(item < parent->data)
            parent->left = p;
        else
            parent->right = p;
    }
}

void tree::displayTree(){
    printTree(root);
    std::cout << std::endl;
}

void tree::printTree(struct node *ptr){
    if(ptr != nullptr){
        printTree(ptr->left);
        std::cout << " " << ptr->data << " ";
        printTree(ptr->right);
    }
}

int main(int argc, char* argv[]){
    assert (argc > 1);
    tree b;
    for (size_t i = 0; i < argc-1; i++) 
        b.insert(atoi(argv[i+1]));

GDBBREAKPOINT:

    b.displayTree();
    return 0;
}