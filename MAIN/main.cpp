#include "../GRAPH/graph.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main() {
    Graph g, g_u;
    bool graphLoaded = false;

    while (true) {
        cout << "\nSelect an option:\n";
        cout << "0. Load airport dataset from CSV\n";
        cout << "1. Shortest path between two airports\n";
        cout << "2. All shortest paths from an airport to all airports in a state\n";
        cout << "3. Shortest path between two airports with a given number of stops\n";
        cout << "4. List total direct flight connections for each airport\n";
        cout << "5. Minimum Spanning Tree (Prim's algorithm)\n";
        cout << "6. Minimum Spanning Tree (Kruskal's algorithm)\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";

        int choice;
        if (!(cin >> choice)) {
            return 0;
        }

        if (choice == 9) {
            break;
        }

        if (choice == 0) {
            if (g.loadFromCSV("DATA/airports.csv")) {
                cout << "CSV loaded successfully.\n";
                g_u = g.createUndirectedGraph();
                graphLoaded = true;
            } else {
                cerr << "Failed to load dataset.\n";
            }
            continue;
        }

        if (!graphLoaded) {
            cout << "Please load the CSV dataset first (Option 0).\n";
            continue;
        }

        if (choice == 1) {
            string originCode, destCode;
            cout << "Enter origin airport code: ";
            cin >> originCode;
            cout << "Enter destination airport code: ";
            cin >> destCode;
            for (char &c : originCode) c = toupper(c);
            for (char &c : destCode) c = toupper(c);

            int originIndex = g.findAirportIndex(originCode);
            int destIndex = g.findAirportIndex(destCode);
            if (originIndex == -1 || destIndex == -1) {
                cout << "One or both airport codes not found in the dataset." << endl;
            } else {
                vector<int> dist, parent;
                g.dijkstraShortestPaths(originIndex, dist, parent);
                if (dist[destIndex] == INF) {
                    cout << "Shortest route from " << originCode << " to " << destCode << ": None" << endl;
                } else {
                    vector<int> path;
                    for (int v = destIndex; v != -1; v = parent[v]) path.push_back(v);
                    for (int i = 0; i < (int)path.size() / 2; ++i)
                        swap(path[i], path[path.size() - 1 - i]);
                    string pathStr = g.getAirportCode(path[0]);
                    for (size_t i = 1; i < path.size(); ++i)
                        pathStr += " -> " + g.getAirportCode(path[i]);
                    int totalCost = 0;
                    for (size_t i = 0; i < path.size() - 1; ++i)
                        totalCost += g.getFlightCost(path[i], path[i+1]);
                    cout << "Shortest route from " << originCode << " to " << destCode << ": "
                         << pathStr << ". The length is " << dist[destIndex]
                         << ". The cost is " << totalCost << "." << endl;
                }
            }
        }

        else if (choice == 2) {
            string originCode, stateCode;
            cout << "Enter origin airport code: ";
            cin >> originCode;
            cout << "Enter destination state (two-letter code): ";
            cin >> stateCode;
            for (char &c : originCode) c = toupper(c);
            for (char &c : stateCode) c = toupper(c);

            int originIndex = g.findAirportIndex(originCode);
            if (originIndex == -1) {
                cout << "Origin airport code not found." << endl;
            } else {
                vector<int> stateAirports = g.getAirportsInState(stateCode);
                if (stateAirports.empty()) {
                    cout << "No airports found in state " << stateCode << "." << endl;
                } else {
                    vector<int> dist, parent;
                    g.dijkstraShortestPaths(originIndex, dist, parent);
                    struct PathInfo { string pathStr; int distance; int cost; };
                    vector<PathInfo> results;
                    for (int idx : stateAirports) {
                        if (idx == originIndex) continue;
                        if (dist[idx] == INF) continue;
                        vector<int> path;
                        for (int v = idx; v != -1; v = parent[v]) path.push_back(v);
                        for (int i = 0; i < (int)path.size() / 2; ++i)
                            swap(path[i], path[path.size() - 1 - i]);
                        string pathStr = g.getAirportCode(path[0]);
                        for (size_t i = 1; i < path.size(); ++i)
                            pathStr += "->" + g.getAirportCode(path[i]);
                        int totalCost = 0;
                        for (size_t i = 0; i < path.size() - 1; ++i)
                            totalCost += g.getFlightCost(path[i], path[i+1]);
                        results.push_back({pathStr, dist[idx], totalCost});
                    }

                    if (results.empty()) {
                        cout << "Shortest paths from " << originCode << " to " << stateCode
                             << " state airports are: None" << endl;
                    } else {
                        cout << "Shortest paths from " << originCode << " to " << stateCode
                             << " state airports are:\n\n";
                        cout << left << setw(40) << "Path"
                             << right << setw(7) << "Length"
                             << setw(7) << "Cost" << endl;
                        for (auto &res : results) {
                            cout << left << setw(40) << res.pathStr
                                 << right << setw(7) << res.distance
                                 << setw(7) << res.cost << endl;
                        }
                    }
                }
            }
        }

        else if (choice == 3) {
            string originCode, destCode;
            int stops;
            cout << "Enter origin airport code: ";
            cin >> originCode;
            cout << "Enter destination airport code: ";
            cin >> destCode;
            cout << "Enter number of stops: ";
            cin >> stops;
            for (char &c : originCode) c = toupper(c);
            for (char &c : destCode) c = toupper(c);

            int originIndex = g.findAirportIndex(originCode);
            int destIndex = g.findAirportIndex(destCode);
            if (originIndex == -1 || destIndex == -1) {
                cout << "One or both airport codes not found." << endl;
            } else {
                vector<int> path;
                int distance, cost;
                bool found = g.findShortestPathWithStops(originIndex, destIndex, stops, path, distance, cost);
                if (!found) {
                    cout << "Shortest route from " << originCode << " to " << destCode
                         << " with " << stops << " stops: None" << endl;
                } else {
                    string pathStr = g.getAirportCode(path[0]);
                    for (size_t i = 1; i < path.size(); ++i)
                        pathStr += " -> " + g.getAirportCode(path[i]);
                    cout << "Shortest route from " << originCode << " to " << destCode
                         << " with " << stops << " stops: " << pathStr
                         << ". The length is " << distance << ". The cost is " << cost << "." << endl;
                }
            }
        }

        else if (choice == 4) {
            int n = g.getNumAirports();
            vector<int> indices(n);
            for (int i = 0; i < n; ++i) indices[i] = i;
            for (int i = 0; i < n; ++i) {
                int maxIdx = i;
                for (int j = i + 1; j < n; ++j) {
                    int totalJ = g.getTotalConnections(indices[j]);
                    int totalMax = g.getTotalConnections(indices[maxIdx]);
                    if (totalJ > totalMax || (totalJ == totalMax &&
                        g.getAirportCode(indices[j]) < g.getAirportCode(indices[maxIdx]))) {
                        maxIdx = j;
                    }
                }
                swap(indices[i], indices[maxIdx]);
            }

            cout << "Airport     Connections" << endl << endl;
            for (int idx : indices)
                cout << g.getAirportCode(idx) << "     " << g.getTotalConnections(idx) << endl;
        }

        else if (choice == 5) {
            Graph::MSTResult mst = g_u.computeMSTPrim();
            if (mst.isForest) {
                cout << "Graph is not connected. MST cannot be formed." << endl;
            } else {
                cout << "Minimal Spanning Tree:\n\n";
                cout << "Edge      Weight" << endl;
                for (auto& edge : mst.edges) {
                    cout << g_u.getAirportCode(edge.first) << " - "
                         << g_u.getAirportCode(edge.second) << "     "
                         << g_u.getFlightCost(edge.first, edge.second) << endl;
                }
                cout << "\nTotal Cost of MST: " << mst.totalCost << endl;
            }
        }

        else if (choice == 6) {
            Graph::MSTResult mst = g_u.computeMSTKruskal();
            if (mst.isForest) {
                cout << "Minimal Spanning Forest:\n\n";
            } else {
                cout << "Minimal Spanning Tree:\n\n";
            }
            cout << "Edge      Weight" << endl;
            for (auto& edge : mst.edges) {
                cout << g_u.getAirportCode(edge.first) << " - "
                     << g_u.getAirportCode(edge.second) << "     "
                     << g_u.getFlightCost(edge.first, edge.second) << endl;
            }
            cout << "\nTotal Cost of MST: " << mst.totalCost << endl;
        }

        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

