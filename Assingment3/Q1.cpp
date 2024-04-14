#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Structure to represent a weighted edge in the graph
struct Edge {
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

// Comparator for sorting edges by weight
bool cmp(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Disjoint Set Union (DSU) data structure for Kruskal's algorithm
struct DSU {
    vector<int> parent, rank;
    DSU(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int xroot = find(x), yroot = find(y);
        if (xroot == yroot)
            return;
        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
};

// Function to find the Minimum Spanning Tree using Kruskal's algorithm
vector<Edge> kruskalMST(vector<Edge>& edges, int n) {
    vector<Edge> mst;
    sort(edges.begin(), edges.end(), cmp);
    DSU dsu(n);
    for (const Edge& e : edges) {
        int x = dsu.find(e.src), y = dsu.find(e.dest);
        if (x != y) {
            mst.push_back(e);
            dsu.unite(x, y);
        }
    }
    return mst;
}

// Function to find the Minimum Spanning Tree using Prim's algorithm
vector<Edge> primMST(const vector<vector<pair<int, int>>>& graph, int n) {
    vector<Edge> mst;
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> inMST(n, false);

    // Start with vertex 0
    key[0] = 0;
    parent[0] = -1;

    // Priority queue to store vertices based on their key values
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;

        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }

    // Construct the MST from the parent array
    for (int i = 1; i < n; i++) {
        mst.push_back(Edge(parent[i], i, key[i]));
    }

    return mst;
}

int main() {
// given graph
/*       2
    0 ---- 1
    | \    | \
    6  \   |  5
    |    \ |   \
    3      8     7
    |      |     |
    4 ---- 2 ---- 4
            3
*/
    int n = 5; // Number of vertices
    vector<Edge> edges;
    edges.push_back(Edge(0, 1, 2));
    edges.push_back(Edge(0, 3, 6));
    edges.push_back(Edge(1, 2, 3));
    edges.push_back(Edge(1, 3, 8));
    edges.push_back(Edge(1, 4, 5));
    edges.push_back(Edge(2, 4, 7));
    edges.push_back(Edge(3, 4, 9));

    // Kruskal's algorithm
    auto kruskal_start = high_resolution_clock::now();
    vector<Edge> mst_kruskal = kruskalMST(edges, n);
    auto kruskal_end = high_resolution_clock::now();
    auto kruskal_duration = duration_cast<microseconds>(kruskal_end - kruskal_start);

    cout << "Kruskal's MST (Time Complexity: O(E log E) or O(E log V)):" << endl;
    for (const Edge& e : mst_kruskal)
        cout << e.src << " -- " << e.dest << " : " << e.weight << endl;
    cout << "Execution time: " << kruskal_duration.count() << " microseconds" << endl;
    cout << endl;

    // Prim's algorithm
    vector<vector<pair<int, int>>> graph(n);
    for (const Edge& e : edges) {
        graph[e.src].emplace_back(e.dest, e.weight);
        graph[e.dest].emplace_back(e.src, e.weight);
    }

    auto prim_start = high_resolution_clock::now();
    vector<Edge> mst_prim = primMST(graph, n);
    auto prim_end = high_resolution_clock::now();
    auto prim_duration = duration_cast<microseconds>(prim_end - prim_start);

    cout << "Prim's MST (Time Complexity: O(E log V)):" << endl;
    for (const Edge& e : mst_prim)
        cout << e.src << " -- " << e.dest << " : " << e.weight << endl;
    cout << "Execution time: " << prim_duration.count() << " microseconds" << endl;

    return 0;
}
