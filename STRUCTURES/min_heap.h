#ifndef MAXHEAP_H
#define MAXHEAP_H

class MinHeap {
    int *harr;
    int capacity;
    int heapSize;

public:
    MinHeap(int cap);

    void heapify(int index);

    int extractMin();

    void insertKey(int k);

    void percolateUp(int index);

    void percolateDown(int index);

    int minimum(int a, int indexA, int b, int indexB);

    void swap(int index1, int index2);

    MinHeap *initHeapFromArray(int *val, int len);

    ~MinHeap();
};

#endif

