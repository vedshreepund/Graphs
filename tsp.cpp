#include<iostream>
#include<vector>
using namespace std;

#define INF 1e9

class Graph{
  int V;
  vector<vector<int>> g;
  int finalCost=INF;

public:
  Graph(int v):V(v){
    g=vector<vector<int>>(V, vector<int>(V));
  }

  void input(){
    for(int i=0;i<V;i++)
      for(int j=0;j<V;j++)
        cin>>g[i][j];
  }

  int firstMin(int i){
    int m=INF;
    for(int k=0;k<V;k++) if(i!=k) m=min(m,g[i][k]);
    return m;
  }

  int secondMin(int i){
    int a=INF,b=INF;
    for(int j=0;j<V;j++){
      if(i==j) continue;
      if(g[i][j]<=a){ b=a; a=g[i][j]; }
      else if(g[i][j]<b && g[i][j]!=a) b=g[i][j];
    }
    return b;
  }

  void solve(vector<int>&path, vector<int>&vis,
             int bound,int cost,int level){

    if(level==V){
      if(g[path[level-1]][path[0]]!=0)
        finalCost=min(finalCost,
          cost+g[path[level-1]][path[0]]);
      return;
    }

    for(int i=0;i<V;i++){
      if(g[path[level-1]][i] && !vis[i]){
        int temp=bound;
        cost+=g[path[level-1]][i];

        if(level==1)
          bound-= (firstMin(path[level-1])+firstMin(i))/2;
        else
          bound-= (secondMin(path[level-1])+firstMin(i))/2;

        if(bound+cost<finalCost){
          path[level]=i;
          vis[i]=1;
          solve(path,vis,bound,cost,level+1);
        }

        cost-=g[path[level-1]][i];
        bound=temp;

        fill(vis.begin(),vis.end(),0);
        for(int j=0;j<level;j++) vis[path[j]]=1;
      }
    }
  }

  int tsp(){
    vector<int> path(V+1), vis(V,0);

    int bound=0;
    for(int i=0;i<V;i++)
      bound+=firstMin(i)+secondMin(i);

    bound=(bound+1)/2;

    vis[0]=1;
    path[0]=0;

    solve(path,vis,bound,0,1);
    return finalCost;
  }
};

int main(){
  int v; cin>>v;
  Graph g(v);
  g.input();

  cout<<g.tsp()<<endl;
}
