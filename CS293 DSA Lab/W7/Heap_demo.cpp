/*
  Heap_demo.cpp
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
public:
  Heap()
  {empty_pos=0;}
  int min()
  {return heap[0];}
  bool insert(int new_elem)
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
    }
    empty_pos++;
    return true;
  }
  void heapify(int pos)
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
      }
      else
      {
        heap[index] = heap[left_child_of(index)];
        heap[left_child_of(index)] = temp;
        index = left_child_of(index);
      }
    }
  }
  int del_min()
  {
    int mini=min();
    heap[0]=heap[empty_pos-1];  //replacing first/root element with last element in the heap
    empty_pos--;
    heapify(0);
    return mini;
  }
  void print_heap()
  {
    cout<<endl<<"Heap: ";
    for(long long i=0;i<empty_pos;i++)
      cout<<heap[i]<<" ";
    cout<<endl;
  }
};

int main()
{
  Heap x;
  int j;char ch='y';
  while(ch=='y')
  {
      cout<<"1 for insert\n2 for del_min\n3 for min."<<endl;
      cin>>j;
      if(j==1)
      {
          cout<<"Enter integer priority to insert: ";
          cin>>j;
          x.insert(j);
      }
      else if(j==2)
        cout<<"Deleted minimum integer priority: "<<x.del_min()<<endl;
      else if(j==3)
        cout<<"Minimum integer priority in heap: "<<x.min()<<endl;
      x.print_heap();
      cout<<"Do you want to continue? ";
      cin>>ch;
  }
  return 0;
}