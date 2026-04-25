#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Graph{
  int V,E;
  vector<vector<int>> edges;
  vector<int> parent, rankv;

public:
  Graph(int v,int e):V(v),E(e){
    parent.resize(V);
    rankv.resize(V,0);
    for(int i=0;i<V;i++) parent[i]=i;
  }

  void input(){
    for(int i=0;i<E;i++){
      int u,v,w;
      cin>>u>>v>>w;
      edges.push_back({w,u,v});
    }
  }

  int find(int x){
    if(parent[x]==x) return x;
    return parent[x]=find(parent[x]);
  }

  void unite(int a,int b){
    a=find(a); b=find(b);
    if(a!=b){
      if(rankv[a]<rankv[b]) swap(a,b);
      parent[b]=a;
      if(rankv[a]==rankv[b]) rankv[a]++;
    }
  }

  int kruskal(){
    sort(edges.begin(),edges.end());

    int cost=0;

    for(auto e:edges){
      int w=e[0], u=e[1], v=e[2];
      if(find(u)!=find(v)){
        cost+=w;
        unite(u,v);
      }
    }
    return cost;
  }
};

int main(){
  int v,e; cin>>v>>e;

  Graph g(v,e);
  g.input();

  cout<<g.kruskal()<<endl;
}
