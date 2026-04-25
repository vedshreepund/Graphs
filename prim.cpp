#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Graph{
  int V, E;
  bool D;
  vector<vector<pair<int,int>>> adj;

public:
  Graph(int v, int e, bool d): V(v), E(e), D(d) {
    adj = vector<vector<pair<int,int>>>(V);
  }

  void input(){
    for(int i=0;i<E;i++){
      int u,v,w;
      cin>>u>>v>>w;
      adj[u].push_back({v,w});
      if(!D) adj[v].push_back({u,w});
    }
  }

  int prim(){
    vector<int> key(V, 1e9);
    vector<int> vis(V,0);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    key[0]=0;
    pq.push({0,0});

    int cost=0;

    while(!pq.empty()){
      auto [w,u]=pq.top(); pq.pop();

      if(vis[u]) continue;

      vis[u]=1;
      cost+=w;

      for(auto [v,wt]:adj[u]){
        if(!vis[v] && wt<key[v]){
          key[v]=wt;
          pq.push({wt,v});
        }
      }
    }
    return cost;
  }
};

int main(){
  int v,e; cin>>v>>e;
  bool d; cin>>d;

  Graph g(v,e,d);
  g.input();

  cout<<g.prim()<<endl;
}
