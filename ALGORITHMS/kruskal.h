#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "union_find.h"

struct KruskalEdge {
    int src;
    int dest;
    int cost;
};

class KruskalGraph {
private:
    KruskalEdge* edges;
    int numVertices;
    int numEdges;
    int edgeCapacity;

    void quickSort(int left, int right);
public:
    KruskalGraph(int v);
    ~KruskalGraph();
    void addEdge(int u, int v, int cost);
    void buildMST(); // Outputs a forest if disconnected
};

#endif // KRUSKAL_H
