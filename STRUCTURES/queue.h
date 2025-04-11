#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
struct QueueNode {
    T data;
    QueueNode* next;
    QueueNode(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class Queue {
private:
    QueueNode<T>* frontNode;
    QueueNode<T>* rearNode;
    size_t queueSize;

public:
    Queue();
    ~Queue();

    void enqueue(const T& value);
    T dequeue();
    T front() const;
    T back() const;
    bool isEmpty() const;
    size_t size() const;
    void clear();
};

#endif // QUEUE_H

