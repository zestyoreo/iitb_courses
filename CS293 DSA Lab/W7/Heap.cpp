/*
  Heap.cpp
  Data Structures and Algorithms Lab - CS293
  Author: P Balasubramanian
  Rollno: 200050103
*/  
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <time.h>
#include <fstream>
using namespace std::chrono;
using namespace std;

class Heap
{
  int heap[1000002];
  long long empty_pos;

  int parent_of(int index)
  {return (floor((index+1)/2)-1);}
  int left_child_of(int index)
  {return ((2*(index+1))-1);}
  int right_child_of(int index)
  {return (2*(index+1));}
  int min()
  {return heap[0];}
public:
  Heap()
  {empty_pos=0;}
  bool insert(int new_elem,long long& swaps)
  {
    heap[empty_pos]=new_elem;
    if(empty_pos==0)
    {
      empty_pos++;
      return true;
    }
    int pos_of_new_elem=empty_pos;

    while(pos_of_new_elem!=0 && heap[parent_of(pos_of_new_elem)]>new_elem)
    {
      int temp=heap[parent_of(pos_of_new_elem)];
      heap[parent_of(pos_of_new_elem)] = new_elem;
      heap[pos_of_new_elem] = temp;
      pos_of_new_elem = parent_of(pos_of_new_elem);
      swaps++;
    }
    empty_pos++;
    return true;
  }
  void heapify(int pos,long long& swaps)
  {
    int index=pos;

    while( (right_child_of(index)<empty_pos && left_child_of(index)<empty_pos) || (right_child_of(index)<empty_pos && heap[index]>heap[right_child_of(index)]) || (left_child_of(index)<empty_pos && heap[index]>heap[left_child_of(index)]) )
    {
      int temp = heap[index];
      if(heap[right_child_of(index)]<heap[left_child_of(index)])
      {
        heap[index] = heap[right_child_of(index)];
        heap[right_child_of(index)] = temp;
        index = right_child_of(index);
        swaps++;
      }
      else
      {
        heap[index] = heap[left_child_of(index)];
        heap[left_child_of(index)] = temp;
        index = left_child_of(index);
        swaps++;
      }
    }
  }
  int del_min(long long& swaps)
  {
    int mini=min();
    heap[0]=heap[empty_pos-1];  //replacing first/root/minimum element with last element in the heap
    empty_pos--;
    heapify(0,swaps);
    return mini;
  }
  void print_heap()
  {
    cout<<endl;
    for(long long i=0;i<empty_pos;i++)
      cout<<heap[i]<<" ";
    cout<<endl;
  }
};

int main()
{
  long long N=10;

  ofstream fout;
  fout.open("info.txt");

  for(;N<1000001;N*=10)
  {
    Heap *x = new Heap;
    auto start = high_resolution_clock::now();
    long long swap=0;
    //inserting N elements
    for(long long i=0;i<N;i++)
      x->insert(rand()%(2*N),swap);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double tim = double(duration.count());
    fout<<N<<","<<tim<<","<<swap<<",";

    //delete-min N elements
    start = high_resolution_clock::now();
    swap=0;
    for(long long i=0;i<N;i++)
      x->del_min(swap);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    tim = double(duration.count());
    fout<<N<<","<<tim<<","<<swap<<",";

    swap=0;
    //inserting N elements
    for(long long i=0;i<N;i++)
      x->insert(rand()%(2*N),swap);

    //inserting or delete-min N/5 elements at random
    start = high_resolution_clock::now();
    swap=0;
    for(long long i=0;i<(N/5);i++)
    {
      if(rand()%2)
        x->insert(rand()%(2*N),swap);
      else
        x->del_min(swap);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    tim = double(duration.count());
    fout<<(N/5)<<","<<tim<<","<<swap<<endl;

    delete x;
  }
  return 0;
}