#include<iostream>
#include<vector>
using namespace std;

class Graph{
  int V,E;
  vector<vector<int>> adj;
  vector<vector<int>> tree;
  vector<pair<int,int>> extraEdges;
  vector<int> parent, vis;

public:
  Graph(int v,int e):V(v),E(e){
    adj.resize(V);
    tree.resize(V);
    parent.resize(V,-1);
    vis.resize(V,0);
  }

  void input(){
    for(int i=0;i<E;i++){
      int u,v; cin>>u>>v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }

  void dfs(int v){
    vis[v]=1;
    for(int u:adj[v]){
      if(!vis[u]){
        parent[u]=v;
        tree[v].push_back(u);
        tree[u].push_back(v);
        dfs(u);
      } else if(u!=parent[v]){
        if(v<u) extraEdges.push_back({v,u});
      }
    }
  }

  void printPath(int u,int v){
    vector<int> pathU, pathV;

    while(u!=-1){
      pathU.push_back(u);
      u=parent[u];
    }
    while(v!=-1){
      pathV.push_back(v);
      v=parent[v];
    }

    int i=pathU.size()-1, j=pathV.size()-1;
    while(i>=0 && j>=0 && pathU[i]==pathV[j]){
      i--; j--;
    }

    for(int k=0;k<=i+1;k++) cout<<pathU[k]<<" ";
    for(int k=j;k>=0;k--) cout<<pathV[k]<<" ";
  }

  void fundamentalCircuits(){
    dfs(0);

    for(auto e:extraEdges){
      int u=e.first, v=e.second;
      cout<<"Cycle: ";
      printPath(u,v);
      cout<<u<<endl;
    }
  }
};

int main(){
  int v,e; cin>>v>>e;
  Graph g(v,e);
  g.input();

  g.fundamentalCircuits();
}
