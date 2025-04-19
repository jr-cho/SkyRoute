#ifndef DFS_H
#define DFS_H

#include <vector>
#include "stack.h"

class DFSGraph {
private:
    std::vector<char[4]> nodeNames;        // Stores airport codes
    std::vector<std::vector<int>> adj;     // Adjacency list
    int findIndex(const char* name);       // Find index of a node by code
public:
    void addNode(const char* name);
    void addEdge(const char* from, const char* to);
    void dfs(const char* start);           // Run DFS from a starting node
};

#endif // DFS_H
