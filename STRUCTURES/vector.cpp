#include "Vector.h"

template <typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
Vector<T>::Vector(size_t size) : data_(new T[size]), size_(size), capacity_(size) {}

template <typename T>
Vector<T>::Vector(const Vector& other) : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data_;
        data_ = new T[other.capacity_];
        size_ = other.size_;
        capacity_ = other.capacity_;
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data_;
}

template <typename T>
void Vector<T>::resize(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    size_t elements_to_copy = (size_ < new_capacity) ? size_ : new_capacity;
    for (size_t i = 0; i < elements_to_copy; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
    if (size_ > capacity_) {
        size_ = capacity_;
    }
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        resize(new_capacity);
    }
    data_[size_++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size_ == 0) {
        throw std::underflow_error("Vector is empty. Cannot pop_back.");
    }
    --size_;
}

template <typename T>
T& Vector<T>::at(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    return data_[index];
}

template <typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    return data_[index];
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    return data_[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    return data_[index];
}

template <typename T>
T& Vector<T>::front() {
    if (size_ == 0) {
        throw std::underflow_error("Vector is empty. No front element.");
    }
    return data_[0];
}

template <typename T>
const T& Vector<T>::front() const {
    if (size_ == 0) {
        throw std::underflow_error("Vector is empty. No front element.");
    }
    return data_[0];
}

template <typename T>
T& Vector<T>::back() {
    if (size_ == 0) {
        throw std::underflow_error("Vector is empty. No back element.");
    }
    return data_[size_ - 1];
}

template <typename T>
const T& Vector<T>::back() const {
    if (size_ == 0) {
        throw std::underflow_error("Vector is empty. No back element.");
    }
    return data_[size_ - 1];
}

template <typename T>
size_t Vector<T>::size() const {
    return size_;
}

template <typename T>
size_t Vector<T>::capacity() const {
    return capacity_;
}

template <typename T>
bool Vector<T>::empty() const {
    return size_ == 0;
}

template <typename T>
void Vector<T>::clear() {
    size_ = 0;
}

template <typename T>
void Vector<T>::reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        resize(new_capacity);
    }
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (capacity_ > size_) {
        resize(size_);
    }
}

// Explicit template instantiation for int type
template class Vector<int>;

