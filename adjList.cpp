#include<iostream>
#include<vector>

using namespace std;

class Graph{

  int V;
  int E;
  bool D;
  vector<vector<int>> adj;

  public:

  Graph ( int v, int e, bool d):
    V(v), E(e), D(d) {
      adj = vector<vector<int>> (V);
    }

    //input
    void input (){

      for ( int i = 0 ; i < E ; i++ ){
        int u, v;
        cin>>u>>v;

        adj[u].push_back(v);

        if ( !D ){
          adj[v].push_back(u);
          
        }
        
      }
    }

    //output
    void output (){
      for( int i = 0 ; i < V ; i++ ){
        cout<<i<<"=> ";
        for ( auto x : adj[i] ){
          cout<<x<<" ";
        }
        cout<<endl;
      }
    }

    
};

int main(){

  int v, e;
  cin>>v>>e;

  bool d;
  cin>>d;

  Graph g( v, e, d );

  g.input();

  g.output();

  return 0;
}
