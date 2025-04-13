#include "undirected_graph.h"
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
UndirectedGraph::UndirectedGraph() : Graph() {}
void UndirectedGraph::addEdge(const string& node1, const string& node2, double weight) {
    Graph::addEdge(node1, node2, weight);
    Graph::addEdge(node2, node1, weight); // Add reverse for undirected
}
vector<tuple<string, string, double>> UndirectedGraph::getAllEdges() const {
    set<pair<string,string>> seen;
    vector<tuple<string, string, double>> edges;
    for (const auto& u : adjList) {        
        for (const auto& v : u.second) {
            auto w = v.second;
            if (seen.find({v.first, u.first}) == seen.end()) {
                edges.push_back({u.first, v.first, w});
                seen.insert({u.first, v.first});
            }
        }
    }
    return edges;
}
string UndirectedGraph::find(string node, unordered_map<string, string>& parent) {
    if (parent[node] != node)
        parent[node] = find(parent[node], parent);
    return parent[node];
}
void UndirectedGraph::unionSets(string u, string v, unordered_map<string, string>& parent) {
    parent[find(u, parent)] = find(v, parent);
}
double UndirectedGraph::kruskalMST() {
    auto edges = getAllEdges();
    std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return get<2>(a) < get<2>(b);
    });
    unordered_map<string, string> parent;
for (const auto& edge : edges) {
    parent[get<0>(edge)] = get<0>(edge);
    parent[get<1>(edge)] = get<1>(edge);
}
for (const auto& edge : edges) { // Corrected loop 
    parent[get<1>(edge)] = get<1>(edge);
}
double totalWeight = 0;
for (const auto& edge : edges) {
    auto u = get<0>(edge);
    auto v = get<1>(edge);
    auto w = get<2>(edge);
    if (find(u, parent) != find(v, parent)) {
        unionSets(u, v, parent);
        totalWeight += w;
    }
}
return totalWeight;
}
double UndirectedGraph::primMST() {
    auto vertices = getVertices();
    if (vertices.empty()) return 0;
    set<string> visited;
    auto cmp = [](const tuple<double, string, string>& a, const tuple<double, string, string>& b) {
        return get<0>(a) > get<0>(b);
    };
    priority_queue<tuple<double, string, string>, vector<tuple<double, string, string>>, decltype(cmp)> pq(cmp);
    string start = vertices[0];
    visited.insert(start);
    for (const auto& it : getNeighbors(start)) {
        string neighbor = it.first;
        double weight = it.second;
        pq.push({weight, start, neighbor});
    }
    double totalWeight = 0;
    while (!pq.empty()) {
        double weight = get<0>(pq.top());
        string u = get<1>(pq.top());
        string v = get<2>(pq.top());
        pq.pop();
        if (visited.find(v) != visited.end()) continue;
        visited.insert(v);
        totalWeight += weight;
        for (const auto& it : getNeighbors(v)) {
            string neighbor = it.first;
            double w = it.second;
            if (visited.find(neighbor) == visited.end()) {
                pq.push({w, v, neighbor});
            }
        }
    }
    return totalWeight;
}
