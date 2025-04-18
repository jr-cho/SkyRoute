#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

class DisjointSet {
private:
    int* parent;
    int* rank;
    int size;

public:
    DisjointSet(int n);
    ~DisjointSet();

    int find(int x);
    void unite(int x, int y);
};

#endif // DISJOINT_SET_H