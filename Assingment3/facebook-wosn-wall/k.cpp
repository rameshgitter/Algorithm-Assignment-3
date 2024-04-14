#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, pair<int, int>>> graph, mst;
int N, E;

int root(int n, int *parent) {
  while (n != parent[n]) {
    parent[n] = parent[parent[n]]; // Path compression for efficiency
    n = parent[n];
  }
  return n;
}

int kruskal() {
  int total = 0;
  int parent[100];

  for (int i = 0; i < N; i++) {
    parent[i] = i;
  }

  sort(graph.begin(), graph.end()); // STL Introsort O(n log n)

  for (int i = 0; i < graph.size(); i++) {

    int ru = root(graph[i].second.first, parent);
    int rv = root(graph[i].second.second, parent);

    if (ru != rv) {
      mst.push_ back(graph[i]);
      parent[ru] = parent[rv];
      total += graph[i].first;
    }
  }

  return total;
}

int prim(int start) {
  int total = 0;

  bool intree[100];
  fill(intree, intree + N, false); // Initialize intree with all false values

  int n = start;
  while (!intree[n]) {
    intree[n] = true;

    int w = INT_MAX; // Use INT_MAX for a safe weight initialization
    int min = -1;
    int min_next;
    for (int i = 0; i < graph.size(); i++) {
      if (graph[i].second.first == n || graph[i].second.second == n) {
        int next;
        if (graph[i].second.first == n)
          next = graph[i].second.second;
        else
          next = graph[i].second.first;

        if (!intree[next] && graph[i].first < w) {
          w = graph[i].first;
          min = i;
          min_next = next;
        }
      }
    }

    if (min != -1) {
      n = min_next;
      mst.push_back(graph[min]);
      total += graph[i].first;
    }
  }

  return total;
}

int main(int argc, const char *argv[]) {
  FILE *fp = fopen("out.facebook-wson-wall.txt", "r");

  fscanf(fp, "%d %d\n", &N, &E);

  for (int i = 0; i < E; i++) {
    char u, v;
    int w;
    fscanf(fp, "%c %c %d\n", &u, &v, &w);
    graph.push_back(make_pair(w, make_pair(u - 'A', v - 'A')));
  }

  int total = kruskal();
  for (int i = 0; i < mst.size(); i++) {
    printf("%c %c %d\n", mst[i].second.first + 'A', mst[i].second.second + 'A', mst[i].first);
  }
  printf("Total with Kruskal: %i\n\n", total);

  mst.clear();

  total = prim(0);

  for( int i=0; i<mst.size(); i++ ) {
    printf("%c %c %d\n", mst[i].second.first+'A', mst[i].second.second+'A', mst[i].first );
  }
    
  printf("Total with Prim: %i\n", total );

  return 0;
}
