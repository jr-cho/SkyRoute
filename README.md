# ✈️ Airport Connectivity & Flight Route Optimization

This project models a real-world flight network as a graph and applies key graph algorithms to analyze connectivity and optimize routing between airports. It's designed to work without STL containers (except for `vector`) and uses custom-built data structures.

---

## 📌 Project Highlights

- **Input**: `airports.csv` dataset with flight records
- **Algorithms**:
  - `BFS` / `DFS`: Explore connectivity and reachability
  - `Dijkstra`: Shortest paths by distance or cost
  - `Kruskal`: MST using Union-Find (cycle detection)
  - `Prim`: MST using adjacency lists
- **Data Structures**:
  - Custom `Vector`, `Queue`, `Stack`, `MinHeap`, and `UnionFind`
- **Graph Representations**:
  - Directed and Undirected Graphs
  - Edge weights for both Distance and Cost
- **Use Case**: Realistic airport route optimization and efficiency analysis

---

## 🗂️ Folder Structure

```bash
.
├── ALGORITHMS
│   ├── bfs.cpp
│   ├── bfs.h
│   ├── dfs.cpp
│   ├── dfs.h
│   ├── dijkstra.cpp
│   ├── dijkstra.h
│   ├── kruskal.cpp
│   ├── kruskal.h
│   ├── prim.cpp
│   ├── prim.h
│   └── union_find.h
├── DATA
│   └── airports.csv
├── GRAPH
│   ├── graph.cpp
│   ├── graph.h
│   ├── undirected_graph.cpp
│   └── undirected_graph.h
├── LICENSE
├── MAIN
│   └── main.cpp
├── README.md
├── REPORT
│   └── presentation_slides.pdf
├── STRUCTURES
│   ├── disjoint_set.cpp
│   ├── disjoint_set.h
│   ├── min_heap.cpp
│   ├── min_heap.h
│   ├── queue.cpp
│   ├── queue.h
│   ├── stack.cpp
│   ├── stack.h
│   ├── vector.cpp
│   └── vector.h
└── UTILS
    ├── airport_utils.h
    ├── input_handler.h
    └── timer.h
```


---

## ⚙️ How to Compile & Run

Use OnlineGDB or your terminal. Example with `g++`:

```bash
g++ -std=c++20 -I./STRUCTURES -I./GRAPH -I./ALGORITHMS -I./UTILS \
    ./MAIN/main.cpp \
    ./STRUCTURES/*.cpp \
    ./ALGORITHMS/*.cpp \
    ./GRAPH/*.cpp \
    -o airport_project

./airport_project
```
Make sure to place `airports.csv` in the expected `DATA/` path or adjust the file reader accordingly.

---

## 👥 Contributors
- Joshua Gottus
- Blake Millar

---

## 📄 License

MIT License — See `LICENSE` file for full details.
