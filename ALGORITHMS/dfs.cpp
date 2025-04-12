#include "dfs.h"
#include <iostream>

int DFSGraph::findIndex(const std::string& name) {
    for (int i = 0; i < nodeNames.size(); i++) {
        if (nodeNames[i] == name) return i;
    }
    return -1;
}

void DFSGraph::addNode(const std::string& name) {
    if (findIndex(name) == -1) {
        nodeNames.push_back(name);
        adj.push_back(Vector<int>());
    }
}

void DFSGraph::addEdge(const std::string& from, const std::string& to) {
    int u = findIndex(from);
    int v = findIndex(to);
    if (u != -1 && v != -1) {
        adj[u].push_back(v);
    }
}

void DFSGraph::dfs(const std::string& start) {
    int startIdx = findIndex(start);
    if (startIdx == -1) return;

    Vector<bool> visited;
    for (int i = 0; i < nodeNames.size(); ++i) visited.push_back(false);

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

