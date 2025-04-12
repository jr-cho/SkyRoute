#include "prim.h"
#include <iostream>
#include <limits>

int PrimGraph::findIndex(const std::string& name) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].name == name) return i;
    }
    return -1;
}

void PrimGraph::addNode(const std::string& name) {
    if (findIndex(name) == -1) {
        PrimNode node = {name, nullptr};
        nodes.push_back(node);
    }
}

void PrimGraph::addEdge(const std::string& from, const std::string& to, int cost) {
    int u = findIndex(from);
    int v = findIndex(to);
    if (u == -1 || v == -1) return;
    PrimEdge* edge1 = new PrimEdge{v, cost, nodes[u].head};
    PrimEdge* edge2 = new PrimEdge{u, cost, nodes[v].head};
    nodes[u].head = edge1;
    nodes[v].head = edge2;
}

void PrimGraph::buildMST() {
    int n = nodes.size();
    Vector<bool> visited;
    Vector<int> key;
    Vector<int> parent;

    for (int i = 0; i < n; i++) {
        visited.push_back(false);
        key.push_back(std::numeric_limits<int>::max());
        parent.push_back(-1);
    }

    key[0] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (u == -1 || key[i] < key[u])) u = i;
        }

        if (key[u] == std::numeric_limits<int>::max()) {
            std::cout << "Graph is not connected. MST cannot be formed." << std::endl;
            return;
        }

        visited[u] = true;

        for (PrimEdge* e = nodes[u].head; e != nullptr; e = e->next) {
            int v = e->to;
            if (!visited[v] && e->cost < key[v]) {
                key[v] = e->cost;
                parent[v] = u;
            }
        }
    }

    int totalCost = 0;
    std::cout << "MST Edges:\n";
    for (int i = 1; i < n; i++) {
        std::cout << nodes[parent[i]].name << " - " << nodes[i].name << " (" << key[i] << ")\n";
        totalCost += key[i];
    }
    std::cout << "Total Cost of MST: " << totalCost << std::endl;
}

