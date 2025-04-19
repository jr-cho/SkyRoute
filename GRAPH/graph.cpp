#include "graph.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>

void Graph::loadFromCSV(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string origin, destination, originCity, destCity, distanceStr, costStr;

        std::getline(ss, origin, ',');
        std::getline(ss, destination, ',');
        std::getline(ss, originCity, ',');
        std::getline(ss, destCity, ',');
        std::getline(ss, distanceStr, ',');
        std::getline(ss, costStr);

        char originCode[4], destCode[4];
        strncpy(originCode, origin.c_str(), 3); originCode[3] = '\0';
        strncpy(destCode, destination.c_str(), 3); destCode[3] = '\0';

        int distance = std::stoi(distanceStr);
        int cost = std::stoi(costStr);

        dijkstraGraph.addAirport(originCode);
        dijkstraGraph.addAirport(destCode);
        dijkstraGraph.addFlight(originCode, destCode, distance, cost);

        dfsGraph.addNode(originCode);
        dfsGraph.addNode(destCode);
        dfsGraph.addEdge(originCode, destCode);

        bfsGraph.addNode(originCode);
        bfsGraph.addNode(destCode);
        bfsGraph.addEdge(originCode, destCode);
    }
    file.close();
}

void Graph::shortestPath(const char* start, const char* end, bool useCost) {
    dijkstraGraph.shortestPath(start, end, useCost);
}

void Graph::dfs(const char* start) {
    dfsGraph.dfs(start);
}

void Graph::bfs(const char* start) {
    bfsGraph.bfs(start);
}

DijkstraGraph& Graph::getDijkstra() {
    return dijkstraGraph;
}
