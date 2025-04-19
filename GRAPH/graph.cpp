#include "graph.h"
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

// Constructor: initialize an empty graph
Graph::Graph() {
    // All vectors start empty; they will be populated as data is loaded
}

// Add a new airport or return index if it already exists
int Graph::getOrAddAirport(const string& code, const string& city, const string& state) {
    // Linear search for existing airport code
    for (int i = 0; i < (int)airports.size(); ++i) {
        if (airports[i].code == code) {
            return i;
        }
    }
    // If not found, create a new Airport entry
    Airport newAirport;
    newAirport.code = code;
    newAirport.city = city;
    newAirport.state = state;
    airports.push_back(newAirport);
    // Add a new adjacency list for this airport
    adjList.emplace_back();
    // Initialize inbound/outbound counts for the new airport
    inboundCount.push_back(0);
    outboundCount.push_back(0);
    return (int)airports.size() - 1;
}

// Private helper: add a directed edge from airport u to v with given distance and cost
void Graph::addEdge(int u, int v, int distance, int cost) {
    Edge edge;
    edge.dest = v;
    edge.distance = distance;
    edge.cost = cost;
    adjList[u].push_back(edge);
    // Update direct connections counts
    outboundCount[u] += 1;
    inboundCount[v] += 1;
}

// Load graph data from a CSV file into the directed graph
bool Graph::loadFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return false;
    }
    string line;
    // Read the first line (possibly header)
    if (!getline(file, line)) {
        cerr << "Error: File " << filename << " is empty." << endl;
        file.close();
        return false;
    }
    // If first line contains column names, skip it
    if (line.find("Origin_airport") != string::npos) {
        // This is a header line; read the next line for data
        if (!getline(file, line)) {
            cerr << "Error: No data found in " << filename << endl;
            file.close();
            return false;
        }
    }

    // Lambda to trim whitespace from both ends of a string
    auto trim = [&](string &s) {
        while (!s.empty() && isspace((unsigned char)s.front())) s.erase(s.begin());
        while (!s.empty() && isspace((unsigned char)s.back())) s.pop_back();
    };

    // Process each line in the CSV
    do {
        if (line.empty()) continue;  // skip empty lines if any

        // Parse CSV line into fields, taking into account quoted commas in city names
        vector<string> fields;
        string field;
        bool inQuotes = false;
        for (char ch : line) {
            if (ch == '\"') {
                // Toggle quote state, but do not include the quote in field data
                inQuotes = !inQuotes;
            } else if (ch == ',' && !inQuotes) {
                // Comma outside quotes: end of one field
                fields.push_back(field);
                field.clear();
            } else {
                // Regular character (or comma inside quotes)
                field.push_back(ch);
            }
        }
        fields.push_back(field);

        // Trim spaces and surrounding quotes from each field
        for (string &f : fields) {
            trim(f);
            if (!f.empty() && f.front() == '\"' && f.back() == '\"') {
                // Remove enclosing quotes if any remain
                f = f.substr(1, f.size() - 2);
            }
            trim(f);
        }

        if (fields.size() < 6) {
            continue; // Skip malformed line (not enough fields)
        }

        // Extract values from fields
        string originCode = fields[0];
        string destCode   = fields[1];
        string originCityState = fields[2];
        string destCityState   = fields[3];
        int distance = 0;
        int cost = 0;
        try {
            distance = stoi(fields[4]);
            cost = stoi(fields[5]);
        } catch (...) {
            // If distance or cost conversion fails, skip this line
            continue;
        }

        // Separate city and state (e.g., "CityName, ST") for origin
        string originCity = originCityState;
        string originState = "";
        size_t commaPos = originCity.find_last_of(',');
        if (commaPos != string::npos) {
            originState = originCity.substr(commaPos + 1);
            originCity = originCity.substr(0, commaPos);
        }
        trim(originCity);
        trim(originState);
        // Separate city and state for destination
        string destCity = destCityState;
        string destState = "";
        commaPos = destCity.find_last_of(',');
        if (commaPos != string::npos) {
            destState = destCity.substr(commaPos + 1);
            destCity = destCity.substr(0, commaPos);
        }
        trim(destCity);
        trim(destState);

        // Add airports to the graph (get index if already present, or create new)
        int originIndex = getOrAddAirport(originCode, originCity, originState);
        int destIndex   = getOrAddAirport(destCode, destCity, destState);
        // Add directed edge for this flight route
        addEdge(originIndex, destIndex, distance, cost);
    } while (getline(file, line));

    file.close();
    return true;
}

