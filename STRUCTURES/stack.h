#ifndef STACK_H
#define STACK_H

class Stack {
private:
    int* data;
    int topIndex;
    int capacity;

    void resize();

public:
    Stack();
    ~Stack();

    void push(int value);
    int pop();
    int top() const;
    bool isEmpty() const;
    int size() const;
};

#endif // STACK_H
