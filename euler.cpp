#include<iostream>
#include<vector>
using namespace std;

class Graph {

    int V, E;
    vector<vector<int>> adj;
    vector<vector<int>> used;
    vector<int> path;

public:

    Graph(int v, int e) : V(v), E(e) {
        adj.resize(V);
        used.resize(V, vector<int>(V, 0));
    }

    void input() {
        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    int getOddCount() {
        int cnt = 0;
        for (int i = 0; i < V; i++) {
            if (adj[i].size() % 2 != 0) cnt++;
        }
        return cnt;
    }

    bool dfs(int v, int edgesUsed) {

        path.push_back(v);

        if (edgesUsed == E) return true;

        for (auto u : adj[v]) {

            if (!used[v][u]) {

                used[v][u] = used[u][v] = 1;

                if (dfs(u, edgesUsed + 1)) return true;

                used[v][u] = used[u][v] = 0;
            }
        }

        path.pop_back();
        return false;
    }

    void solve() {

        int odd = getOddCount();

        if (odd != 0 && odd != 2) {
            cout << "No Euler Path or Circuit\n";
            return;
        }

        int start = 0;

        if (odd == 2) {
            for (int i = 0; i < V; i++) {
                if (adj[i].size() % 2 != 0) {
                    start = i;
                    break;
                }
            }
            cout << "Euler Path exists\n";
        } else {
            cout << "Euler Circuit exists\n";
        }

        if (dfs(start, 0)) {
            for (auto x : path) cout << x << " ";
            cout << endl;
        } else {
            cout << "No valid traversal found\n";
        }
    }
};

int main() {

    int v, e;
    cin >> v >> e;

    Graph g(v, e);
    g.input();

    g.solve();

    return 0;
}
