// ----------- main.cpp -----------
#include "graph.h"
#include "undirected_graph.h"
#include "timer.h"
#include "input_handler.h"
#include <iostream>

void showMenu() {
    std::cout << "\n===== Airport Route Optimization Menu =====\n";
    std::cout << "1. Load airport data from CSV\n";
    std::cout << "2. Find shortest path between two airports\n";
    std::cout << "3. Run DFS from an airport\n";
    std::cout << "4. Run BFS from an airport\n";
    std::cout << "5. Display total direct flight connections\n";
    std::cout << "6. Generate undirected graph (G_u)\n";
    std::cout << "7. Run Prim's MST on G_u\n";
    std::cout << "8. Run Kruskal's MST on G_u\n";
    std::cout << "0. Exit\n";
}

int main() {
    Graph directedGraph;
    UndirectedGraph undirectedGraph;
    Timer timer;
    int choice;
    bool dataLoaded = false;
    bool undirectedReady = false;

    do {
        showMenu();
        choice = getChoice();

        if (choice == 1) {
            std::cout << "\nLoading airports.csv...\n";
            timer.start();
            directedGraph.loadFromCSV("./DATA/airports.csv");
            timer.stop("CSV Load");
            dataLoaded = true;
        } else if (choice == 2 && dataLoaded) {
            char start[4], end[4];
            std::cout << "Enter origin airport code: "; getAirportCode(start);
            std::cout << "Enter destination airport code: "; getAirportCode(end);
            std::cout << "Minimize (0 = Distance, 1 = Cost): ";
            int mode = getChoice();
            directedGraph.shortestPath(start, end, mode == 1);
        } else if (choice == 3 && dataLoaded) {
            char start[4];
            std::cout << "Enter starting airport code for DFS: "; getAirportCode(start);
            directedGraph.dfs(start);
        } else if (choice == 4 && dataLoaded) {
            char start[4];
            std::cout << "Enter starting airport code for BFS: "; getAirportCode(start);
            directedGraph.bfs(start);
        } else if (choice == 5 && dataLoaded) {
            directedGraph.displaySortedConnections();
        } else if (choice == 6 && dataLoaded) {
            std::cout << "\nGenerating undirected graph...\n";
            undirectedGraph.loadFromDirected("airports.csv");
            std::cout << "Done.\n";
            undirectedReady = true;
        } else if (choice == 7 && undirectedReady) {
            std::cout << "\nRunning Prim's MST...\n";
            undirectedGraph.buildPrimMST();
        } else if (choice == 8 && undirectedReady) {
            std::cout << "\nRunning Kruskal's MST...\n";
            undirectedGraph.buildKruskalMST();
        } else if (choice == 0) {
            std::cout << "Exiting. Goodbye!\n";
        } else {
            std::cout << "\n[!] Invalid choice or missing data. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

