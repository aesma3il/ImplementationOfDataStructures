#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> heap;

    // Helper functions to get parent and child indices
    int parent(int index) { return (index - 1) / 2; }
    int leftChild(int index) { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }

    // Helper function to maintain heap property by moving up
    void heapifyUp(int index) {
        if (index && heap[parent(index)] > heap[index]) {
            std::swap(heap[parent(index)], heap[index]);
            heapifyUp(parent(index));
        }
    }

    // Helper function to maintain heap property by moving down
    void heapifyDown(int index) {
        int smallest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < heap.size() && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < heap.size() && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // Constructor
    PriorityQueue() {}

    // Insert an element into the priority queue
    void insert(T value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Remove and return the highest priority element
    T remove() {
        if (heap.empty()) {
            throw std::underflow_error("Priority Queue is empty");
        }
        T root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
        return root;
    }

    // Peek at the highest priority element
    T peek() const {
        if (heap.empty()) {
            throw std::underflow_error("Priority Queue is empty");
        }
        return heap[0];
    }

    // Check if the priority queue is empty
    bool isEmpty() const {
        return heap.empty();
    }

    // Get the size of the priority queue
    size_t size() const {
        return heap.size();
    }
};

// Example usage
int main() {
    PriorityQueue<int> pq;

    pq.insert(30);
    pq.insert(20);
    pq.insert(50);
    pq.insert(10);

    std::cout << "Highest priority element: " << pq.peek() << std::endl; // Should print 10

    std::cout << "Removing elements from the priority queue:" << std::endl;
    while (!pq.isEmpty()) {
        std::cout << pq.remove() << " "; // Should print elements in priority order
    }
    std::cout << std::endl;

    return 0;
}
