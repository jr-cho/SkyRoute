#ifndef DFS_H
#define DFS_H

#include "vector.h"
#include "stack.h"
#include <string>

class DFSGraph {
private:
    Vector<std::string> nodeNames;
    Vector<Vector<int>> adj;
    int findIndex(const std::string& name);
public:
    void addNode(const std::string& name);
    void addEdge(const std::string& from, const std::string& to);
    void dfs(const std::string& start);
};

#endif // DFS
