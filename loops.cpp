#include<iostream>
#include<vector>

using namespace std;

class Graph{

  int V;
  int E;
  bool D;
  vector<vector<int>> adj;
  vector<vector<int>> cc;
  vector<int>current_cc;

  public:

  vector<int> vis;
  
  Graph ( int v, int e, bool d):
    V(v), E(e), D(d) {
      adj = vector<vector<int>> (V);
      vis = vector<int> (V);
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

    bool dfs ( int vertex, int par ){

      vis[vertex] = 1;
      current_cc.push_back(vertex);
      bool isloop = false;

      for( auto child : adj[vertex] ){
            
        if( vis[child] && child == par ) continue;
        if( vis[child] ) return true;

        isloop |=  dfs(child, vertex );
        
      }
      return isloop;    
    }

    int num_connected_components(){
      
      int count = 0;
      for ( int i = 0 ; i < V ; i++ ){
        if(vis[i]) continue;
        current_cc.clear();
        dfs(i, -1 );
        cc.push_back(current_cc);
        count++;
      }
      return count;
    }

    void components(){
      for( auto i : cc ){
        for( auto j : i ){
          cout<<j<<" ";
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

 // cout<<"Number of components in this graph is => "<<g.num_connected_components()<<endl;

  //g.components();

  bool is_loop = false;

  for ( int i = 0 ; i < v; i++ ){
    if( g.vis[i] ) continue;

    if( g.dfs(i, -1)){
      is_loop = true;
      break;
    }
  }

  cout<<is_loop<<endl;

  return 0;
}
