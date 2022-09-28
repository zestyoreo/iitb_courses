#include "graph.h"
#include <bits/stdc++.h>

using namespace std;

container::container(int k){
    ty = k;     
}

void container::insert(int z){
    if(ty==1){
        cnt.push_back(z);
    }else{
        cnt.push_front(z);
    }
}

bool container::ifEmpty(){
    return cnt.size()==0;
}

int container::get(){
    
        int res = cnt.front();
        cnt.pop_front();
        return res;
   
}

Node::Node(int in){
    ind = in;
}

pair<int,int> srt(pair<int,int> z){
    if(z.first>z.second){
        z.first = z.first^z.second;
        z.second = z.second^z.first;
        z.first = z.first^z.second;
    }
    return z;
}

Graph::Graph(int n){
    N = n;
    for(int i = 0;i<=n;i++){
        nodes.push_back(Node(i));
    }
    int m = 0;
    map <pair<int,int>, bool > ifco;
    while(m<2*N){
        int i = (rand()%N)+1;
        int j = (rand()%N) + 1;
        pair<int,int> z = srt(make_pair(i,j));
        if(i!=j && !ifco[z]){
            cout<<z.first<<" "<<z.second<<endl;
            nodes[i].edges.push_back(j);
            nodes[j].edges.push_back(i);
            ifco[z] = true;
            m++;
        }
    }
}
void Graph::Reset(){
    for(int i = 1;i<=N;i++){
        nodes[i].color = 0;
        nodes[i].par = 0;
        nodes[i].d = -1;
    }
}

void Graph::Traversal(int c){
    if(c==1)cout<<"Starting BFS!"<<endl;
    else cout<<"Starting DFS!"<<endl;

    container mycont(c);
    int j = 1;
    for(int i = 1;i<=N;i++){
        if(nodes[i].color==0){
            cout<<"Starting traversing the "<<j<<"th connected component!"<<endl;
            nodes[i].color = 1;
            nodes[i].par = -1;
            mycont.insert(i);
            while(!mycont.ifEmpty()){
                int p = mycont.get();
                cout<<"Processing the node "<<p<<endl;
                for(int k = 0;k<nodes[p].edges.size();k++){
                    if(nodes[nodes[p].edges[k]].color!=2){
                        cout<<"Found the node "<<nodes[p].edges[k]<<", through the traversal from "<<p<<endl;
                        nodes[nodes[p].edges[k]].color = 1;
                        nodes[nodes[p].edges[k]].par = p;
                        mycont.insert(nodes[p].edges[k]);
                    }
                }
                nodes[p].color = 2;
            }
            j++;
        }
    }
    
}

void Graph::printOddcycle(int u, int v){
    cout<<"An odd-membered cycle has been found from the vertex "<<u<<" to "<<v<<endl;
    while(u!=v){
        int d = nodes[u].par;
        cout<<"Go from "<<u<<" to "<<d<<endl;
        u = d;
    }
}

bool Graph::ifBipartite(){
    container mycont(0);
    for(int i = 1;i<=N;i++){
        if(nodes[i].color==0){
            nodes[i].color = 1;
            nodes[i].par = -1;
            nodes[i].d = 0;
            mycont.insert(i);
            while(!mycont.ifEmpty()){
                int p = mycont.get();
                for(int k = 0;k<nodes[p].edges.size();k++){
                    if(nodes[nodes[p].edges[k]].color!=2){
                        nodes[nodes[p].edges[k]].color = 1;
                        nodes[nodes[p].edges[k]].par = p;
                        nodes[nodes[p].edges[k]].d = nodes[p].d+1;
                        mycont.insert(nodes[p].edges[k]);
                    }else{
                        if((nodes[p].d-nodes[nodes[p].edges[k]].d)%2==0){
                            cout<<"The Graph isn't Bipartite!"<<endl;
                            printOddcycle(p,nodes[p].edges[k]);
                            return false;
                        }
                    }
                    
                }
                nodes[p].color = 2;
            }
        }
    }
    cout<<"The Graph is bipartite!"<<endl;
    cout<<endl;
    return true;
}

int main(){
    srand(101);
    Graph G(10);
    G.Traversal(0);
   G.Reset();
   G.Traversal(1);
   G.Reset();
   G.ifBipartite();
}



