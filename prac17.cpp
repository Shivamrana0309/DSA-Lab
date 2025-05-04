#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <climits>
#include <functional>

using namespace std;

void dijkstra(int src, int dest, const vector<vector<pair<int,int>>>& graph) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX), parent(n, -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[src] = 0;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }

    if (dest < 0 || dest >= n || dist[dest] == INT_MAX) {
        cout << "No path from " << src << " to " << dest << ".\n";
        return;
    }

    cout << "Shortest path distance: " << dist[dest] << "\n";
    cout << "Path: ";
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    for (int v : path) cout << v << " ";
    cout << "\n";
}

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<pair<int,int>>> graph(n);
    cout << "Enter directed edges (u v w):\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }

    while (true) {
        cout << "\nMenu:\n"
                "1. Find shortest path\n"
                "2. Exit\n"
                "Choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int src, dest;
            cout << "Enter source and destination nodes: ";
            cin >> src >> dest;
            if (src < 0 || src >= n) {
                cout << "Invalid source node.\n";
                continue;
            }
            dijkstra(src, dest, graph);
        }
        else if (choice == 2) {
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