// Find the index of an airport given its code (returns -1 if not found)
int Graph::findAirportIndex(const string& code) const {
    for (int i = 0; i < (int)airports.size(); ++i) {
        if (airports[i].code == code) {
            return i;
        }
    }
    return -1;
}

// Create an undirected graph G_u from the directed graph G using the specified rules
Graph Graph::createUndirectedGraph() const {
    Graph undirected;
    int n = (int)airports.size();
    // Copy all airport nodes (so codes and city/state info are preserved)
    undirected.airports = airports;
    undirected.adjList.resize(n);
    undirected.inboundCount.assign(n, 0);
    undirected.outboundCount.assign(n, 0);

    // Prepare a matrix to track the minimum cost between any two airports
    vector< vector<int> > minCost(n, vector<int>(n, INF));
    for (int u = 0; u < n; ++u) {
        for (const Edge& edge : adjList[u]) {
            int v = edge.dest;
            if (edge.cost < minCost[u][v]) {
                minCost[u][v] = edge.cost;
            }
        }
    }
    // Go through each pair of vertices and add appropriate undirected edges
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            bool edgeIJ = (minCost[i][j] < INF);
            bool edgeJI = (minCost[j][i] < INF);
            if (edgeIJ && !edgeJI) {
                // Only one directed edge (i -> j) exists
                int c = minCost[i][j];
                undirected.addEdge(i, j, c, c);
                undirected.addEdge(j, i, c, c);
            } else if (!edgeIJ && edgeJI) {
                // Only one directed edge (j -> i) exists
                int c = minCost[j][i];
                undirected.addEdge(i, j, c, c);
                undirected.addEdge(j, i, c, c);
            } else if (edgeIJ && edgeJI) {
                // Both directions exist; keep one undirected edge with the minimum cost
                int c = (minCost[i][j] < minCost[j][i] ? minCost[i][j] : minCost[j][i]);
                undirected.addEdge(i, j, c, c);
                undirected.addEdge(j, i, c, c);
            }
            // If neither edge exists, nothing to add for this pair
        }
    }
    return undirected;
}

// Breadth-First Search from a starting index, returns count of reachable airports
int Graph::BFS(int startIndex) const {
    int n = (int)airports.size();
    if (startIndex < 0 || startIndex >= n) return 0;
    vector<bool> visited(n, false);
    vector<int> q;
    visited[startIndex] = true;
    q.push_back(startIndex);
    int count = 1;
    size_t qi = 0;
    // Standard BFS using a queue (vector used as queue here)
    while (qi < q.size()) {
        int u = q[qi++];
        for (const Edge& edge : adjList[u]) {
            int v = edge.dest;
            if (!visited[v]) {
                visited[v] = true;
                q.push_back(v);
                count++;
            }
        }
    }
    return count;
}

