// In this lab you will be implementing binary search tree as an enhancement to last week's tree traversal
// You will also be implementing the first question in your tutorial: the specific version of the binary search tree 
//which stores at each node, the height of that node. In addition, store a null terminated string (max length 32) (this is instead of the char from the earlier lab).
//The string is used for defining the ordering, based on alphabetical comparison as implemented in strcmp.
// You may find it necessary/convenient to store a pointer to the parent of each node
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <time.h>
#include <fstream>
#include <cmath>
using namespace std::chrono;
using namespace std;

struct Node {
  char *data;
  int h;            //height of subtree from current node
  Node *parent;
  Node *left;
  Node *right;

  Node()
  {
    parent = NULL;
    left = NULL;
    right =NULL;
    h = 1;
  }
  Node(char *str)
  {
    str[strlen(str)] = '\0';
    data = str;
    parent = NULL;
    left = NULL;
    right =NULL;
    h = 1;
  }
};

enum TraversalType_e { PRE_ORDER, IN_ORDER, POST_ORDER };

class BST {
 private:
  struct Node *root;
 public:

  BST()
  { root = NULL; } // Default constructor to construct empty BST

  Node *get_root()
  { return root;}

  void traverse(TraversalType_e tt, Node* current_node){

    if(tt == PRE_ORDER)
    {
        if(current_node == NULL){ return; }
        cout<<current_node->data<<" ";
        traverse(tt,current_node->left);
        traverse(tt,current_node->right);
    }
    else if(tt == POST_ORDER)
    {
        if(current_node == NULL){ return; }
        traverse(tt,current_node->left);
        traverse(tt,current_node->right);
        cout<<current_node->data<<" ";
    }
    else if(tt == IN_ORDER)
    {
        if(current_node == NULL){ return; }
        traverse(tt,current_node->left);
        cout<<current_node->data<<" "<<current_node->h<<endl; //with height
        //cout<<current_node->data<<" "<<" "; //without height
        traverse(tt,current_node->right);
    }
  }

  //---- Lab4 functions start here ----//
  int calch(struct Node *n)
  {
    if(n->left!=NULL && n->right!=NULL)
    {
      if (n->left->h < n->right->h)
        return n->right->h + 1;
      else 
        return  n->left->h + 1;
    }
    
    else if(n->left && n->right == NULL)
    { return n->left->h + 1;}
    
    else if(n->left ==NULL && n->right)
    { return n->right->h + 1;}
    
    else
      return 1;
  }

  // Min and Max nodes in the BST
  struct Node *min(struct Node *current_node){
    while(current_node->left!=NULL)
    {
      current_node = current_node->left;
    }
    return current_node;
  }
  struct Node *max(struct Node *current_node){
    while(current_node->right!=NULL)
    {
      current_node = current_node->right;
    }
    return current_node;
  }

  // Search for a given character; return a pointer to the node; NULL if no such string found
  struct Node *search(char *s, struct Node *current_node){
    if(current_node == NULL)
      return NULL;
    else if(strcmp(current_node->data,s)==0)
      return current_node;
    else if(strcmp(current_node->data,s)>0)
      return search(s,current_node->left);
    else                                      //if(strcmp(current_node->data,s)<0)
      return search(s,current_node->right);
  }

