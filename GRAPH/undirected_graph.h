#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include <vector>
#include <cstring>
#include "prim.h"
#include "kruskal.h"

class UndirectedGraph {
private:
    struct UGEdge {
        char from[4];
        char to[4];
        int cost;
    };

    std::vector<UGEdge> edges;
    std::vector<char[4]> nodes;

    int findNodeIndex(const char* code);
    bool edgeExists(const char* a, const char* b, int& costAB, int& costBA);

public:
    void loadFromDirected(const char* filename);
    void buildPrimMST();
    void buildKruskalMST();
};

#endif // UNDIRECTED_GRAPH_H
