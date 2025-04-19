#include "bfs.h"
#include <iostream>
#include <cstring>

int BFSGraph::findIndex(const char* name) {
    for (int i = 0; i < nodeNames.size(); i++) {
        if (strcmp(nodeNames[i], name) == 0) return i;
    }
    return -1;
}

void BFSGraph::addNode(const char* name) {
    if (findIndex(name) == -1) {
        char code[4];
        strncpy(code, name, 3);
        code[3] = '\0';
        nodeNames.push_back({});
        strncpy(nodeNames.back(), code, 4);
        adj.push_back(std::vector<int>());
    }
}

void BFSGraph::addEdge(const char* from, const char* to) {
    int u = findIndex(from);
    int v = findIndex(to);
    if (u != -1 && v != -1) {
        adj[u].push_back(v);
    }
}

void BFSGraph::bfs(const char* start) {
    int startIdx = findIndex(start);
    if (startIdx == -1) return;

    std::vector<bool> visited(nodeNames.size(), false);
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
