#include "dfs.h"
#include <iostream>
#include <cstring>

int DFSGraph::findIndex(const char* name) {
    for (int i = 0; i < nodeNames.size(); i++) {
        if (strcmp(nodeNames[i], name) == 0) return i;
    }
    return -1;
}

void DFSGraph::addNode(const char* name) {
    if (findIndex(name) == -1) {
        char code[4];
        strncpy(code, name, 3);
        code[3] = '\0';
        nodeNames.push_back({});
        strncpy(nodeNames.back(), code, 4);
        adj.push_back(std::vector<int>());
    }
}

void DFSGraph::addEdge(const char* from, const char* to) {
    int u = findIndex(from);
    int v = findIndex(to);
    if (u != -1 && v != -1) {
        adj[u].push_back(v);
    }
}

void DFSGraph::dfs(const char* start) {
    int startIdx = findIndex(start);
    if (startIdx == -1) return;

    std::vector<bool> visited(nodeNames.size(), false);

    Stack<int> stack;
    stack.push(startIdx);
    std::cout << "DFS from " << start << ": ";

    while (!stack.isEmpty()) {
        int u = stack.top();
        stack.pop();

        if (!visited[u]) {
            visited[u] = true;
            std::cout << nodeNames[u] << " ";

            for (int i = adj[u].size() - 1; i >= 0; i--) {
                int v = adj[u][i];
                if (!visited[v]) stack.push(v);
            }
        }
    }
    std::cout << std::endl;
}
