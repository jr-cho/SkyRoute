#include "kruskal.h"
#include <iostream>

KruskalGraph::KruskalGraph(int v) {
    numVertices = v;
    edgeCapacity = 100;
    numEdges = 0;
    edges = new KruskalEdge[edgeCapacity];
}

KruskalGraph::~KruskalGraph() {
    delete[] edges;
}

void KruskalGraph::addEdge(int u, int v, int cost) {
    if (numEdges >= edgeCapacity) return;
    edges[numEdges++] = {u, v, cost};
}

void KruskalGraph::quickSort(int left, int right) {
    int i = left, j = right;
    KruskalEdge pivot = edges[(left + right) / 2];
    while (i <= j) {
        while (edges[i].cost < pivot.cost) i++;
        while (edges[j].cost > pivot.cost) j--;
        if (i <= j) {
            KruskalEdge temp = edges[i];
            edges[i] = edges[j];
            edges[j] = temp;
            i++; j--;
        }
    }
    if (left < j) quickSort(left, j);
    if (i < right) quickSort(i, right);
}

void KruskalGraph::buildMST() {
    quickSort(0, numEdges - 1);
    UnionFind uf(numVertices);
    int mstCost = 0;
    int components = numVertices;

    std::cout << "Minimal Spanning Forest:\nEdge\tCost" << std::endl;
    for (int i = 0; i < numEdges; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        if (uf.find(u) != uf.find(v)) {
            std::cout << u << " - " << v << "\t" << edges[i].cost << std::endl;
            mstCost += edges[i].cost;
            uf.unite(u, v);
            components--;
        }
    }

    std::cout << "Total Cost of MST: " << mstCost << std::endl;
    if (components > 1) {
        std::cout << "Note: The graph was disconnected. Displayed MST is a forest covering all components." << std::endl;
    }
}
