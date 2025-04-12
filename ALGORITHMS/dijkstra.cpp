#include "dijkstra.h"
#include <iostream>
#include <limits>

int DijkstraGraph::findIndex(const std::string& code) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].code == code) return i;
    }
    return -1;
}

void DijkstraGraph::addAirport(const std::string& code) {
    if (findIndex(code) == -1) {
        Node node = {code, nullptr};
        nodes.push_back(node);
    }
}

void DijkstraGraph::addFlight(const std::string& from, const std::string& to, int distance, int cost) {
    int fromIdx = findIndex(from);
    int toIdx = findIndex(to);
    if (fromIdx == -1 || toIdx == -1) return;

    Edge* newEdge = new Edge{toIdx, distance, cost, nodes[fromIdx].head};
    nodes[fromIdx].head = newEdge;
}

void DijkstraGraph::shortestPath(const std::string& start, const std::string& end, bool useCost) {
    int n = nodes.size();
    std::vector<int> dist(n, std::numeric_limits<int>::max());
    std::vector<bool> visited(n, false);
    std::vector<int> prev(n, -1);

    int startIdx = findIndex(start);
    int endIdx = findIndex(end);
    if (startIdx == -1 || endIdx == -1) {
        std::cout << "Invalid airport code." << std::endl;
        return;
    }

    dist[startIdx] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (u == -1 || dist[u] == std::numeric_limits<int>::max()) break;
        visited[u] = true;

        for (Edge* e = nodes[u].head; e != nullptr; e = e->next) {
            int weight = useCost ? e->cost : e->distance;
            if (dist[u] + weight < dist[e->destination]) {
                dist[e->destination] = dist[u] + weight;
                prev[e->destination] = u;
            }
        }
    }

    if (dist[endIdx] == std::numeric_limits<int>::max()) {
        std::cout << "No path from " << start << " to " << end << std::endl;
        return;
    }

    std::vector<int> path;
    for (int at = endIdx; at != -1; at = prev[at]) path.insert(path.begin(), at);

    std::cout << "Shortest path from " << start << " to " << end << ": ";
    for (int i = 0; i < path.size(); i++) {
        std::cout << nodes[path[i]].code;
        if (i < path.size() - 1) std::cout << " -> ";
    }
    std::cout << ". Total " << (useCost ? "cost" : "distance") << ": " << dist[endIdx] << std::endl;
}
