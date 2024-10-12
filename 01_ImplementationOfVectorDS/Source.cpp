#include <iostream>
#include <stdexcept> // for std::out_of_range

template <typename T>
class MyVector {
private:
    T* data;             // Pointer to the dynamically allocated array
    size_t capacity;     // Maximum number of elements the vector can hold
    size_t size;         // Current number of elements in the vector

    // Function to resize the internal array when capacity is reached
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity]; // Allocate new array

        // Copy old elements to the new array
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }

        delete[] data;      // Free the old array
        data = newData;     // Update the data pointer
        capacity = newCapacity; // Update the capacity
    }

public:
    // Constructor
    MyVector(size_t initialCapacity = 2)
        : size(0), capacity(initialCapacity) {
        data = new T[capacity]; // Allocate initial array
    }

    // Destructor
    ~MyVector() {
        delete[] data; // Free the allocated array
    }

    // Add an element to the end of the vector
    void push_back(const T& value) {
        if (size >= capacity) {
            resize(capacity * 2); // Double the capacity
        }
        data[size++] = value; // Assign value and increment size
    }

    // Access an element at a specific index
    T& at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Const access to an element at a specific index
    const T& at(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Get the current size of the vector
    size_t getSize() const {
        return size;
    }

    // Check if the vector is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Remove the last element from the vector
    void pop_back() {
        if (size == 0) {
            throw std::out_of_range("Vector is empty");
        }
        --size; // Simply decrement size to remove the last element
    }

    // Get the current capacity of the vector
    size_t getCapacity() const {
        return capacity;
    }

    // Clear all elements in the vector
    void clear() {
        size = 0; // Reset size, but do not free the memory
    }

    // Overloaded operator[] for element access
    T& operator[](size_t index) {
        return at(index);
    }

    // Const version of operator[]
    const T& operator[](size_t index) const {
        return at(index);
    }

    // Function to print elements (for demonstration purposes)
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    MyVector<int> vec;

    // Adding elements
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // Accessing elements
    std::cout << "Elements in vector: ";
    vec.print(); // Output: 1 2 3

    std::cout << "Element at index 1: " << vec.at(1) << std::endl; // Output: 2

    // Removing the last element
    vec.pop_back();
    std::cout << "After pop_back: ";
    vec.print(); // Output: 1 2

    // Check size and capacity
    std::cout << "Size: " << vec.getSize() << ", Capacity: " << vec.getCapacity() << std::endl; // Output: Size: 2, Capacity: 2

    // Clear the vector
    vec.clear();
    std::cout << "After clear, is empty: " << vec.isEmpty() << std::endl; // Output: 1 (true)

    return 0;
}
