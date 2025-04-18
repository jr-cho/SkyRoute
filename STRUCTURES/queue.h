#ifndef QUEUE_H
#define QUEUE_H

class Queue {
private:
    int* data;
    int frontIndex;
    int rearIndex;
    int capacity;
    int count;

    void resize();

public:
    Queue();
    ~Queue();

    void enqueue(int value);
    int dequeue();
    int front() const;
    bool isEmpty() const;
    int size() const;
};

#endif // QUEUE_H