#include<iostream>
#include<vector>
using namespace std;

class Graph{
  int V,E;
  vector<vector<int>> adj;
  vector<vector<int>> tree;
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
      }
    }
  }

  void getComponent(int v, vector<int>&comp, vector<int>&vis2){
    vis2[v]=1;
    comp.push_back(v);

    for(int u:tree[v]){
      if(!vis2[u]) getComponent(u,comp,vis2);
    }
  }

  void cutSets(){
    dfs(0);

    for(int u=0;u<V;u++){
      for(int v:tree[u]){
        if(u<v){

          vector<vector<int>> temp=tree;
          temp[u].erase(remove(temp[u].begin(),temp[u].end(),v),temp[u].end());
          temp[v].erase(remove(temp[v].begin(),temp[v].end(),u),temp[v].end());

          vector<int> vis2(V,0), comp1;
          getComponent(u,comp1,vis2);

          cout<<"Cut-set removing edge "<<u<<"-"<<v<<": ";
          for(int x:comp1) cout<<x<<" ";
          cout<<" | ";

          for(int i=0;i<V;i++){
            if(!vis2[i]) cout<<i<<" ";
          }
          cout<<endl;
        }
      }
    }
  }
};

int main(){
  int v,e; cin>>v>>e;
  Graph g(v,e);
  g.input();

  g.cutSets();
}
