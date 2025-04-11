#include "Queue.h"
#include <stdexcept>

template <typename T>
Queue<T>::Queue() : frontNode(nullptr), rearNode(nullptr), queueSize(0) {}

template <typename T>
Queue<T>::~Queue() {
    clear();
}

template <typename T>
void Queue<T>::enqueue(const T& value) {
    QueueNode<T>* newNode = new QueueNode<T>(value);
    if (rearNode) {
        rearNode->next = newNode;
    } else {
        frontNode = newNode;
    }
    rearNode = newNode;
    ++queueSize;
}

template <typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty. Cannot dequeue.");
    }
    QueueNode<T>* temp = frontNode;
    T dequeuedValue = temp->data;
    frontNode = frontNode->next;
    if (!frontNode) {
        rearNode = nullptr;
    }
    delete temp;
    --queueSize;
    return dequeuedValue;
}

template <typename T>
T Queue<T>::front() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty. Cannot access front.");
    }
    return frontNode->data;
}

template <typename T>
T Queue<T>::back() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty. Cannot access back.");
    }
    return rearNode->data;
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return frontNode == nullptr;
}

template <typename T>
size_t Queue<T>::size() const {
    return queueSize;
}

template <typename T>
void Queue<T>::clear() {
    while (!isEmpty()) {
        dequeue();
    }
}

// Explicit template instantiation for int type
template class Queue<int>;

