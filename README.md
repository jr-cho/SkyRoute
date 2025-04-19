# ✈️ Sky Route
### Graph-Based Airport Connectivity and Flight Route Optimization System

Sky Route is a C++ console-based system that models airports and flight routes using graphs. It reads data from a CSV file and allows users to explore optimal routes using various graph algorithms.

## 🚀 Features
- Load airport dataset
- Find shortest paths using Dijkstra’s algorithm
- Find all shortest paths to a U.S. state
- Search with a fixed number of stops
- Analyze direct connections to each airport
- Generate MSTs using Prim’s and Kruskal’s algorithms

## 🧠 Algorithms Used
- Dijkstra's Algorithm
- BFS / DFS
- Prim's MST
- Kruskal's MST

## 📂 Project Structure
- `DATA/`: Dataset (airports.csv)
- `GRAPH/`: Graph class and algorithms
- `MAIN/`: Main menu logic and user interaction
- `REPORT/`: Final report and analysis

🛠️ Compile and Run

With Makefile
```bash
make           # Compile the program
make run       # Compile and run the program
make clean     # Remove compiled files
```

Manual Compile
```bash
g++ -std=c++11 MAIN/main.cpp GRAPH/graph.cpp -o sky_route.out
./sky_route.out
```


## ✅ Requirements
- C++11 or higher
- No STL (except `vector`, per spec)

## Team Members
- Joshua Gottus
- Blake Millar

