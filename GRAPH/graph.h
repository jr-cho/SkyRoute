#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "dijkstra.h"
#include "dfs.h"
#include "bfs.h"

struct AirportConnectionCount {
    char code[4];
    int inbound;
    int outbound;
};

class Graph {
private:
    DijkstraGraph dijkstraGraph;
    DFSGraph dfsGraph;
    BFSGraph bfsGraph;
    std::vector<AirportConnectionCount> connectionCounts;

    int findConnectionIndex(const char* code);
    void updateConnectionCount(const char* from, const char* to);

public:
    void loadFromCSV(const char* filename);
    void shortestPath(const char* start, const char* end, bool useCost);
    void dfs(const char* start);
    void bfs(const char* start);
    DijkstraGraph& getDijkstra();
    void displaySortedConnections();
};

#endif // GRAPH_H

