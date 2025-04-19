#include "dijkstra.h"
#include <iostream>
#include <cstring>

const int INF = 1000000000;

int DijkstraGraph::findIndex(const char* code) {
    for (int i = 0; i < nodes.size(); i++) {
        if (strcmp(nodes[i].code, code) == 0) return i;
    }
    return -1;
}

void DijkstraGraph::addAirport(const char* code) {
    if (findIndex(code) == -1) {
        Node node;
        strncpy(node.code, code, 3);
        node.code[3] = '\0';
        node.head = nullptr;
        nodes.push_back(node);
    }
}

void DijkstraGraph::addFlight(const char* from, const char* to, int distance, int cost) {
    int fromIdx = findIndex(from);
    int toIdx = findIndex(to);
    if (fromIdx == -1 || toIdx == -1) return;

    Edge* newEdge = new Edge{toIdx, distance, cost, nodes[fromIdx].head};
    nodes[fromIdx].head = newEdge;
}

void DijkstraGraph::shortestPath(const char* start, const char* end, bool useCost) {
    int n = nodes.size();
    std::vector<int> dist(n, INF);
    std::vector<int> prev(n, -1);
    std::vector<bool> visited(n, false);

    int startIdx = findIndex(start);
    int endIdx = findIndex(end);
    if (startIdx == -1 || endIdx == -1) {
        std::cout << "Invalid airport code." << std::endl;
        return;
    }

    MinHeap heap(n);
    dist[startIdx] = 0;
    heap.insert(startIdx, 0);

    while (!heap.isEmpty()) {
        HeapNode minNode = heap.extractMin();
        int u = minNode.vertex;
        if (visited[u]) continue;
        visited[u] = true;

        for (Edge* e = nodes[u].head; e != nullptr; e = e->next) {
            int v = e->destination;
            int weight = useCost ? e->cost : e->distance;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                heap.insert(v, dist[v]);
            }
        }
    }

    if (dist[endIdx] == INF) {
        std::cout << "No path from " << start << " to " << end << std::endl;
        return;
    }

    std::vector<int> path;
    for (int at = endIdx; at != -1; at = prev[at]) {
        path.insert(path.begin(), at);
    }

    std::cout << "Shortest path from " << start << " to " << end << ": ";
    for (int i = 0; i < path.size(); i++) {
        std::cout << nodes[path[i]].code;
        if (i < path.size() - 1) std::cout << " -> ";
    }
    std::cout << ". Total " << (useCost ? "cost" : "distance") << ": " << dist[endIdx] << std::endl;
}
