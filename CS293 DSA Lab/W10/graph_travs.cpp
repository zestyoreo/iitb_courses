/*
  graph_travs.cpp
  BFS and DFS Graph Traversals & Checking if Graph is Bipartite using DFS
  Data Structures and Algorithms Lab - CS293
  Author: P Balasubramanian
  Rollno: 200050103
*/  

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define MAX_RC 10

class Graph
{
    int adj_list[MAX_RC][MAX_RC];
    int num_adj[MAX_RC];
    int N;                          //number of vertices  6<=N<=10

    public:
        Graph(int n)
        {
            //generate random graph
            N = n;

            for (int i = 0; i < N; i++)
            {
                num_adj[i]=0;
            }
            
            //generate 2N edges
            for (int i = 0; i < 2*N; i++)
            {
                int vert_1 = rand()%N;
                int vert_2 = rand()%N;
                while(vert_1==vert_2)
                    vert_2 = rand()%N;
                
                if(num_adj[vert_1]==0 || num_adj[vert_2]==0)
                    add_edge(vert_1,vert_2);
                else
                {
                    bool exist = false;
                    for (int j = 0; j < num_adj[vert_1]; j++)
                    {
                        if (adj_list[vert_1][j]==vert_2)
                        {
                            exist=true;
                        }
                    }
                    if(!exist)
                        add_edge(vert_1,vert_2);
                    else
                        i--;    
                }
            }
            cout<<endl; 
        }

        void add_edge(int vert_1,int vert_2)
        {
            adj_list[vert_1][num_adj[vert_1]] = vert_2;
            num_adj[vert_1]++;
            adj_list[vert_2][num_adj[vert_2]] = vert_1;
            num_adj[vert_2]++;
            cout<<"("<<vert_1<<","<<vert_2<<"), ";
        }

        void BFS_DFS(int source,bool BFS)
        {
            bool visited[MAX_RC];
            int dist[MAX_RC];
            queue<int> Q;
            stack<int> S;
            for (int i = 0; i < N; i++)
            {
                 visited[i]=false;
                 dist[i]=10000; //infinity
            }
            visited[source]=true;
            dist[source]=0;
            
            if(BFS)
            {
                Q.push(source);
                cout<<"BFS Traversal"<<endl;
            }
            else
            {
                S.push(source);
                cout<<"DFS Traversal"<<endl;
            }

            cout<<source<<" ";

            while((BFS && Q.size()!=0)||(!BFS && S.size()!=0))
            {
                int u;
                if(BFS)
                    u = Q.front();
                else
                {
                    u = S.top();
                    S.pop();
                }

                if(num_adj[u]!=0)
                {
                    for (int i = 0; i < num_adj[u] ; i++)
                    {
                        int v = adj_list[u][i];
                        if(!visited[v])
                        {
                            cout<<v<<" ";
                            visited[v]=true;
                            dist[v] = dist[u]+1;
                            if(BFS)
                                Q.push(v);
                            else
                                S.push(v);
                        }
                    }
                }
                if(BFS)
                    Q.pop();
            }
        cout<<endl;
        }

        bool DFS_Bipartite(int s)
        {
            stack<int> S;
            vector<int> color(N);
            vector<int> visited(N);
            for (int i = 0; i < N; i++)
            {
                visited[i]=false;
            }
            visited[s]=true;
            color[s]=0;
            S.push(s);

            while(S.size()!=0)
            {
                int s = S.top();
                S.pop();
                if(num_adj[s]!=0)
                {
                    for(int i = 0; i < num_adj[s] ; i++)
                    {
                        int u = adj_list[s][i];
                        if (visited[u] == false) 
                        {
                            visited[u] = true;
                            S.push(u);

                            if(color[s]==1)
                                color[u] = 0;
                            else
                                color[u] = 1;
                        }
                        else if(color[u] == color[s])
                        {
                            cout<<"Graph is not Bipartite."<<endl<<"The odd cycle detected is"<<endl;
                            while(S.size()!=0)
                            {
                                cout<<S.top()<<", ";
                                S.pop();
                            }
                            return false;
                        }
                    }
                }
            }
            cout<<"Graph is Bipartite."<<endl;
            return true;
        }
};
int main()
{
    int n,source;
    cout<<"Enter number of vertices (N) in graph: ";
    cin>>n;
    Graph x(n);
    cout<<"Enter source vertex from where BFS and DFS take place."<<endl;
    cin>>source;
    x.BFS_DFS(source,true);
    x.BFS_DFS(source,false);
    x.DFS_Bipartite(source);
    return 0;
}