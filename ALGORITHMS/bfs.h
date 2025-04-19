#ifndef BFS_H
#define BFS_H

#include <vector>
#include "queue.h"

class BFSGraph {
private:
    std::vector<char[4]> nodeNames;        // Stores airport codes
    std::vector<std::vector<int>> adj;     // Adjacency list
    int findIndex(const char* name);       // Find index of a node by code
public:
    void addNode(const char* name);
    void addEdge(const char* from, const char* to);
    void bfs(const char* start);           // Run BFS from a starting node
};

#endif // BFS
