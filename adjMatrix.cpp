#include <iostream>
#include <vector>

using namespace std;

class Graph{

  int V = 8;
  int E;
  bool directed;
  vector<vector<int>> adj;  

  public:

    Graph( int v, int e, bool d ){
      V = v;
      E = e;
      directed = d;
      adj = vector<vector<int>> (v, vector<int>(v,0));
      
    }

    //input
    void input(){
      for ( int i = 0 ; i < E ; i++ ){
        int u,v;
        cin>>u>>v;
        adj[u][v] = 1;
        
        if(!directed){
          adj[v][u] = 1;
        }
      }
    }

    //print
    void print(){
      for ( int i = 0 ; i < V ; i++ ){
        for ( int j = 0 ; j < V ; j++ ){
          cout<<adj[i][j]<<" ";
        }
        cout<<endl;
      }
    }
    
  
};

int main(){

   int v, e;
   cin>>v>>e;

   bool dir;
   cin>>dir;

   Graph g( v, e, dir );

   g.input();

   g.print();
   
  
}
