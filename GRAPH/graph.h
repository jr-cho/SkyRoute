#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

// Constant for representing "infinite" distance (no connection)
static const int INF = 1000000000;

class Graph {
private:
    struct Airport {
        std::string code;
        std::string city;
        std::string state;
    };
    struct Edge {
        int dest;
        int distance;
        int cost;
    };
    std::vector<Airport> airports;              // List of airports (nodes)
    std::vector< std::vector<Edge> > adjList;   // Adjacency list: edges from each airport
    std::vector<int> inboundCount;   // inbound flight count for each airport
    std::vector<int> outboundCount;  // outbound flight count for each airport

    // Add a directed edge from u to v with given distance and cost
    void addEdge(int u, int v, int distance, int cost);

    // Add a new airport or return its index if it already exists
    int getOrAddAirport(const std::string& code, const std::string& city, const std::string& state);

    // DFS helper for finding a path with an exact number of stops (edges)
    void dfsUtilStops(int currentIndex, int destIndex, int remainingEdges, std::vector<bool>& visited,
                      int currentDistance, int currentCost, std::vector<int>& currentPath,
                      int& bestDistance, int& bestCost, std::vector<int>& bestPath) const;

public:
    // Constructor
    Graph();

    // Load graph data from a CSV file. Returns true if loaded successfully.
    bool loadFromCSV(const std::string& filename);

    // Find index of an airport by its code, or -1 if not found
    int findAirportIndex(const std::string& code) const;

    // Create an undirected graph G_u from this directed graph according to the specification
    Graph createUndirectedGraph() const;

    // Breadth-First Search from a starting airport index (returns count of reachable vertices)
    int BFS(int startIndex) const;

    // Dijkstra's algorithm to compute shortest distances from an origin index (uses distance as weight).
    // Outputs distance and parent arrays for all vertices.
    void dijkstraShortestPaths(int originIndex, std::vector<int>& dist, std::vector<int>& parent) const;

    // Find shortest path between origin and destination with a given number of stops (intermediate vertices).
    // Returns true if such a path exists. Outputs the path (sequence of indices), total distance and total cost.
    bool findShortestPathWithStops(int originIndex, int destIndex, int stops, 
                                   std::vector<int>& outPath, int& outDistance, int& outCost) const;

    // Utility functions to access airport data
    int getNumAirports() const;
    std::string getAirportCode(int index) const;
    std::vector<int> getAirportsInState(const std::string& state) const;
    int getTotalConnections(int index) const;
    int getFlightCost(int u, int v) const;

    // Structure to hold MST result (for Prim's or Kruskal's algorithms)
    struct MSTResult {
        std::vector< std::pair<int,int> > edges;  // edges in MST (pairs of vertex indices)
        int totalCost;
        bool isForest; // true if graph was not fully connected (result is a forest rather than a single tree)
        MSTResult() : totalCost(0), isForest(false) {}
    };

    // Compute Minimum Spanning Tree using Prim's algorithm (on the undirected graph).
    MSTResult computeMSTPrim() const;

    // Compute Minimum Spanning Tree (or Forest if disconnected) using Kruskal's algorithm.
    MSTResult computeMSTKruskal() const;
};

#endif // GRAPH_H

