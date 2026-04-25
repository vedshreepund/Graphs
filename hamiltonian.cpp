#include<iostream>
#include<vector>
using namespace std;

class Graph{
  int V,E;
  vector<vector<int>> adj;

public:
  Graph(int v,int e):V(v),E(e){
    adj=vector<vector<int>>(V);
  }

  void input(){
    for(int i=0;i<E;i++){
      int u,v; cin>>u>>v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }

  bool dfsPath(int v, vector<int>&vis, int cnt){
    if(cnt==V) return true;

    for(int u:adj[v]){
      if(!vis[u]){
        vis[u]=1;
        if(dfsPath(u,vis,cnt+1)) return true;
        vis[u]=0;
      }
    }
    return false;
  }

  bool hamiltonianPath(){
    for(int i=0;i<V;i++){
      vector<int> vis(V,0);
      vis[i]=1;
      if(dfsPath(i,vis,1)) return true;
    }
    return false;
  }

  bool dfsCycle(int v,int start, vector<int>&vis,int cnt){
    if(cnt==V){
      for(int u:adj[v]) if(u==start) return true;
      return false;
    }

    for(int u:adj[v]){
      if(!vis[u]){
        vis[u]=1;
        if(dfsCycle(u,start,vis,cnt+1)) return true;
        vis[u]=0;
      }
    }
    return false;
  }

  bool hamiltonianCycle(){
    for(int i=0;i<V;i++){
      vector<int> vis(V,0);
      vis[i]=1;
      if(dfsCycle(i,i,vis,1)) return true;
    }
    return false;
  }
};

int main(){
  int v,e; cin>>v>>e;
  Graph g(v,e);
  g.input();

  cout<<g.hamiltonianPath()<<endl;
  cout<<g.hamiltonianCycle()<<endl;
}
