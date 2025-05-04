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

void kruskalMST() {
    if (numVertices <= 0) {
        cout << "Graph not initialized or no vertices." << endl;
        return;
    }
    vector<Edge> sortedEdges = edges;
    sort(sortedEdges.begin(), sortedEdges.end(), [](Edge a, Edge b){ return a.weight < b.weight; });
    vector<int> parent(numVertices);
    vector<int> rank(numVertices, 0);
    for (int i = 0; i < numVertices; i++)
        parent[i] = i;
    int edgeCount = 0;
    int totalCost = 0;
    cout << "Kruskal's MST:" << endl;
    for (auto edge : sortedEdges) {
        if (edgeCount == numVertices - 1)
            break;
        int u = edge.u, v = edge.v;
        if (findSet(parent, u) != findSet(parent, v)) {
            cout << u << " - " << v << " \tWeight: " << edge.weight << endl;
            totalCost += edge.weight;
            unionSets(parent, rank, u, v);
            edgeCount++;
        }
    }
    if (edgeCount != numVertices - 1)
        cout << "Graph is not connected, MST cannot be formed." << endl;
    else
        cout << "Total cost: " << totalCost << endl;
}
int main() {
    int choice;
    while (true) {
        cout << "\n----- MST Menu -----" << endl;
        cout << "1. Input Graph" << endl;
        cout << "2. Kruskal's Algorithm" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1:
                inputGraph();
                break;
            case 2:
                kruskalMST();
                break;
            case 0:
                exit(0);
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}