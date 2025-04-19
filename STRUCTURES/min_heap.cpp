#include "min_heap.h"
#include <climits>

MinHeap::MinHeap(int cap) {
    capacity = cap;
    heapSize = 0;
    heap = new HeapNode[capacity];
}

MinHeap::~MinHeap() {
    delete[] heap;
}

bool MinHeap::isEmpty() const {
    return heapSize == 0;
}

HeapNode MinHeap::getMin() const {
    if (isEmpty()) return {-1, INT_MAX};
    return heap[0];
}

void MinHeap::insert(int vertex, int dist) {
    if (heapSize == capacity) resize();
    heap[heapSize] = {vertex, dist};
    heapifyUp(heapSize);
    heapSize++;
}

HeapNode MinHeap::extractMin() {
    if (isEmpty()) return {-1, INT_MAX};
    HeapNode root = heap[0];
    heap[0] = heap[--heapSize];
    heapifyDown(0);
    return root;
}

void MinHeap::heapifyUp(int i) {
    while (i > 0 && heap[i].dist < heap[(i - 1) / 2].dist) {
        HeapNode temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

void MinHeap::heapifyDown(int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && heap[left].dist < heap[smallest].dist) smallest = left;
    if (right < heapSize && heap[right].dist < heap[smallest].dist) smallest = right;

    if (smallest != i) {
        HeapNode temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        heapifyDown(smallest);
    }
}

void MinHeap::resize() {
    capacity *= 2;
    HeapNode* newHeap = new HeapNode[capacity];
    for (int i = 0; i < heapSize; i++) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
}

