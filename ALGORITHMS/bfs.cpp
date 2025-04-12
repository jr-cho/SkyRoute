#include "bfs.h"
#include <iostream>

int BFSGraph::findIndex(const std::string& name) {
    for (int i = 0; i < nodeNames.size(); i++) {
        if (nodeNames[i] == name) return i;
    }
    return -1;
}

void BFSGraph::addNode(const std::string& name) {
    if (findIndex(name) == -1) {
        nodeNames.push_back(name);
        adj.push_back(Vector<int>());
    }
}

void BFSGraph::addEdge(const std::string& from, const std::string& to) {
    int u = findIndex(from);
    int v = findIndex(to);
    if (u != -1 && v != -1) {
        adj[u].push_back(v);
    }
}

void BFSGraph::bfs(const std::string& start) {
    int startIdx = findIndex(start);
    if (startIdx == -1) return;

    Vector<bool> visited;
    for (int i = 0; i < nodeNames.size(); ++i) visited.push_back(false);

    Queue<int> queue;
    visited[startIdx] = true;
    queue.enqueue(startIdx);

    std::cout << "BFS from " << start << ": ";
    while (!queue.isEmpty()) {
        int u = queue.dequeue();
        std::cout << nodeNames[u] << " ";

        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = true;
                queue.enqueue(v);
            }
        }
    }
    std::cout << std::endl;
}
