#include "Stack.h"
#include <stdexcept>

template <typename T>
Stack<T>::Stack() : topNode(nullptr), stackSize(0) {}

template <typename T>
Stack<T>::~Stack() {
    clear();
}

template <typename T>
void Stack<T>::push(const T& value) {
    StackNode<T>* newNode = new StackNode<T>(value);
    newNode->next = topNode;
    topNode = newNode;
    ++stackSize;
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty. Cannot pop.");
    }
    StackNode<T>* temp = topNode;
    T poppedValue = temp->data;
    topNode = topNode->next;
    delete temp;
    --stackSize;
    return poppedValue;
}

template <typename T>
T Stack<T>::peek() const {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty. Cannot peek.");
    }
    return topNode->data;
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return topNode == nullptr;
}

template <typename T>
size_t Stack<T>::size() const {
    return stackSize;
}

template <typename T>
void Stack<T>::clear() {
    while (!isEmpty()) {
        pop();
    }
}

template class Stack<int>;

