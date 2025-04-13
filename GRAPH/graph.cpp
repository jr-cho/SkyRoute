#include "graph.h"
#include <queue>
#include <unordered_map>
#include <set>
#include <limits>
#include <algorithm>
using namespace std;
Graph::Graph() {}
void Graph::addEdge(const string& source, const string& destination, double weight) {
    adjList[source].push_back({destination, weight});
    // Directed: no need to add the reverse edge
}
vector<string> Graph::getVertices() const {
    vector<string> vertices;
    for (const auto& pair : adjList) {
        vertices.push_back(pair.first);
    }
    return vertices;
}

vector<pair<string, double>> Graph::getNeighbors(const string& vertex) const {
    auto it = adjList.find(vertex);
    if (it != adjList.end()) {
        return it->second;
    }
    return {};
}

vector<string> Graph::shortestPath(const string& start, const string& end) {
    unordered_map<string, double> distances;
    unordered_map<string, string> prev;
    auto cmp = [&](const string& a, const string& b) {
        return distances[a] > distances[b];
    };
    priority_queue<string, vector<string>, decltype(cmp)> pq(cmp);

    for (const auto& v : adjList) {
        distances[v.first] = numeric_limits<double>::infinity();
    }
    distances[start] = 0;
    pq.push(start);
    while (!pq.empty()) {
        string current = pq.top(); 
        pq.pop();
        if (current == end) break;

        for (const auto& neighborPair : adjList[current]) {
            string neighbor = neighborPair.first;
            double weight = neighborPair.second;
            double newDist = distances[current] + weight;
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                prev[neighbor] = current;
                pq.push(neighbor);
            }
        }
    }
    vector<string> path;
    for (string at = end; !at.empty(); at = prev[at]) {
        path.push_back(at);
    }

    reverse(path.begin(), path.end());

    if (path.front() != start) return {}; // No path found
    return path;
}
