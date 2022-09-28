#include<iostream>

using namespace std;

struct node
{
  int key_value;
  node *left;
  node *right;
};


class btree
{
    public:
        btree();
        ~btree();
 
        void insert(int key);
        node *search(int key);
        void destroy_tree();
    
    private:
        void destroy_tree(node *leaf);
        void insert(int key, node *leaf);
        node *search(int key, node *leaf);
        node *root;
};

btree::btree()
{
  root=NULL;
}

btree::~btree()
{
  destroy_tree();
}

void btree::destroy_tree(node *leaf)
{
  if(leaf!=NULL)
  {
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
}

void btree::insert(int key, node *leaf)
{
  if(key< leaf->key_value)
  {
    if(leaf->left!=NULL)
     insert(key, leaf->left);
    else
    {
      leaf->left=new node;
      leaf->left->key_value=key;
      leaf->left->left=NULL;    //Sets the left child of the child node to null
      leaf->left->right=NULL;   //Sets the right child of the child node to null
    }  
  }
  else if(key>=leaf->key_value)
  {
    if(leaf->right!=NULL)
      insert(key, leaf->right);
    else
    {
      leaf->right=new node;
      leaf->right->key_value=key;
      leaf->right->left=NULL;  //Sets the left child of the child node to null
      leaf->right->right=NULL; //Sets the right child of the child node to null
    }
  }
}

node *btree::search(int key, node *leaf)
{
  if(leaf!=NULL)
  {
    if(key==leaf->key_value)
      return leaf;
    if(key<leaf->key_value)
      return search(key, leaf->left);
    else
      return search(key, leaf->right);
  }
  else return NULL;
}

void btree::insert(int key)
{
  if(root!=NULL)
    insert(key, root);
  else
  {
    root=new node;
    root->key_value=key;
    root->left=NULL;
    root->right=NULL;
  }
}

node *btree::search(int key)
{
  return search(key, root);
}

void btree::destroy_tree()
{
  destroy_tree(root);
}

int main ()
{
   int a [10] = {5,3,9,6,8,23,4,12,1,7};
   btree bt;
   for (int i=0; i<10; i++)
   {
	   bt.insert(a[i]);	   

   };
   return 0;
}
