#include "min_heap.h"

MinHeap::MinHeap() : capacity(10), heapSize(0) {
    heap = new int[capacity];
}

MinHeap::~MinHeap() {
    delete[] heap;
}

void MinHeap::resize() {
    int newCapacity = capacity * 2;
    int* newHeap = new int[newCapacity];
    for (int i = 0; i < heapSize; ++i) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
    capacity = newCapacity;
}

void MinHeap::heapifyUp(int index) {
    while (index != 0 && heap[(index - 1) / 2] > heap[index]) {
        int temp = heap[index];
        heap[index] = heap[(index - 1) / 2];
        heap[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

void MinHeap::heapifyDown(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heapSize && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < heapSize && heap[right] < heap[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        int temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        heapifyDown(smallest);
    }
}

void MinHeap::insert(int key) {
    if (heapSize == capacity) resize();
    heap[heapSize] = key;
    heapifyUp(heapSize);
    heapSize++;
}

int MinHeap::extractMin() {
    if (isEmpty()) return -1;
    int min = heap[0];
    heap[0] = heap[--heapSize];
    heapifyDown(0);
    return min;
}

int MinHeap::getMin() const {
    if (isEmpty()) return -1;
    return heap[0];
}

bool MinHeap::isEmpty() const {
    return heapSize == 0;
}