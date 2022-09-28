/*
  Graph.cpp
  Making the base for an undirected graph
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

#define MAX_EDGES 100
struct vertice
{
  int data;
  edge *edg;
  int num_edges;
  vertice(int d)
  {
    data = d;
    edg = new edge[MAX_EDGES];
  }
};

struct edge
{
  int data;
  vertice *vert_1;
  vertice *vert_2;

  edge()
  {
    vert_1 = NULL:
    vert2 = NULL;
  }
};

class Graph
{
  vertice *v;
  egde *e;

  Graph()
  {
    v=NULL;
    e=NULL;
  }

  void insert_vertice();
  void insert_edge();
  void delete_vertice();
  void delete_edge();
  vertice* find_other_vertice();
  vertice* adjacent_vertices();
  vertice* white_adjacent_vertices();

};

int main()
{
  return 0;
}