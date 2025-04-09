## Directory Overview

### ALGORITHMS
Contains implementations of graph algorithms used for analysis and optimization.

- `bfs.h / bfs.cpp`: Implements Breadth-First Search for traversing graphs and finding paths.
- `dfs.h / dfs.cpp`: Implements Depth-First Search for graph traversal.
- `dijkstra.h / dijkstra.cpp`: Finds the shortest path in a weighted graph (based on distance or cost).
- `prim.h / prim.cpp`: Constructs a Minimum Spanning Tree (MST) using Prim’s algorithm on the undirected graph.
- `kruskal.h / kruskal.cpp`: Constructs MST using Kruskal’s algorithm, utilizing the Union-Find data structure.
- `union_find.h`: Header for the disjoint-set union-find structure, used by Kruskal’s algorithm.

---

### DATA
Houses the dataset file required for graph construction.

- `Airports Data.csv`: Raw dataset with columns: `Origin_airport`, `Destination_airport`, `Origin_city`, `Destination_city`, `Distance`, and `Cost`.

---

### GRAPH
Contains the core graph representation.

- `graph.h / graph.cpp`: Defines a directed weighted graph structure using adjacency lists. Supports edge creation and retrieval.
- `undirected_graph.h / undirected_graph.cpp`: Converts the original directed graph into an undirected version, based on specific rules (one-way or two-way with min-cost edge retention).

---

### MAIN
Main driver for running the program.

- `main.cpp`: Entry point of the program. Parses input, constructs graphs, calls algorithm functions, and displays results.

---

### REPORT
Stores documentation for grading and presentation.

- `team_project_report.pdf`: Includes class descriptions, algorithm overviews, time complexity analysis, and sample runs.
- `presentation_slides.pdf`: 3–4 minute visual overview of the project with a code demonstration.

---

### STRUCTURES
Custom implementations of data structures used throughout the project. STL is avoided except for `std::vector`.

- `disjoint_set.h`: Implements the disjoint-set (union-find) for Kruskal’s algorithm.
- `min_heap.h`: Implements a min-heap for Dijkstra’s and Prim’s priority queue behavior.
- `queue.h`: Custom queue used in BFS.
- `stack.h`: Custom stack used in DFS.
- `vector.h`: Optional custom wrapper or extension of `std::vector` if needed.

---

### UTILS
Utility headers supporting data parsing, preprocessing, and timing.

- `airport_utils.h`: Contains airport-specific helper functions (e.g., mapping city names to airports, formatting routes).
- `input_handler.h`: Reads and parses `Airports Data.csv` into graph structures.
- `timer.h`: Measures runtime performance of algorithms (optional for benchmarking).

---

## Functionality Checklist

1. Build a **weighted directed graph** from the CSV dataset using both **distance** and **cost**.
2. Use **Dijkstra’s algorithm** to:
   - Find the shortest path between two airports.
   - Find shortest paths to all airports in a specific state.
   - Handle paths with a specified number of stops.
3. Display the number of **inbound, outbound, and total connections** for each airport, sorted descending.
4. Construct an **undirected graph** from the directed graph following cost-based rules.
5. Generate **MSTs** using both **Prim’s** and **Kruskal’s** algorithms on the undirected graph.

---

