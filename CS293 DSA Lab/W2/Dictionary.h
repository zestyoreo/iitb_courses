#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
using namespace std;
// In this lab you will implement a dictionary of strings (each string is null terminated, of max length 32 including the null)

// The hash code map should use a polynomial accumulation scheme as mentioned in the lecture video

// The compression map should use the Fibonacci hashing scheme as mentioned in the lecture video

// IMPORTANT: DO NOT compute the polynomial value at one go, it will overflow the integer limit. You need to compute 'k' in various stages, starting from the inner-most bracket (see slides), and in each step take mod 1. 
//Note that mathematically [A*(alpha + beta * x)] mod 1 is the same as { [A*alpha] mod 1 + [A*beta*x] mod 1 } mod 1.

// You can use a fixed size of the array of a power of 2 (no need to grow)

// To resolve hash collisions, use the simple linear probing scheme (use the next unused slot in array), with NULL and TOMBSTONE markers as described in the lecture slides

// We will use the dictionary to count the frequency of words in a given text: you must define suitable fields in struct Entry for this purpose

// FILES
// Dictionary.cpp : implement the Dictionary class methods here
// main.cpp : write code here to read STDIN one word after another: cin>>str should do it (you can assume each word is at most 31 characters)
// During demo to TA: main.cpp should print hash value of each string and also relevant steps in findFreeIndex, also finally print frequency of each input word
// Extra/optional: write code to generate random strings, and show how well your hash+compression map is working

// You can change this array size if you want
#define ARRAY_SIZE (1<<6)

struct Entry {
  char *key;    //the string/word
  int frequency;
};

double mod_1(double y)
{
  return (y-floor(y));
}

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char *key)
  {
    double a,x=33;
    a = (sqrt(5)-1)/2;
    double h = 0;
    for(int i=strlen(key)-1;i>=0;i--)
    {
      h = mod_1(mod_1(x*h)+mod_1(a*int(*(key+i))));
    }
    int h_k = floor(N*h);
    return h_k;
  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char *key)
  {
    int hash = hashValue(key);
    cout<<"Hash is: "<<hash<<endl;
    int i = hash;
    while(true)
    {
      if(!(strcmp((A+i)->key,key)))
      {
        return -1;
      }
      if(*((A+i)->key)=='!' || *((A+i)->key)=='$')
       { cout<<"Found an empty slot in index: "<<i<<endl;
        return i;}
      else
      {
        i++;
        if(i == hash)
          return -1;
        if(i>=N)
        {i=0;}
      }

    }
  }
 public:
  Dictionary() // Default constructor
  {
    N = int(ARRAY_SIZE);
    A = new Entry[N];//'!' is null and '$' is a tombstone
    for(int i=0;i<N;i++)
      { 
        (A+i)->key = new char[32];
        *((A+i)->key) = '!';
      }
  }
  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char *key)
  {
    int hash = hashValue(key);
    while(*((A+hash)->key)!= '!')
    {
      if(!(strcmp((A+hash)->key,key)))
      {
        return (A+hash);
      }
    }
    return NULL;
  }
  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e)
  {
    int index = findFreeIndex(e.key);
    if(index==-1)
    { 
      if(get(e.key) == NULL)
      {
        cout<<"Array is full."<<endl;
        return false;}
      else
      {
        Entry *p = get(e.key);
        (p->frequency)+=1;
        cout<<"Entry frequency increased."<<endl;
        return true;
      }  
    }  
    else
    {
      cout<<"The Entry is inserted at index: "<<index<<endl;
      *(A+index) = e;
      return true;
    }
  }

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char *key){
    Entry *p = get(key);
    if(p == NULL)
      return false;
    else
    {
      if(p->frequency==1)
      {
        (p->frequency)--;
        *(p->key) = '!';
        return true;
      }
      else{
        (p->frequency)--;
        return false;
      }
    }
  }
};

#endif
