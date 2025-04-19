#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include "min_heap.h"

struct Edge {
    int destination;
    int distance;
    int cost;
    Edge* next;
};

struct Node {
    char code[4];
    Edge* head;
};

class DijkstraGraph {
private:
    std::vector<Node> nodes;
    int findIndex(const char* code);
public:
    void addAirport(const char* code);
    void addFlight(const char* from, const char* to, int distance, int cost);
    void shortestPath(const char* start, const char* end, bool useCost); // true = minimize cost, false = distance
};

#endif // DIJKSTRA_H
