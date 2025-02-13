#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <exception>

class ArrayException : public std::exception {
private:
    std::string message;

public:
    explicit ArrayException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

template<typename T>
class Array {
private:
    T* arr;
    size_t size;
    size_t capacity;

    void reallocate(size_t newCapacity) {
        T* newArr = new (std::nothrow) T[newCapacity];
        if (!newArr) {
            throw ArrayException("Memory allocation failed during reallocation.");
        }
        for (size_t i = 0; i < size; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }

public:
    Array(size_t initialCapacity = 10) : size(0), capacity(initialCapacity) {
        arr = new (std::nothrow) T[capacity];
        if (!arr) {
            throw ArrayException("Memory allocation failed during initialization.");
        }
    }

    Array(size_t n, bool randomize) : size(n), capacity(n) {
        arr = new (std::nothrow) T[capacity];
        if (!arr) {
            throw ArrayException("Memory allocation failed during initialization.");
        }
        if (randomize) {
            srand(static_cast<unsigned>(time(0)));
            for (size_t i = 0; i < size; ++i) {
                arr[i] = rand() % 100;
            }
        }
    }

    Array(size_t n, T min, T max) : size(n), capacity(n) {
        if (min > max) {
            throw ArrayException("Invalid range: min is greater than max.");
        }
        arr = new (std::nothrow) T[capacity];
        if (!arr) {
            throw ArrayException("Memory allocation failed during initialization.");
        }
        srand(static_cast<unsigned>(time(0)));
        for (size_t i = 0; i < size; ++i) {
            arr[i] = min + rand() % (max - min + 1);
        }
    }

    Array(const Array& other) : size(other.size), capacity(other.capacity) {
        arr = new (std::nothrow) T[capacity];
        if (!arr) {
            throw ArrayException("Memory allocation failed during copy.");
        }
        for (size_t i = 0; i < size; ++i) {
            arr[i] = other.arr[i];
        }
    }

    Array(Array&& other) noexcept : arr(other.arr), size(other.size), capacity(other.capacity) {
        other.arr = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    ~Array() {
        delete[] arr;
    }

    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }

    void append(const T& value) {
        if (size >= capacity) {
            reallocate(capacity * 2);
        }
        arr[size++] = value;
    }

    void erase(size_t index) {
        if (size == 0) {
            throw ArrayException("Cannot erase from an empty array.");
        }
        if (index >= size) {
            throw ArrayException("Index out of range.");
        }
        for (size_t i = index; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        --size;
    }

    void clear() {
        size = 0;
    }

    void reserve(size_t newCapacity) {
        if (newCapacity > capacity) {
            reallocate(newCapacity);
        }
    }

    void shrink() {
        if (size < capacity) {
            reallocate(size);
        }
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw ArrayException("Index out of range.");
        }
        return arr[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw ArrayException("Index out of range.");
        }
        return arr[index];
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] arr;
            size = other.size;
            capacity = other.capacity;
            arr = new (std::nothrow) T[capacity];
            if (!arr) {
                throw ArrayException("Memory allocation failed during assignment.");
            }
            for (size_t i = 0; i < size; ++i) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] arr;
            arr = other.arr;
            size = other.size;
            capacity = other.capacity;
            other.arr = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    void display() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

#endif