// Dijkstra's algorithm for shortest paths from origin (using distance as weight)
void Graph::dijkstraShortestPaths(int originIndex, vector<int>& dist, vector<int>& parent) const {
    int n = (int)airports.size();
    dist.assign(n, INF);
    parent.assign(n, -1);
    if (originIndex < 0 || originIndex >= n) {
        return;
    }
    // Initialize source vertex
    dist[originIndex] = 0;
    parent[originIndex] = -1;
    vector<bool> visited(n, false);

    // Iterate to find shortest distances to all vertices
    for (int count = 0; count < n; ++count) {
        // Pick the unvisited vertex with the smallest distance
        int u = -1;
        int minDist = INF;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        if (u == -1) break;  // no more reachable vertices
        visited[u] = true;
        // Relax edges from vertex u
        for (const Edge& edge : adjList[u]) {
            int v = edge.dest;
            if (!visited[v] && dist[u] + edge.distance < dist[v]) {
                dist[v] = dist[u] + edge.distance;
                parent[v] = u;
            }
        }
    }
}

// DFS utility to find a path with exactly 'remainingEdges' edges from currentIndex to destIndex
void Graph::dfsUtilStops(int currentIndex, int destIndex, int remainingEdges, vector<bool>& visited,
                         int currentDistance, int currentCost, vector<int>& currentPath,
                         int& bestDistance, int& bestCost, vector<int>& bestPath) const {
    if (remainingEdges == 0) {
        // No more edges to use; check if we arrived at the destination
        if (currentIndex == destIndex) {
            // Found a path with the exact number of edges
            if (bestDistance == INF || currentDistance < bestDistance) {
                bestDistance = currentDistance;
                bestCost = currentCost;
                bestPath = currentPath;
            }
        }
        return;
    }
    // Try extending the path by one more edge
    for (const Edge& edge : adjList[currentIndex]) {
        int v = edge.dest;
        if (!visited[v]) {
            visited[v] = true;
            currentPath.push_back(v);
            dfsUtilStops(v, destIndex, remainingEdges - 1, visited,
                         currentDistance + edge.distance, currentCost + edge.cost,
                         currentPath, bestDistance, bestCost, bestPath);
            // Backtrack
            currentPath.pop_back();
            visited[v] = false;
        }
    }
}

// Find the shortest path with a given number of stops (DFS search with depth limit)
bool Graph::findShortestPathWithStops(int originIndex, int destIndex, int stops,
                                      std::vector<int>& outPath, int& outDistance, int& outCost) const {
    int n = (int)airports.size();
    outPath.clear();
    outDistance = INF;
    outCost = INF;
    if (originIndex < 0 || originIndex >= n || destIndex < 0 || destIndex >= n) {
        return false;
    }
    // Depth-limited DFS from the origin
    vector<bool> visited(n, false);
    vector<int> currentPath;
    int bestDistance = INF;
    int bestCost = INF;
    vector<int> bestPath;
    visited[originIndex] = true;
    currentPath.push_back(originIndex);
    // 'stops' is number of intermediate stops, so total edges = stops + 1
    dfsUtilStops(originIndex, destIndex, stops + 1, visited, 0, 0, currentPath, bestDistance, bestCost, bestPath);
    if (bestDistance == INF) {
        // No path found with the exact number of stops
        return false;
    }
    outDistance = bestDistance;
    outCost = bestCost;
    outPath = bestPath;
    return true;
}

// Compute Minimum Spanning Tree using Prim's algorithm (on an undirected graph)
Graph::MSTResult Graph::computeMSTPrim() const {
    MSTResult result;
    int n = (int)airports.size();
    if (n == 0) return result;
    vector<int> key(n, INF);
    vector<int> parentIdx(n, -1);
    vector<bool> inMST(n, false);

    // Start Prim's from vertex 0 (arbitrary start)
    key[0] = 0;
    parentIdx[0] = -1;

    for (int count = 0; count < n; ++count) {
        // Pick the vertex not in MST with the smallest key
        int u = -1;
        int minKey = INF;
        for (int v = 0; v < n; ++v) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }
        if (u == -1) break;
        if (key[u] == INF) {
            // If we encounter a vertex with INF key, the graph is disconnected
            result.isForest = true;
            break;
        }
        inMST[u] = true;
        if (parentIdx[u] != -1) {
            // Add the edge (parent -> u) to the MST result
            result.edges.emplace_back(parentIdx[u], u);
            result.totalCost += key[u];
        }
        // Update keys of neighbors of u
        for (const Edge& edge : adjList[u]) {
            int v = edge.dest;
            if (!inMST[v] && edge.cost < key[v]) {
                key[v] = edge.cost;
                parentIdx[v] = u;
            }
        }
    }
    // If graph is disconnected, result.isForest will be true (MST is incomplete)
    return result;
}

