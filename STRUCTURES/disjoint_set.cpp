#include "disjoint_set.h"

DisjointSet::DisjointSet(int size) {
    parent.resize(size);
    rank.resize(size, 0);
    for (int i = 0; i < size; ++i) {
        parent[i] = i;
    }
}

int DisjointSet::find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);  // Path compression
    }
    return parent[u];
}

void DisjointSet::unite(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);

    if (rootU != rootV) {
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

