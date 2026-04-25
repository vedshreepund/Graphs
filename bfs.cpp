#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Graph{

  int V,E;
  vector<vector<int>> adj;
  vector<vector<int>> tree;
  vector<int> vis;

public:

  Graph(int v,int e):V(v),E(e){
    adj.resize(V);
    tree.resize(V);
    vis.resize(V,0);
  }

  void input(){
    for(int i=0;i<E;i++){
      int u,v;
      cin>>u>>v;

      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }

  void bfs(int start){
    queue<int> q;
    q.push(start);
    vis[start]=1;

    while(!q.empty()){
      int v=q.front(); q.pop();

      for(auto u:adj[v]){
        if(!vis[u]){
          vis[u]=1;
          tree[v].push_back(u);
          tree[u].push_back(v);
          q.push(u);
        }
      }
    }
  }

  void printTree(){
    for(int i=0;i<V;i++){
      cout<<i<<" => ";
      for(auto x:tree[i]){
        cout<<x<<" ";
      }
      cout<<endl;
    }
  }

  void spanningTree(){
    bfs(0);
    printTree();
  }
};

int main(){

  int v,e;
  cin>>v>>e;

  Graph g(v,e);
  g.input();

  g.spanningTree();

  return 0;
}
