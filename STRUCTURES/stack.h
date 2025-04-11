#ifndef STACK_H
#define STACK_H

#include <iostream>

template <typename T>
struct StackNode {
    T data;
    StackNode* next;
    StackNode(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class Stack {
private:
    StackNode<T>* topNode;
    size_t stackSize;

public:
    Stack();
    ~Stack();
    void push(const T& value);
    T pop();
    T peek() const;
    bool isEmpty() const;
    size_t size() const;
    void clear();
};

#endif // STACK_H

