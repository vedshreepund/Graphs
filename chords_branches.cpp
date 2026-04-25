#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Graph{

  int V,E;
  vector<vector<pair<int,int>>> adj;
  vector<vector<int>> tree;
  vector<pair<int,int>> edges;
  vector<pair<int,int>> mstEdges;
  vector<pair<int,int>> chords;

  vector<int> parent, rankv;

public:

  Graph(int v,int e):V(v),E(e){
    adj.resize(V);
    tree.resize(V);
    parent.resize(V);
    rankv.resize(V,0);

    for(int i=0;i<V;i++) parent[i]=i;
  }

  void input(){
    for(int i=0;i<E;i++){
      int u,v,w;
      cin>>u>>v>>w;
      edges.push_back({u,v});
      adj[u].push_back({v,w});
      adj[v].push_back({u,w});
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

  void buildMST(){

    vector<tuple<int,int,int>> ed;

    for(int u=0;u<V;u++){
      for(auto [v,w]:adj[u]){
        if(u<v) ed.push_back({w,u,v});
      }
    }

    sort(ed.begin(),ed.end());

    for(auto [w,u,v]:ed){
      if(find(u)!=find(v)){
        unite(u,v);
        mstEdges.push_back({u,v});
        tree[u].push_back(v);
        tree[v].push_back(u);
      }
    }

    for(auto e:edges){
      bool inMST=false;
      for(auto m:mstEdges){
        if((e.first==m.first && e.second==m.second) ||
           (e.first==m.second && e.second==m.first)){
          inMST=true;
        }
      }
      if(!inMST) chords.push_back(e);
    }
  }

  bool dfsPath(int src,int dest,vector<int>&vis,vector<int>&path){
    vis[src]=1;
    path.push_back(src);

    if(src==dest) return true;

    for(auto u:tree[src]){
      if(!vis[u]){
        if(dfsPath(u,dest,vis,path)) return true;
      }
    }

    path.pop_back();
    return false;
  }

  void fundamentalCircuits(){

    for(auto [u,v]:chords){

      vector<int> vis(V,0), path;

      dfsPath(u,v,vis,path);

      cout<<"Cycle: ";
      for(int x:path) cout<<x<<" ";
      cout<<u<<endl;
    }
  }

  void print(){

    cout<<"Branches (MST edges):\n";
    for(auto e:mstEdges)
      cout<<e.first<<" "<<e.second<<endl;

    cout<<"Chords:\n";
    for(auto e:chords)
      cout<<e.first<<" "<<e.second<<endl;

    cout<<"Fundamental Circuits:\n";
    fundamentalCircuits();
  }

};

int main(){

  int v,e;
  cin>>v>>e;

  Graph g(v,e);
  g.input();

  g.buildMST();
  g.print();

  return 0;
}
