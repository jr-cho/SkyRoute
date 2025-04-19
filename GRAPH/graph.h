#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "dijkstra.h"
#include "dfs.h"
#include "bfs.h"

class Graph {
private:
    DijkstraGraph dijkstraGraph;
    DFSGraph dfsGraph;
    BFSGraph bfsGraph;
public:
    void loadFromCSV(const char* filename);
    void shortestPath(const char* start, const char* end, bool useCost);
    void dfs(const char* start);
    void bfs(const char* start);
    DijkstraGraph& getDijkstra();
};

#endif // GRAPH_H