// Compute MST (or Minimum Spanning Forest) using Kruskal's algorithm
Graph::MSTResult Graph::computeMSTKruskal() const {
    MSTResult result;
    int n = (int)airports.size();
    if (n == 0) return result;

    // Structure for an edge with cost (for sorting)
    struct KEdge { int u; int v; int cost; };
    vector<KEdge> edges;
    edges.reserve(adjList.size() * 2);
    // Collect each undirected edge once (u < v to avoid duplicates)
    for (int u = 0; u < n; ++u) {
        for (const Edge& edge : adjList[u]) {
            int v = edge.dest;
            if (u < v) {
                KEdge e = {u, v, edge.cost};
                edges.push_back(e);
            }
        }
    }
    // Sort edges by cost (using selection sort to avoid other STL algorithms)
    int m = (int)edges.size();
    for (int i = 0; i < m; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < m; ++j) {
            if (edges[j].cost < edges[minIdx].cost) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            // Swap edge i and edge minIdx
            KEdge temp = edges[i];
            edges[i] = edges[minIdx];
            edges[minIdx] = temp;
        }
    }

    // Initialize Union-Find sets for all vertices
    vector<int> parent(n);
    vector<int> rank(n, 0);
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
    // Lambda for Union-Find 'find' operation with path compression
    auto findSet = [&](int a) {
        while (parent[a] != a) {
            parent[a] = parent[parent[a]];
            a = parent[a];
        }
        return a;
    };
    // Process edges in increasing order of cost
    for (const KEdge& e : edges) {
        int ru = findSet(e.u);
        int rv = findSet(e.v);
        if (ru != rv) {
            // Union the sets of u and v
            if (rank[ru] < rank[rv]) {
                parent[ru] = rv;
            } else if (rank[ru] > rank[rv]) {
                parent[rv] = ru;
            } else {
                parent[rv] = ru;
                rank[ru] += 1;
            }
            // Add this edge to the MST (or forest) result
            result.edges.emplace_back(e.u, e.v);
            result.totalCost += e.cost;
        }
    }
    // If not all vertices are connected, we have a spanning forest
    if (result.edges.size() < (unsigned)(n - 1)) {
        result.isForest = true;
    }
    return result;
}

// Utility: get total number of airports in the graph
int Graph::getNumAirports() const {
    return (int)airports.size();
}

// Utility: get the airport code for a given index
string Graph::getAirportCode(int index) const {
    if (index < 0 || index >= (int)airports.size()) {
        return "";
    }
    return airports[index].code;
}

// Utility: get all airport indices in a given state (matching state code)
vector<int> Graph::getAirportsInState(const string& state) const {
    vector<int> result;
    for (int i = 0; i < (int)airports.size(); ++i) {
        if (airports[i].state == state) {
            result.push_back(i);
        }
    }
    return result;
}

// Utility: get total direct flight connections (inbound + outbound) for a given airport index
int Graph::getTotalConnections(int index) const {
    if (index < 0 || index >= (int)airports.size()) return 0;
    return inboundCount[index] + outboundCount[index];
}

// Utility: get the cost of a direct flight from u to v (returns -1 if no direct edge)
int Graph::getFlightCost(int u, int v) const {
    if (u < 0 || u >= (int)airports.size()) return -1;
    for (const Edge& edge : adjList[u]) {
        if (edge.dest == v) {
            return edge.cost;
        }
    }
    return -1;
}

