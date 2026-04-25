#include<iostream>
#include<vector>

using namespace std;

class Graph{

  int V;
  int E;
  bool D;
  vector<vector<int>> adj;

public:

  Graph(int v, int e, bool d): V(v), E(e), D(d){
    adj.resize(V);
  }

  void input(){
    for(int i=0;i<E;i++){
      int u,v;
      cin>>u>>v;

      adj[u].push_back(v);
      if(!D) adj[v].push_back(u);
    }
  }

  void output(){
    for(int i=0;i<V;i++){
      cout<<i<<" => ";
      for(auto x:adj[i]) cout<<x<<" ";
      cout<<endl;
    }
  }

  Graph graphUnion(Graph &g2){
    Graph res(V,0,D);

    vector<vector<int>> mat(V, vector<int>(V,0));

    for(int i=0;i<V;i++){
      for(auto j:adj[i]){
        mat[i][j]=1;
        mat[j][i]=1;
      }
    }

    for(int i=0;i<V;i++){
      for(auto j:g2.adj[i]){
        mat[i][j]=1;
        mat[j][i]=1;
      }
    }

    for(int i=0;i<V;i++){
      for(int j=i+1;j<V;j++){
        if(mat[i][j]){
          res.adj[i].push_back(j);
          res.adj[j].push_back(i);
        }
      }
    }

    return res;
  }

  Graph graphIntersection(Graph &g2){
    Graph res(V,0,D);

    vector<vector<int>> mat(V, vector<int>(V,0));

    for(int i=0;i<V;i++){
      for(auto j:g2.adj[i]){
        mat[i][j]=1;
      }
    }

    for(int i=0;i<V;i++){
      for(auto j:adj[i]){
        if(mat[i][j] && i<j){
          res.adj[i].push_back(j);
          res.adj[j].push_back(i);
        }
      }
    }

    return res;
  }

  Graph graphDisjoint(Graph &g2){
    Graph res(V,0,D);

    vector<vector<int>> mat(V, vector<int>(V,0));

    for(int i=0;i<V;i++){
      for(auto j:g2.adj[i]){
        mat[i][j]=1;
      }
    }

    for(int i=0;i<V;i++){
      for(auto j:adj[i]){
        if(!mat[i][j] && i<j){
          res.adj[i].push_back(j);
          res.adj[j].push_back(i);
        }
      }
    }

    return res;
  }

};

int main(){

  int v,e1,e2;
  cin>>v>>e1>>e2;

  bool d;
  cin>>d;

  Graph g1(v,e1,d);
  Graph g2(v,e2,d);

  g1.input();
  g2.input();

  cout<<"Graph 1:\n";
  g1.output();

  cout<<"Graph 2:\n";
  g2.output();

  Graph u = g1.graphUnion(g2);
  Graph in = g1.graphIntersection(g2);
  Graph dff = g1.graphDisjoint(g2);

  cout<<"\nUnion:\n";
  u.output();

  cout<<"\nIntersection:\n";
  in.output();

  cout<<"\nDisjoint (G1 - G2):\n";
  dff.output();

  return 0;
}
