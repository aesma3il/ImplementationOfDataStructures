#include <iostream>
#include <stdexcept> // for std::runtime_error

// Node structure for the linked list
template <typename T>
struct Node {
    T data;           // Data stored in the node
    Node* next;      // Pointer to the next node
    Node* prev;      // Pointer to the previous node

    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

// Generic Double-Ended Queue (Deque) class
template <typename T>
class Deque {
private:
    Node<T>* frontNode; // Pointer to the front node of the deque
    Node<T>* rearNode;  // Pointer to the rear node of the deque

public:
    // Constructor
    Deque() : frontNode(nullptr), rearNode(nullptr) {}

    // Destructor to clear the deque
    ~Deque() {
        while (!isEmpty()) {
            dequeueFront();
        }
    }

    // Add an element to the front of the deque
    void enqueueFront(const T& value) {
        Node<T>* newNode = new Node<T>(value); // Create a new node
        if (isEmpty()) {                      // If the deque is empty
            frontNode = rearNode = newNode;  // New node is both front and rear
        }
        else {
            newNode->next = frontNode;        // Link the new node
            frontNode->prev = newNode;        // Update the previous front
            frontNode = newNode;              // Update the front pointer
        }
    }

    // Add an element to the rear of the deque
    void enqueueRear(const T& value) {
        Node<T>* newNode = new Node<T>(value); // Create a new node
        if (isEmpty()) {                      // If the deque is empty
            frontNode = rearNode = newNode;  // New node is both front and rear
        }
        else {
            newNode->prev = rearNode;         // Link the new node
            rearNode->next = newNode;         // Update the next of the previous rear
            rearNode = newNode;                // Update the rear pointer
        }
    }

    // Remove an element from the front of the deque
    void dequeueFront() {
        if (isEmpty()) {
            throw std::runtime_error("Deque is empty. Cannot dequeue from front.");
        }
        Node<T>* temp = frontNode;           // Store the current front node
        frontNode = frontNode->next;         // Move front to the next node
        if (frontNode) {                     // If the deque is not empty after dequeue
            frontNode->prev = nullptr;       // Update previous pointer of new front
        }
        else {
            rearNode = nullptr;               // If the deque becomes empty
        }
        delete temp;                        // Free the old front node
    }

    // Remove an element from the rear of the deque
    void dequeueRear() {
        if (isEmpty()) {
            throw std::runtime_error("Deque is empty. Cannot dequeue from rear.");
        }
        Node<T>* temp = rearNode;            // Store the current rear node
        rearNode = rearNode->prev;           // Move rear to the previous node
        if (rearNode) {                      // If the deque is not empty after dequeue
            rearNode->next = nullptr;        // Update next pointer of new rear
        }
        else {
            frontNode = nullptr;              // If the deque becomes empty
        }
        delete temp;                        // Free the old rear node
    }

    // Get the front element of the deque
    T front() const {
        if (isEmpty()) {
            throw std::runtime_error("Deque is empty. Cannot retrieve front element.");
        }
        return frontNode->data; // Return the data of the front node
    }

    // Get the rear element of the deque
    T rear() const {
        if (isEmpty()) {
            throw std::runtime_error("Deque is empty. Cannot retrieve rear element.");
        }
        return rearNode->data; // Return the data of the rear node
    }

    // Check if the deque is empty
    bool isEmpty() const {
        return frontNode == nullptr; // Returns true if deque is empty
    }

    // Print the deque (for demonstration purposes)
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
    Deque<int> intDeque;

    // Enqueuing elements to the front and rear of the deque
    intDeque.enqueueRear(10);
    intDeque.enqueueRear(20);
    intDeque.enqueueFront(5);
    intDeque.enqueueFront(1);

    // Printing the deque
    std::cout << "Deque elements: ";
    intDeque.print(); // Output: 1 5 10 20

    // Accessing the front and rear elements
    std::cout << "Front element: " << intDeque.front() << std::endl; // Output: 1
    std::cout << "Rear element: " << intDeque.rear() << std::endl;   // Output: 20

    // Dequeuing elements from the front and rear
    intDeque.dequeueFront();
    std::cout << "After dequeue from front, deque elements: ";
    intDeque.print(); // Output: 5 10 20

    intDeque.dequeueRear();
    std::cout << "After dequeue from rear, deque elements: ";
    intDeque.print(); // Output: 5 10

    // Check if deque is empty
    std::cout << "Is deque empty? " << (intDeque.isEmpty() ? "Yes" : "No") << std::endl; // Output: No

    // Dequeue remaining elements
    intDeque.dequeueFront();
    intDeque.dequeueFront();
    std::cout << "After dequeuing all elements, is deque empty? " << (intDeque.isEmpty() ? "Yes" : "No") << std::endl; // Output: Yes

    return 0;
}
