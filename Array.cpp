#include <iostream>
#include <cstdlib>
#include <ctime> 
using namespace std;

class Array {
private:
    int* arr;
    size_t size;

public:
    Array(size_t n = 10) : size(n) {
        arr = new int[size];
        for (size_t i = 0; i < size; ++i) {
            arr[i] = 0;
        }
    }

    Array(size_t n, bool randomize) : size(n) {
        arr = new int[size];
        if (randomize) {
            srand(static_cast<unsigned>(time(0)));
            for (size_t i = 0; i < size; ++i) {
                arr[i] = rand() % 100;
            }
        }
    }

    Array(size_t n, int min, int max) : size(n) {
        arr = new int[size];
        srand(static_cast<unsigned>(time(0)));
        for (size_t i = 0; i < size; ++i) {
            arr[i] = min + rand() % (max - min + 1);
        }
    }

    Array(const Array& other) : size(other.size) {
        arr = new int[size];
        for (size_t i = 0; i < size; ++i) {
            arr[i] = other.arr[i];
        }
    }

    Array(Array&& other) noexcept : arr(other.arr), size(other.size) {
        other.arr = nullptr;
        other.size = 0;
    }

    ~Array() {
        delete[] arr;
    }

    void display() const {
        for (size_t i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void fillRandom(int min = 0, int max = 100) {
        srand(static_cast<unsigned>(time(0)));
        for (size_t i = 0; i < size; ++i) {
            arr[i] = min + rand() % (max - min + 1);
        }
    }

    void resize(size_t newSize) {
        int* newArr = new int[newSize];
        for (size_t i = 0; i < min(size, newSize); ++i) {
            newArr[i] = arr[i];
        }
        for (size_t i = size; i < newSize; ++i) {
            newArr[i] = 0;
        }
        delete[] arr;
        arr = newArr;
        size = newSize;
    }

    void sort() {
        for (size_t i = 0; i < size - 1; ++i) {
            for (size_t j = 0; j < size - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    int minValue() const {
        int minVal = arr[0];
        for (size_t i = 1; i < size; ++i) {
            if (arr[i] < minVal) {
                minVal = arr[i];
            }
        }
        return minVal;
    }

    int maxValue() const {
        int maxVal = arr[0];
        for (size_t i = 1; i < size; ++i) {
            if (arr[i] > maxVal) {
                maxVal = arr[i];
            }
        }
        return maxVal;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] arr;
            size = other.size;
            arr = new int[size];
            for (size_t i = 0; i < size; ++i) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    Array operator+(const Array& other) const {
        size_t newSize = size + other.size;
        Array result(newSize);
        for (size_t i = 0; i < size; ++i) {
            result.arr[i] = arr[i];
        }
        for (size_t i = 0; i < other.size; ++i) {
            result.arr[size + i] = other.arr[i];
        }
        return result;
    }

    Array& operator+=(const Array& other) {
        size_t newSize = size + other.size;
        int* newArr = new int[newSize];
        for (size_t i = 0; i < size; ++i) {
            newArr[i] = arr[i];
        }
        for (size_t i = 0; i < other.size; ++i) {
            newArr[size + i] = other.arr[i];
        }
        delete[] arr;
        arr = newArr;
        size = newSize;
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] arr;
            arr = other.arr;
            size = other.size;
            other.arr = nullptr;
            other.size = 0;
        }
        return *this;
    }

    int& operator[](size_t index) {
        if (index >= size) throw out_of_range("Index out of range");
        return arr[index];
    }

    const int& operator[](size_t index) const {
        if (index >= size) throw out_of_range("Index out of range");
        return arr[index];
    }

    bool operator==(const Array& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i) {
            if (arr[i] != other.arr[i]) return false;
        }
        return true;
    }

    bool operator!=(const Array& other) const {
        return !(*this == other);
    }

    bool operator>(const Array& other) const {
        return size > other.size;
    }

    bool operator<(const Array& other) const {
        return size < other.size;
    }

    friend ostream& operator<<(ostream& os, const Array& array) {
        for (size_t i = 0; i < array.size; ++i) {
            os << array.arr[i] << " ";
        }
        return os;
    }

    Array operator*(const Array& other) const {
        Array result(0);
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < other.size; ++j) {
                if (arr[i] == other.arr[j]) {
                    result.resize(result.size + 1);
                    result.arr[result.size - 1] = arr[i];
                    break;
                }
            }
        }
        return result;
    }
};