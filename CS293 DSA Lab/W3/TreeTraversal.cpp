#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
// In this lab you will be implementing binary tree traversal, and also the algorithm to deduce the tree given pre-order and in-order traversal
// For these, we will be implementing a tree where each node stores a character

struct Node {
  char val;
  Node *left;
  Node *right;
  Node()
  {
    left = NULL;
    right = NULL;
  }
  Node(char c)
  {
    val = c;
    left = NULL;
    right = NULL;
  }
};

enum TraversalType_e { PRE_ORDER, IN_ORDER, POST_ORDER };

class Tree {
 private:
  struct Node *root;
  
 public:
    bool tree_possible;
  Tree() // Default constructor to construct empty tree
  { root = NULL; 
    tree_possible = true;}

  Tree(char *pre_order, char *in_order, int N) {
    tree_possible = true;
    root = deduce_tree(pre_order, in_order, N);
    int post_order_len = 0; 
    trav2(root,post_order_len);
    if(post_order_len != N)
    {
        tree_possible = false;
        root = NULL;
    }
    //check length of post-order and pre-orer traversal here, if they match then the tree is possible else set root=NULL
  }

  int find_index_root(char c,char *in_order,int N)
  {
    for(int i=0;i<N;i++)
    {
        if(*(in_order+i)==c)
            return i;
    }
    return -1;
  }

  struct Node *deduce_tree(char *pre_order, char *in_order, int N){
    if(N==0)
    {
        return NULL;
    }
    else
    {
        Node *root_node;
        char *pre_order_left; char *in_order_left; int n_left;
        char *pre_order_right; char *in_order_right; int n_right;

        root_node = new Node;
        root_node->val = *(pre_order);

        int index_root = find_index_root(root_node->val,in_order,N);
        if(index_root == -1)
            return NULL;
        n_left = index_root;
        n_right = N - index_root - 1;

        pre_order_left = new char[n_left];
        in_order_left = new char[n_left];
        pre_order_right = new char[n_right];
        in_order_right = new char[n_right];

        int i;
        for(i=0;i<n_left;i++)
        {
            *(in_order_left+i) = *(in_order+i);
            *(pre_order_left+i) = *(pre_order+1+i);
        }
        *(in_order_left+i) = '\0';
        *(pre_order_left+i)= '\0';

        for(i=0;i<n_right;i++)
        {
            *(in_order_right+i) = *(in_order+index_root+1+i);
            *(pre_order_right+i) = *(pre_order+1+n_left+i);
        }
        *(in_order_right+i) = '\0';
        *(pre_order_right+i)= '\0';

        root_node->left = deduce_tree(pre_order_left,in_order_left,n_left);
        root_node->right = deduce_tree(pre_order_right,in_order_right,n_right);
        return root_node;
    }
  }

  Node *get_root()
  { return root;}

  // Traverse the tree as per the given traversal type; this function must be recursive
  void traverse(TraversalType_e tt, Node* current_node){

    if(tt == PRE_ORDER)
    {
        if(current_node == NULL){ return; }
        cout<<current_node->val<<" ";
        traverse(tt,current_node->left);
        traverse(tt,current_node->right);
    }
    else if(tt == POST_ORDER)
    {
        if(current_node == NULL){ return; }
        traverse(tt,current_node->left);
        traverse(tt,current_node->right);
        cout<<current_node->val<<" ";
    }
    else if(tt == IN_ORDER)
    {
        if(current_node == NULL){ return; }
        traverse(tt,current_node->left);
        cout<<current_node->val<<" ";
        traverse(tt,current_node->right);
    }
  }
  void trav2(Node* current_node,int &count)
    {
        if(current_node == NULL){ return; }
        trav2(current_node->left,count);
        count++;
        trav2(current_node->right,count);
    }
};

int main()
{
    char *pre_order;
    char *in_order;
    pre_order = new char[100];
    in_order = new char[100];

    cout<<"Enter pre-order traversal: ";
    cin>>pre_order;
    cout<<"Enter in-order traversal: ";
    cin>>in_order;
    *(pre_order+strlen(pre_order)) = '\0';
    *(in_order+strlen(pre_order)) = '\0';

    int N = strlen(pre_order);

    Tree t(pre_order, in_order, N);
    TraversalType_e tt;
    tt = POST_ORDER;
    cout<<"Post-order traversal is: ";
    if(t.tree_possible)
        t.traverse(tt,t.get_root());
    else{
        cout<<"Tree not possible"<<endl;
    }
    return 0;

}

// Implement the above in TreeTraversal.cpp
// Also include the main() function in TreeTraversal.cpp
// In the main function, you can read two strings; you can assume that they each have unique characters, but check that their lengths are the same
// The first string will represent the pre-order traversal of the tree and the second will represent the in-order traversal
// You have to construct the tree using the suitable non-default constructor
// Then print its post-order traversal as a string
// Beware of null termination before printing strings!
