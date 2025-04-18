#include "queue.h"
#include <iostream>

Queue::Queue() : frontIndex(0), rearIndex(0), capacity(10), count(0) {
    data = new int[capacity];
}

Queue::~Queue() {
    delete[] data;
}

void Queue::resize() {
    int newCapacity = capacity * 2;
    int* newData = new int[newCapacity];
    for (int i = 0; i < count; ++i) {
        newData[i] = data[(frontIndex + i) % capacity];
    }
    delete[] data;
    data = newData;
    frontIndex = 0;
    rearIndex = count;
    capacity = newCapacity;
}

void Queue::enqueue(int value) {
    if (count == capacity) resize();
    data[rearIndex] = value;
    rearIndex = (rearIndex + 1) % capacity;
    ++count;
}

int Queue::dequeue() {
    if (isEmpty()) return -1;
    int value = data[frontIndex];
    frontIndex = (frontIndex + 1) % capacity;
    --count;
    return value;
}

int Queue::front() const {
    if (isEmpty()) return -1;
    return data[frontIndex];
}

bool Queue::isEmpty() const {
    return count == 0;
}

int Queue::size() const {
    return count;
}