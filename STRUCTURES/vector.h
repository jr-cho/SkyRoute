#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void resize(size_t new_capacity);

public:
    Vector();
    explicit Vector(size_t size);
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    ~Vector();

    void push_back(const T& value);
    void pop_back();
    T& at(size_t index);
    const T& at(size_t index) const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    void clear();
    void reserve(size_t new_capacity);
    void shrink_to_fit();
};

#endif // VECTOR_H

