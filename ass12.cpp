#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define edge pair<int, int>

class Graph {
private:
    vector<pair<int, edge>> G; // graph edges (weight, (u, v))
    vector<pair<int, edge>> T; // MST result edges
    int *parent;
    int V; // number of vertices

public:
    Graph(int V);
    void AddWeightedEdge(int u, int v, int w);
    int find_set(int i);
    void union_set(int u, int v);
    void kruskal();
    void print();
};

// Constructor
Graph::Graph(int V) {
    this->V = V;
    parent = new int[V];
    for (int i = 0; i < V; i++)
        parent[i] = i;
}

// Add edge (u, v) with weight w
void Graph::AddWeightedEdge(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));
}

// Find representative (with path compression)
int Graph::find_set(int i) {
    if (i == parent[i])
        return i;
    return parent[i] = find_set(parent[i]);
}

// Union two sets
void Graph::union_set(int u, int v) {
    parent[u] = v;
}

// Kruskal’s MST algorithm
void Graph::kruskal() {
    sort(G.begin(), G.end()); // Sort edges by ascending weight
    int totalCost = 0;

    for (size_t i = 0; i < G.size(); i++) {
        int u = G[i].second.first;
        int v = G[i].second.second;

        int set_u = find_set(u);
        int set_v = find_set(v);

        if (set_u != set_v) {
            T.push_back(G[i]); // include edge in MST
            totalCost += G[i].first;
            union_set(set_u, set_v);
        }
    }

    cout << "\nEdges in the Optimal Pipeline Network:\n";
    cout << "House 1 - House 2 : Cost\n";
    for (size_t i = 0; i < T.size(); i++) {
        cout << " " << T[i].second.first << " - " << T[i].second.second
             << " : " << T[i].first << endl;
    }

    cout << "\nMinimum Total Cost to Lay Pipeline Network: " << totalCost << endl;
}

// ---------------- MAIN ----------------
int main() {
    int V, E;
    cout << "Enter number of houses (nodes): ";
    cin >> V;
    cout << "Enter number of possible connections (edges): ";
    cin >> E;

    Graph g(V);

    cout << "Enter each connection as: house1 house2 cost\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.AddWeightedEdge(u, v, w);
    }

    g.kruskal();
    return 0;
}
