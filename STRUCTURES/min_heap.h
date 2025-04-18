#ifndef MIN_HEAP_H
#define MIN_HEAP_H

class MinHeap {
private:
    int* heap;
    int capacity;
    int heapSize;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();

public:
    MinHeap();
    ~MinHeap();

    void insert(int key);
    int extractMin();
    int getMin() const;
    bool isEmpty() const;
};

#endif // MIN_HEAP_H