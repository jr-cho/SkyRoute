#include "stack.h"
#include <iostream>

Stack::Stack() : topIndex(-1), capacity(10) {
    data = new int[capacity];
}

Stack::~Stack() {
    delete[] data;
}

void Stack::resize() {
    int newCapacity = capacity * 2;
    int* newData = new int[newCapacity];
    for (int i = 0; i <= topIndex; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void Stack::push(int value) {
    if (topIndex + 1 == capacity) resize();
    data[++topIndex] = value;
}

int Stack::pop() {
    if (isEmpty()) return -1;
    return data[topIndex--];
}

int Stack::top() const {
    if (isEmpty()) return -1;
    return data[topIndex];
}

bool Stack::isEmpty() const {
    return topIndex == -1;
}

int Stack::size() const {
    return topIndex + 1;
}