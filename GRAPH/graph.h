#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include <limits>
using namespace std;
class Graph {
public:
    Graph();
    void addEdge(const string& source, const string& destination, double weight);
    vector<string> getVertices() const;
    vector<pair<string, double>> getNeighbors(const string& vertex) const;

    // Dijkstra's algorithm to find shortest path
    vector<string> shortestPath(const string& start, const string& end);

protected:
    unordered_map<string, vector<pair<string, double>>> adjList;
};
#endif // GRAPH_H
