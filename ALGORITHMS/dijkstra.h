#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <string>

struct Edge {
    int destination;
    int distance;
    int cost;
    Edge* next;
};

struct Node {
    std::string code;
    Edge* head;
};

class DijkstraGraph {
private:
    std::vector<Node> nodes;
    int findIndex(const std::string& code);
public:
    void addAirport(const std::string& code);
    void addFlight(const std::string& from, const std::string& to, int distance, int cost);
    void shortestPath(const std::string& start, const std::string& end, bool useCost);
};

#endif // DIJKSTRA
