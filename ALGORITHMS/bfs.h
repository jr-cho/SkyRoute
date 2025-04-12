#ifndef BFS_H
#define BFS_H

#include "vector.h"
#include "queue.h"
#include <string>

class BFSGraph {
private:
    Vector<std::string> nodeNames;
    Vector<Vector<int>> adj;
    int findIndex(const std::string& name);
public:
    void addNode(const std::string& name);
    void addEdge(const std::string& from, const std::string& to);
    void bfs(const std::string& start);
};

#endif // BFS
