#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

int V;
int finalCost = INF;

int firstMin(vector<vector<int>> &graph, int i) {
    int minVal = INF;
    for (int k = 0; k < V; k++) {
        if (i != k)
            minVal = min(minVal, graph[i][k]);
    }
    return minVal;
}

int secondMin(vector<vector<int>> &graph, int i) {
    int first = INF, second = INF;
    for (int j = 0; j < V; j++) {
        if (i == j) continue;

        if (graph[i][j] <= first) {
            second = first;
            first = graph[i][j];
        }
        else if (graph[i][j] < second && graph[i][j] != first) {
            second = graph[i][j];
        }
    }
    return second;
}

void tspRec(vector<vector<int>> &graph,
            vector<bool> &visited,
            int curr_bound,
            int curr_weight,
            int level,
            int curr_path[]) {

    if (level == V) {
        if (graph[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight +
                           graph[curr_path[level - 1]][curr_path[0]];

            finalCost = min(finalCost, curr_res);
        }
        return;
    }

    for (int i = 0; i < V; i++) {

        if (graph[curr_path[level - 1]][i] != 0 && !visited[i]) {

            int temp = curr_bound;
            curr_weight += graph[curr_path[level - 1]][i];

            if (level == 1)
                curr_bound -= (firstMin(graph, curr_path[level - 1]) +
                               firstMin(graph, i)) / 2;
            else
                curr_bound -= (secondMin(graph, curr_path[level - 1]) +
                               firstMin(graph, i)) / 2;

            if (curr_bound + curr_weight < finalCost) {

                curr_path[level] = i;
                visited[i] = true;

                tspRec(graph, visited, curr_bound,
                       curr_weight, level + 1, curr_path);
            }

            curr_weight -= graph[curr_path[level - 1]][i];
            curr_bound = temp;

            fill(visited.begin(), visited.end(), false);
            for (int j = 0; j < level; j++)
                visited[curr_path[j]] = true;
        }
    }
}

int TSP(vector<vector<int>> &graph) {

    vector<bool> visited(V, false);
    int curr_path[V + 1];

    int curr_bound = 0;

    for (int i = 0; i < V; i++)
        curr_bound += (firstMin(graph, i) +
                       secondMin(graph, i));

    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    visited[0] = true;
    curr_path[0] = 0;

    tspRec(graph, visited, curr_bound, 0, 1, curr_path);

    return finalCost;
}

int main() {

    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cin >> graph[i][j];

    cout << TSP(graph) << endl;
}
