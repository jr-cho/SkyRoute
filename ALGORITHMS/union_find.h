#ifndef UNION_FIND_H
#define UNION_FIND_H

#include "vector.h"

class UnionFind {
private:
    Vector<int> parent;
    Vector<int> rank;

public:
    UnionFind(int size) {
        for (int i = 0; i < size; i++) {
            parent.push_back(i);
            rank.push_back(0);
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

#endif // UNION_FIND

