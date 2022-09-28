#ifndef __TREE_H__
#define __TREE_H__

#define TREE_PARENT(i) ((i-1)/2) 
#define TREE_LEFT(i) (2*i+1)
#define TREE_RIGHT(i) (2*i+2)

#include <iostream>

struct node {
    struct node *left;
    struct node *right;
    int data;
};

class tree {
private:
    struct node *root;
public:
    tree();
    bool isEmpty();
    void insert(int item);
    void displayTree();
    void printTree(struct node *);
};

tree::tree() {
    root = nullptr;
}

#endif //__TREE_H__