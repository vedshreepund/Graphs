#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Graph{

  int V,E;
  vector<vector<int>> adj;
  vector<vector<int>> distMatrix;
  vector<int> ecc;

public:

  Graph(int v,int e):V(v),E(e){
    adj.resize(V);
  }

  void input(){
    for(int i=0;i<E;i++){
      int u,v;
      cin>>u>>v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }

  vector<int> bfs(int src){
    vector<int> dist(V,-1);
    queue<int> q;

    dist[src]=0;
    q.push(src);

    while(!q.empty()){
      int v=q.front(); q.pop();

      for(auto u:adj[v]){
        if(dist[u]==-1){
          dist[u]=dist[v]+1;
          q.push(u);
        }
      }
    }
    return dist;
  }

  void computeDistanceMatrix(){
    distMatrix.resize(V);

    for(int i=0;i<V;i++){
      distMatrix[i]=bfs(i);
    }
  }

  void computeEccentricity(){
    ecc.resize(V);

    for(int i=0;i<V;i++){
      int mx=0;
      for(int d:distMatrix[i]){
        if(d!=-1) mx=max(mx,d);
      }
      ecc[i]=mx;
    }
  }

  int getRadius(){
    int radius=1e9;
    for(int x:ecc) radius=min(radius,x);
    return radius;
  }

  int getDiameter(){
    int diameter=0;
    for(int x:ecc) diameter=max(diameter,x);
    return diameter;
  }

  vector<int> getCenters(){
    int radius=getRadius();
    vector<int> centers;

    for(int i=0;i<V;i++){
      if(ecc[i]==radius) centers.push_back(i);
    }
    return centers;
  }

  void printDistanceMatrix(){
    cout<<"Distance Matrix:\n";
    for(int i=0;i<V;i++){
      for(int j=0;j<V;j++){
        cout<<distMatrix[i][j]<<" ";
      }
      cout<<endl;
    }
  }

  void printEccentricity(){
    cout<<"Eccentricity:\n";
    for(int i=0;i<V;i++){
      cout<<"Node "<<i<<" -> "<<ecc[i]<<endl;
    }
  }

};

int main(){

  int v,e;
  cin>>v>>e;

  Graph g(v,e);
  g.input();

  g.computeDistanceMatrix();
  g.computeEccentricity();

  g.printDistanceMatrix();
  g.printEccentricity();

  cout<<"Radius: "<<g.getRadius()<<endl;
  cout<<"Diameter: "<<g.getDiameter()<<endl;

  vector<int> centers = g.getCenters();

  cout<<"Center: ";
  for(auto x:centers) cout<<x<<" ";
  cout<<endl;

  return 0;
}
