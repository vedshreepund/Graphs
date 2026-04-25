#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Graph{

  int V,E;
  bool D;
  vector<vector<pair<int,int>>> adj;

public:

  Graph(int v,int e,bool d):V(v),E(e),D(d){
    adj.resize(V);
  }

  void input(){
    for(int i=0;i<E;i++){
      int u,v,w;
      cin>>u>>v>>w;

      adj[u].push_back({v,w});
      if(!D) adj[v].push_back({u,w});
    }
  }

  void output(){
    for(int i=0;i<V;i++){
      cout<<i<<" => ";
      for(auto x:adj[i]){
        cout<<"("<<x.first<<","<<x.second<<") ";
      }
      cout<<endl;
    }
  }

  void dijkstra(int src){

    vector<int> dist(V, 1e9);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty()){

      auto [d, u] = pq.top();
      pq.pop();

      if(d > dist[u]) continue;

      for(auto [v, w] : adj[u]){

        if(dist[v] > dist[u] + w){
          dist[v] = dist[u] + w;
          pq.push({dist[v], v});
        }
      }
    }

    cout<<"Shortest distances from "<<src<<":\n";
    for(int i=0;i<V;i++){
      cout<<"Node "<<i<<" -> "<<dist[i]<<endl;
    }
  }

};

int main(){

  int v,e;
  cin>>v>>e;

  bool d;
  cin>>d;

  Graph g(v,e,d);

  g.input();
  g.output();

  int src;
  cin>>src;

  g.dijkstra(src);

  return 0;
}
