#ifndef MIN_HEAP_H
#define MIN_HEAP_H

struct HeapNode {
    int vertex;
    int dist;
};

class MinHeap {
private:
    HeapNode* heap;
    int capacity;
    int heapSize;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();

public:
    MinHeap(int cap = 100);
    ~MinHeap();

    void insert(int vertex, int dist);
    HeapNode extractMin();
    HeapNode getMin() const;
    bool isEmpty() const;
};

#endif // MIN_HEAP_H
