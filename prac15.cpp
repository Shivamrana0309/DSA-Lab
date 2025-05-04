#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct Edge {
    int u, v, weight;
};

int numVertices;
vector<Edge> edges;

int findSet(vector<int>& parent, int i) {
    if (parent[i] != i)
        parent[i] = findSet(parent, parent[i]);
    return parent[i];
}

void unionSets(vector<int>& parent, vector<int>& rank, int u, int v) {
    int ru = findSet(parent, u);
    int rv = findSet(parent, v);
    if (ru != rv) {
        if (rank[ru] < rank[rv])
            parent[ru] = rv;
        else if (rank[ru] > rank[rv])
            parent[rv] = ru;
        else {
            parent[rv] = ru;
            rank[ru]++;
        }
    }
}

void inputGraph() {
    edges.clear();
    cout << "Enter number of vertices: ";
    cin >> numVertices;
    int numEdges;
    cout << "Enter number of edges: ";
    cin >> numEdges;
    for (int i = 0; i < numEdges; i++) {
        int u, v, w;
        cout << "Enter edge (u v w,edges start from 0): ";
        cin >> u >> v >> w;
        // u--; v--;
        Edge edge;
        edge.u = u;
        edge.v = v;
        edge.weight = w;
        edges.push_back(edge);
    }
}

void primMST() {
    if (numVertices <= 0) {
        cout << "Graph not initialized or no vertices." << endl;
        return;
    }
    const int INF = numeric_limits<int>::max();
    vector<vector<int>> adj(numVertices, vector<int>(numVertices, INF));
    for (auto edge : edges) {
        adj[edge.u][edge.v] = edge.weight;
        adj[edge.v][edge.u] = edge.weight;
    }
    vector<int> key(numVertices, INF);
    vector<bool> inMST(numVertices, false);
    vector<int> parent(numVertices, -1);
    key[0] = 0;
    for (int count = 0; count < numVertices - 1; count++) {
        int u = -1;
        int minVal = INF;
        for (int i = 0; i < numVertices; i++) {
            if (!inMST[i] && key[i] < minVal) {
                minVal = key[i];
                u = i;
            }
        }
        if (u == -1)
            break;
        inMST[u] = true;
        for (int v = 0; v < numVertices; v++) {
            if (adj[u][v] != INF && !inMST[v] && adj[u][v] < key[v]) {
                key[v] = adj[u][v];
                parent[v] = u;
            }
        }
    }
    int totalCost = 0;
    cout << "Prim's MST:" << endl;
    for (int i = 1; i < numVertices; i++) {
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << " \tWeight: " << adj[i][parent[i]] << endl;
            totalCost += adj[i][parent[i]];
        }
    }
    cout << "Total cost: " << totalCost << endl;
}
int main() {
    int choice;
    while (true) {
        cout << "\n----- MST Menu -----" << endl;
        cout << "1. Input Graph" << endl;
        cout << "2. Prim's Algorithm" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1:
                inputGraph();
                break;
            case 2:
                primMST();
                break;
            case 0:
                exit(0);
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}