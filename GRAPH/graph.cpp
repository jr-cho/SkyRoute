#include "graph.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>

int Graph::findConnectionIndex(const char* code) {
    for (int i = 0; i < connectionCounts.size(); i++) {
        if (strcmp(connectionCounts[i].code, code) == 0) return i;
    }
    return -1;
}

void Graph::updateConnectionCount(const char* from, const char* to) {
    int fromIdx = findConnectionIndex(from);
    int toIdx = findConnectionIndex(to);

    if (fromIdx == -1) {
        AirportConnectionCount acc;
        strncpy(acc.code, from, 4);
        acc.inbound = 0;
        acc.outbound = 1;
        connectionCounts.push_back(acc);
    } else {
        connectionCounts[fromIdx].outbound++;
    }

    if (toIdx == -1) {
        AirportConnectionCount acc;
        strncpy(acc.code, to, 4);
        acc.inbound = 1;
        acc.outbound = 0;
        connectionCounts.push_back(acc);
    } else {
        connectionCounts[toIdx].inbound++;
    }
}

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

        updateConnectionCount(originCode, destCode);
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

void Graph::displaySortedConnections() {
    for (int i = 0; i < connectionCounts.size(); ++i) {
        for (int j = i + 1; j < connectionCounts.size(); ++j) {
            int totalI = connectionCounts[i].inbound + connectionCounts[i].outbound;
            int totalJ = connectionCounts[j].inbound + connectionCounts[j].outbound;
            if (totalJ > totalI) {
                AirportConnectionCount temp = connectionCounts[i];
                connectionCounts[i] = connectionCounts[j];
                connectionCounts[j] = temp;
            }
        }
    }

    std::cout << "Airport\tConnections" << std::endl;
    for (const auto& entry : connectionCounts) {
        std::cout << entry.code << "\t" << (entry.inbound + entry.outbound) << std::endl;
    }
}
