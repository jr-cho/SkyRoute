#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H
#include "graph.h"
using namespace std;
class UndirectedGraph : public Graph {
public:
    UndirectedGraph();
    void addEdge(const string& node1, const string& node2, double weight);
    // MST Algorithms
    double primMST();
    double kruskalMST();
private:
    vector<tuple<string, string, double>> getAllEdges() const;
    string find(string node, unordered_map<string, string>& parent);
    void unionSets(string u, string v, unordered_map<string, string>& parent);
};
#endif // UNDIRECTED_GRAPH_H
