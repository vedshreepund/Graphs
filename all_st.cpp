#include<iostream>
#include<vector>
using namespace std;

class Graph{

  int V,E;
  vector<pair<int,int>> edges;

public:

  Graph(int v,int e):V(v),E(e){}

  void input(){
    for(int i=0;i<E;i++){
      int u,v;
      cin>>u>>v;
      edges.push_back({u,v});
    }
  }

  vector<int> parent;

  int find(int x){
    if(parent[x]==x) return x;
    return parent[x]=find(parent[x]);
  }

  bool unionSet(int a,int b){
    a=find(a);
    b=find(b);

    if(a==b) return false;

    parent[b]=a;
    return true;
  }

  void printTree(vector<pair<int,int>>&res){
    for(auto e:res){
      cout<<"("<<e.first<<","<<e.second<<") ";
    }
    cout<<endl;
  }

  void solve(int idx, vector<pair<int,int>>&res){

    if(res.size()==V-1){

      parent.resize(V);
      for(int i=0;i<V;i++) parent[i]=i;

      for(auto e:res){
        if(!unionSet(e.first,e.second)) return;
      }

      int root=find(0);
      for(int i=1;i<V;i++){
        if(find(i)!=root) return;
      }

      printTree(res);
      return;
    }

    if(idx==E) return;

    res.push_back(edges[idx]);
    solve(idx+1,res);

    res.pop_back();
    solve(idx+1,res);
  }

  void allSpanningTrees(){
    vector<pair<int,int>> res;
    solve(0,res);
  }
};

int main(){

  int v,e;
  cin>>v>>e;

  Graph g(v,e);
  g.input();

  g.allSpanningTrees();

  return 0;
}
