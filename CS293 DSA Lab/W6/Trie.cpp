/*
  Trie.cpp
  Data Structures and Algorithms Lab - CS293
  Author: P Balasubramanian
  Rollno: 200050103
*/  

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>
using namespace std;
const int ALPHABET_SIZE = 26;

struct Trie_node {

  struct Trie_node *children[ALPHABET_SIZE+1];
  int word[3];

  Trie_node(){
    children = new Trie_node[ALPHABET_SIZE+1];
    for (int i = 0; i < ALPHABET_SIZE+1; ++i)
    {
      children[i] = NULL;
    } 
  }

};
class Trie {
public:
  Trie_node root;
  void insert(int s_no, char a[100])
  {
    
  }
}

int main(){


}

