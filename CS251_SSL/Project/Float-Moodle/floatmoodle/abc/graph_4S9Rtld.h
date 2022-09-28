#include <bits/stdc++.h>
using namespace std;

class container{
    int ty;         // 0 means stack, 1 means queue
    deque<int> cnt;
    public:
        container(int k);
        void insert(int z);
        bool ifEmpty();
        int get();
};

struct Node{
    int color = 0;      // 0 for white, 1 for grey, 2 for black
    int ind;
    int par;
    int d = 0;
    vector<int> edges;
    Node(int in);
};

class Graph{
    int N;
    vector<struct Node> nodes;
    public:
        Graph(int n);
        void Traversal(int c);
        bool ifBipartite();
        void printOddcycle(int u, int v);
        void Reset();
};