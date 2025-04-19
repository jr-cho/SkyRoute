#include "prim.h"
#include <iostream>
#include <cstring>

const int INF = 1000000000; 

int PrimGraph::findIndex(const char* name) {
    for (int i = 0; i < nodes.size(); i++) {
        if (strcmp(nodes[i].name, name) == 0) return i;
    }
    return -1;
}

void PrimGraph::addNode(const char* name) {
    if (findIndex(name) == -1) {
        PrimNode node;
        strncpy(node.name, name, 3);
        node.name[3] = '\0';
        node.head = nullptr;
        nodes.push_back(node);
    }
}

void PrimGraph::addEdge(const char* from, const char* to, int cost) {
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
    std::vector<bool> visited(n, false);
    std::vector<int> key(n, INF);
    std::vector<int> parent(n, -1);

    key[0] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (u == -1 || key[i] < key[u])) u = i;
        }

        if (key[u] == INF) {
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

