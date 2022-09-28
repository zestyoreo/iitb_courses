/*
  maze.cpp
  Solving a Maze using Graphs
  Data Structures and Algorithms Lab - CS293
  Author: P Balasubramanian
  Rollno: 200050103
*/  
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define MAX_RC 100
struct cell
{
    int row,col;
    cell()
    {}
    cell(int r, int c)
    {
        row = r;
        col = c;
    }
};

class Graph
{
    cell adj_list[MAX_RC][MAX_RC][4];
    int num_adj[MAX_RC][MAX_RC];
    int N,M;    //number of rows and columns of CELLS

    public:
        Graph(int n,int m)
        {
            N = --n;
            M = --m;
            
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    num_adj[i][j] = 0;
                    adj_list[i][j][0] = cell(-1,-1);
                }   
            }  
        }
        void create_graph()
        {
            // horizontal walls input
            bool horizontal[MAX_RC][MAX_RC];
            cout<<"_________HORIZONTAL WALLS MATRIX_________"<<endl;
            for (int i = 0; i < N+1; i++)
            {
                for (int j = 0; j < M; j++)
                {  
                    int w;
                    cin>>w;
                    if(w==0)
                        horizontal[i][j] = false;
                    else
                        horizontal[i][j] = true;
                }
            }
            // vertical walls input
            bool vertical[MAX_RC][MAX_RC];
            cout<<"__________VERTICAL WALLS MATRIX__________"<<endl;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M+1; j++)
                {  
                    int w;
                    cin>>w;
                    if(w==0)
                        vertical[i][j] = false;
                    else
                        vertical[i][j] = true;
                }
            }

            // creating the graph
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    int k;
                    //upper wall
                    if(!horizontal[i][j] && (i-1>-1) && num_adj[i][j]<4)
                    {
                        k = num_adj[i][j];
                        adj_list[i][j][k] = cell(i-1,j);
                        num_adj[i][j]++;
                    }
                    
                    //lower wall
                    if(!horizontal[i+1][j] && (i+1<N) && num_adj[i][j]<4)
                    {
                        k = num_adj[i][j];
                        adj_list[i][j][k] = cell(i+1,j);
                        num_adj[i][j]++;
                    }

                    //left wall
                    if(!vertical[i][j] && (j-1>-1) && num_adj[i][j]<4)
                    {
                        k = num_adj[i][j];
                        adj_list[i][j][k] = cell(i,j-1);
                        num_adj[i][j]++;
                    }

                    //right wall
                    if(!vertical[i][j+1] && (j+1<M) && num_adj[i][j]<4)
                    {
                        k = num_adj[i][j];
                        adj_list[i][j][k] = cell(i,j+1);
                        num_adj[i][j]++;
                    }
                }
            }
        }
        void shortest_path()
        {
            cell c(N-1,M-1);
            char color[MAX_RC][MAX_RC];
            int dist[MAX_RC][MAX_RC];
            pair<int,int> parent[MAX_RC][MAX_RC];
            queue<cell> Q;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    if(i!=c.row || j!=c.col)
                    {
                        color[i][j] = 'w';
                        dist[i][j] = 10001; //infinity
                    }
                    else
                    {
                        color[i][j] = 'g';
                        dist[i][j] = 0;
                        parent[i][j].first = -1;
                        parent[i][j].second = -1;
                        Q.push(c);
                    }
                }  
            }
            while(Q.size()!=0)
            {
                cell u = Q.front();
                if(num_adj[u.row][u.col]!=0)
                {
                    for (int i = 0; i < num_adj[u.row][u.col] ; i++)
                    {
                        cell v = adj_list[u.row][u.col][i];
                        if(color[v.row][v.col]=='w')
                        {
                            color[v.row][v.col] = 'g';
                            dist[v.row][v.col] = dist[u.row][u.col] +1;
                            parent[v.row][v.col].first = u.row;
                            parent[v.row][v.col].second = u.col;
                            Q.push(v);
                        }
                    }
                }
                Q.pop();
                color[u.row][u.col]='b';  
            }

            //print_distance;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    cout<<dist[i][j]<<" ";
                }
                cout<<endl;
            }
            //print_color;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    cout<<color[i][j]<<" ";
                }
                cout<<endl;
            }
            //print_num_adj;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    cout<<num_adj[i][j]<<" ";
                }
                cout<<endl;
            }
            //print_path;
            cell v(0,0);
            while(v.row!=-1)
            {
                cout<<"("<<v.row<<","<<v.col<<"), ";
                int x = v.row;
                v.row = parent[v.row][v.col].first;
                v.col = parent[x][v.col].second;
            }
            cout<<endl;
        }
};

int main()
{
    int n,m;
    cout<<"Enter number of rows and columns of maze-grid: ";
    cin>>n>>m;

    Graph x(n,m);

    x.create_graph();
    x.shortest_path();

    return 0;
}