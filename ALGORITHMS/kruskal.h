#ifndef KRUSKAL_H
#define KRUSKAL_H

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
    int* parent;

    int findSet(int i);
    void unionSets(int u, int v);
    void quickSort(int left, int right);
public:
    KruskalGraph(int v);
    ~KruskalGraph();
    void addEdge(int u, int v, int cost);
    void buildMST();
};

#endif // KRUSKAL
