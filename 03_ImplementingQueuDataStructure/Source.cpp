#include <iostream>
#include <stdexcept> // for std::runtime_error

// Node structure for the linked list
template <typename T>
struct Node {
    T data;           // Data stored in the node
    Node* next;      // Pointer to the next node

    Node(const T& value) : data(value), next(nullptr) {}
};

// Generic Queue class
template <typename T>
class Queue {
private:
    Node<T>* frontNode; // Pointer to the front node of the queue
    Node<T>* rearNode;  // Pointer to the rear node of the queue

public:
    // Constructor
    Queue() : frontNode(nullptr), rearNode(nullptr) {}

    // Destructor to clear the queue
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Enqueue an element to the rear of the queue
    void enqueue(const T& value) {
        Node<T>* newNode = new Node<T>(value); // Create a new node
        if (rearNode) {                        // If the queue is not empty
            rearNode->next = newNode;          // Link the new node
        }
        else {
            frontNode = newNode;                // If queue was empty, new node is also front
        }
        rearNode = newNode;                     // Update the rear to the new node
    }

    // Dequeue an element from the front of the queue
    void dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty. Cannot dequeue.");
        }
        Node<T>* temp = frontNode;            // Store the current front node
        frontNode = frontNode->next;           // Move front to the next node
        if (!frontNode) {                      // If the queue becomes empty
            rearNode = nullptr;                // Update rear to nullptr
        }
        delete temp;                          // Free the old front node
    }

    // Get the front element of the queue
    T front() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty. Cannot retrieve front element.");
        }
        return frontNode->data; // Return the data of the front node
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return frontNode == nullptr; // Returns true if queue is empty
    }

    // Print the queue (for demonstration purposes)
    void print() const {
        Node<T>* current = frontNode; // Start from the front node
        while (current) {
            std::cout << current->data << " ";
            current = current->next; // Move to the next node
        }
        std::cout << std::endl;
    }
};

int main() {
    Queue<int> intQueue;

    // Enqueuing elements into the queue
    intQueue.enqueue(10);
    intQueue.enqueue(20);
    intQueue.enqueue(30);

    // Printing the queue
    std::cout << "Queue elements: ";
    intQueue.print(); // Output: 10 20 30

    // Accessing the front element
    std::cout << "Front element: " << intQueue.front() << std::endl; // Output: 10

    // Dequeuing an element
    intQueue.dequeue();
    std::cout << "After dequeue, queue elements: ";
    intQueue.print(); // Output: 20 30

    // Check if queue is empty
    std::cout << "Is queue empty? " << (intQueue.isEmpty() ? "Yes" : "No") << std::endl; // Output: No

    // Dequeue remaining elements
    intQueue.dequeue();
    intQueue.dequeue();
    std::cout << "After dequeuing all elements, is queue empty? " << (intQueue.isEmpty() ? "Yes" : "No") << std::endl; // Output: Yes

    return 0;
}
