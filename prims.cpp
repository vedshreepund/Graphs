#include <bits/stdc++.h>
using namespace std;

int prim(int V, vector<vector<pair<int,int>>> &adj) {
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    key[0] = 0;
    pq.push({0, 0});

    int total = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int wt = pq.top().first;
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        total += wt;

        for (auto it : adj[u]) {
            int v = it.first;
            int w = it.second;

            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                pq.push({w, v});
            }
        }
    }
    return total;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<pair<int,int>>> adj(V);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    cout << prim(V, adj) << endl;
}
