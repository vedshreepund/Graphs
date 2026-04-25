#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

bool cmp(Edge a, Edge b) {
    return a.w < b.w;
}

vector<int> parent, rankv;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    int px = find(x);
    int py = find(y);

    if (px == py) return;

    if (rankv[px] < rankv[py])
        parent[px] = py;
    else if (rankv[px] > rankv[py])
        parent[py] = px;
    else {
        parent[py] = px;
        rankv[px]++;
    }
}

int kruskal(int V, vector<Edge> &edges) {
    sort(edges.begin(), edges.end(), cmp);

    parent.resize(V);
    rankv.resize(V, 0);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int total = 0;

    for (auto e : edges) {
        if (find(e.u) != find(e.v)) {
            total += e.w;
            unite(e.u, e.v);
        }
    }
    return total;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<Edge> edges(E);

    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].u--;
        edges[i].v--;
    }

    cout << kruskal(V, edges) << endl;
}
