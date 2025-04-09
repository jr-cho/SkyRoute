#include "MinHeap.h"
#include <iostream>

MinHeap::MinHeap(int cap) {
    heapSize = 0;
    this->cap = cap;
    harr = new int[cap];
}

void MinHeap::heapify(int index) {
    percolateDown(index);
}

int MinHeap::extractMin() {
    if (heapSize <= 0)
        return INT_MAX;

    if (heapSize == 1) {
        heapSize--;
        return harr[0];
    }

    int root = harr[0];
    harr[0] = harr[heapSize - 1];
    heapSize--;
    percolateDown(0);

    return root;
}

void MinHeap::insertKey() {
    if(heapSize == cap) {
      std::cout << "\nOVERFLOW: Could not insert Key\n";
      return;
    }

    heapSize++;
    int i = heapSize;
    harr[i] = k;

    percolateUp(i);
}

void MinHeap::percolateUp() {
    while (index != 0 && harr[(index - 1) / 2] > harr[index]) {
        swap(index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
}

void MinHeap::percolateDown() {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < heapSize && harr[left] < harr[smallest])
        smallest = left;

    if (right < heapSize && harr[right] < harr[smallest])
        smallest = right;

    if (smallest != index) {
        swap(index, smallest);
        percolateDown(smallest);
    }
}

int MinHeap::minimum(int a, int indexA, int b, int indexB) {
    return (a < b) ? indexA : indexB;
}

void MinHeap::swap() {
    if (heapSize == capacity) {
        std::cout << "\nOVERFLOW: Could not insert Key\n";
        return;
    }

    harr[heapSize] = k;
    percolateUp(heapSize);
    heapSize++;
}

MinHeap *MinHeap::initHeapFromArray(int *val, int len) {
  MinHeap *h = new MinHeap(len);

  for(int i=1; int i<=length; i++)
    h->harr[i] = val[i-1];

  h->heapSize = length;

  h->Heapify();
  return h;
}




