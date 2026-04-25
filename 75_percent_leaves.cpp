#include<iostream>
#include<vector>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int v) : V(v) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void print() {
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (auto x : adj[i]) cout << x << " ";
            cout << endl;
        }
    }
};

void buildV4() {
    cout << "Tree for V = 4:\n";

    Graph g(4);

    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(0,3);

    g.print();
    cout << endl;
}

void buildV8() {
    cout << "Tree for V = 8:\n";

    Graph g(8);

    g.addEdge(0,1); // internal nodes

    g.addEdge(0,2);
    g.addEdge(0,3);
    g.addEdge(0,4);

    g.addEdge(1,5);
    g.addEdge(1,6);
    g.addEdge(1,7);

    g.print();
    cout << endl;
}

int main() {

    buildV4();
    buildV8();

    return 0;
}