  // Insert the given node in the BST; return true if success; false if already exists (don't insert duplicates)
  bool insert(struct Node *n)
  {
    Node *duplicate = search(n->data,root);

    if(root == NULL)     //first insertion of the BST
    {
      root = new Node;
      root = n;
      root->h = calch(root);
      return true;
    }

    else if(duplicate!=NULL)      //Node already exists
      return false;       

    else
    {
      Node *current_node = root;
      Node *prev_node;
      char *s = n->data;
      while(current_node!=NULL)
      {
          prev_node = current_node;
          if(strcmp(current_node->data,s)>0)
          { current_node = current_node->left; }

          else if(strcmp(current_node->data,s)<0)
          { current_node = current_node->right; }
      }

      current_node = prev_node;
      n->parent = current_node;

      if(strcmp(current_node->data,s)>0)
      { 
        current_node->left = n;
        current_node = current_node->left;
      }

      else if(strcmp(current_node->data,s)<0)
      {
        current_node->right = n; 
        current_node = current_node->right;
      }

      while(current_node!=NULL)             //updating height
      {
        current_node->h = calch(current_node);
        current_node = current_node->parent;
      }

      return true;
    }
  }  
  // Delete the given character from the BST; return true if success; false if not found
  bool remove(char *s){
    Node *z = search(s,root);        // z is node to be deleted
    if(z == NULL)
    { return false; }

    else
    { Node *x;
      if(z->left==NULL && z->right==NULL)     // z is a leaf
      {
        if(z->parent->right == z)
          z->parent->right = NULL;
        else if(z->parent->left == z)
          z->parent->left = NULL;
        
        x = z->parent; 
        z->parent = NULL;
        z = x;
      }
      else if(z->left==NULL || z->right==NULL)      // z is a node with one child
      {
        Node *child;
        if(z->left == NULL)
          child = z->right;
        else
          child = z->left;

        if(z->parent->right == z)
          z->parent->right = child;
        else
          z->parent->left = child;

        child->parent = z->parent;
        
        x = z->parent; 
        z->parent = NULL;
        z = x;
      }
      else                                      // z is a node with 2 children
      {
        Node *succ = successor(z);;
        if(succ ==  NULL)
        { succ = predecessor(z); }
        remove(succ->data);
        z->data = succ->data;
      }

      while(z!=NULL)
      {
        z->h = calch(z);
        z = z->parent;
      }
      return true;
    }

  }
  // Return the successor of the given node; NULL if no successor exists
  struct Node *successor(struct Node *n)
  {
    if(max(root) == n)
      { return NULL; } 

    else if(n->right !=NULL)
      { return min(n->right);}

    Node *y = n->parent;
    while(y!=NULL && n==y->right)
    {
      n = y;
      y = y->parent;
    }
    return y;
  }
  // Return the predecessor of the given node; NULL if no predecessor exists
  struct Node *predecessor(struct Node *n)
  {
    if(min(root) == n)
      { return NULL; }

    else if(n->left !=NULL)
      { return max(n->left);}

    Node *y = n->parent;
    while(y!=NULL && n==y->left)
    {
      n = y;
      y = y->parent;
    }
    return y;
  }
};

int main(){

  BST T;
  int n;
  cout<<"For printing inorder with heights of each node, uncomment code in traversal()\n";
  cout<<"Enter number of strings to insert into BST: ";
  cin>>n;
  for(int i=0;i<n;i++)
  {
    Node *e;
    e = new Node;
    e->data = new char[32];
    cin>>e->data;
    *(e->data+strlen(e->data)) = '\0';
    T.insert(e);
  }
  TraversalType_e tt;
  tt = IN_ORDER;
  T.traverse(tt,T.get_root());
}
// Implement the above in BST.cpp
// Also include the main() function in BST.cpp
// In the main function, you can read one string after another, insert them
// Check that the in-order traversal gives strings in sorted order
// Also check that the height of each node is correct

// Next, plot a graph of time to insert vs size of tree
// Compare the shape of this plot with nlog(n) in the same graph
// For this, you may find it convenient to insert random strings, say a million of them, in a loop, and compute+store the time taken for each insert operation, then later plot
// You can just generate random int/float values and convert them to strings of certain length

// Optional: (a) insert a milion strings (b) delete each of them
// Compare the memory occupied by your program, before insertion, after insertion, and after deletion (you can put a sleep(30) or cin in-between); you can use the linux top command for this
// If you do not delete memory carefully, you will likely be leaking memory, which can cause the program/system to crash; if you are adventerous, make it crash your laptop

