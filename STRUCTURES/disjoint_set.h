#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <vector>

class DisjointSet {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DisjointSet(int size);
    int find(int u);
    void unite(int u, int v);
};

#endif // DISJOINT_SET_H

