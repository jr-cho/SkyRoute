#include "kruskal.h"
#include <iostream>

KruskalGraph::KruskalGraph(int v) {
    numVertices = v;
    edgeCapacity = 100;
    numEdges = 0;
    edges = new KruskalEdge[edgeCapacity];
    parent = new int[v];
    for (int i = 0; i < v; i++) parent[i] = i;
}

KruskalGraph::~KruskalGraph() {
    delete[] edges;
    delete[] parent;
}

int KruskalGraph::findSet(int i) {
    if (parent[i] != i)
        parent[i] = findSet(parent[i]);
    return parent[i];
}

void KruskalGraph::unionSets(int u, int v) {
    int uRoot = findSet(u);
    int vRoot = findSet(v);
    parent[uRoot] = vRoot;
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
    int mstCost = 0;
    std::cout << "Minimal Spanning Tree:\nEdge\tCost" << std::endl;
    for (int i = 0; i < numEdges; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        if (findSet(u) != findSet(v)) {
            std::cout << u << " - " << v << "\t" << edges[i].cost << std::endl;
            mstCost += edges[i].cost;
            unionSets(u, v);
        }
    }
    std::cout << "Total Cost of MST: " << mstCost << std::endl;
}

