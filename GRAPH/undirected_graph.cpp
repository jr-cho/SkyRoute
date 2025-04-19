#include "undirected_graph.h"
#include <fstream>
#include <sstream>
#include <iostream>

int UndirectedGraph::findNodeIndex(const char* code) {
    for (int i = 0; i < nodes.size(); ++i) {
        if (strcmp(nodes[i], code) == 0) return i;
    }
    return -1;
}

bool UndirectedGraph::edgeExists(const char* a, const char* b, int& costAB, int& costBA) {
    costAB = -1; costBA = -1;
    for (auto& edge : edges) {
        if (strcmp(edge.from, a) == 0 && strcmp(edge.to, b) == 0)
            costAB = edge.cost;
        else if (strcmp(edge.from, b) == 0 && strcmp(edge.to, a) == 0)
            costBA = edge.cost;
    }
    return costAB != -1 || costBA != -1;
}

void UndirectedGraph::loadFromDirected(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string origin, destination, oc, dc, dist, cost;

        std::getline(ss, origin, ',');
        std::getline(ss, destination, ',');
        std::getline(ss, oc, ',');
        std::getline(ss, dc, ',');
        std::getline(ss, dist, ',');
        std::getline(ss, cost);

        char from[4], to[4];
        strncpy(from, origin.c_str(), 3); from[3] = '\0';
        strncpy(to, destination.c_str(), 3); to[3] = '\0';
        int c = std::stoi(cost);

        int costAB, costBA;
        if (!edgeExists(from, to, costAB, costBA)) {
            UGEdge edge = {"", "", c};
            strncpy(edge.from, from, 4);
            strncpy(edge.to, to, 4);
            edges.push_back(edge);

            if (findNodeIndex(from) == -1) {
                char newNode[4]; strncpy(newNode, from, 4);
                nodes.push_back({});
                strncpy(nodes.back(), newNode, 4);
            }
            if (findNodeIndex(to) == -1) {
                char newNode[4]; strncpy(newNode, to, 4);
                nodes.push_back({});
                strncpy(nodes.back(), newNode, 4);
            }
        } else if (costAB != -1 && costBA != -1) {
            int minCost = std::min(costAB, costBA);
            bool found = false;
            for (auto& edge : edges) {
                if ((strcmp(edge.from, from) == 0 && strcmp(edge.to, to) == 0) ||
                    (strcmp(edge.from, to) == 0 && strcmp(edge.to, from) == 0)) {
                    edge.cost = minCost;
                    found = true;
                    break;
                }
            }
            if (!found) {
                UGEdge edge = {"", "", minCost};
                strncpy(edge.from, from, 4);
                strncpy(edge.to, to, 4);
                edges.push_back(edge);
            }
        }
    }
    file.close();
}

void UndirectedGraph::buildPrimMST() {
    PrimGraph pg;
    for (auto& node : nodes) pg.addNode(node);
    for (auto& edge : edges) pg.addEdge(edge.from, edge.to, edge.cost);
    pg.buildMST();
}

void UndirectedGraph::buildKruskalMST() {
    KruskalGraph kg(nodes.size());
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = i + 1; j < nodes.size(); j++) {
            for (auto& edge : edges) {
                if ((strcmp(nodes[i], edge.from) == 0 && strcmp(nodes[j], edge.to) == 0) ||
                    (strcmp(nodes[j], edge.from) == 0 && strcmp(nodes[i], edge.to) == 0)) {
                    kg.addEdge(i, j, edge.cost);
                }
            }
        }
    }
    kg.buildMST();
}

