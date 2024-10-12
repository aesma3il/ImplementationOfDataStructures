#include <iostream>
#include <stdexcept> // for std::runtime_error

// Node structure for the linked list
template <typename T>
struct Node {
    T data;           // Data stored in the node
    Node* next;      // Pointer to the next node

    Node(const T& value) : data(value), next(nullptr) {}
};

// Generic Stack class
template <typename T>
class Stack {
private:
    Node<T>* topNode; // Pointer to the top node of the stack

public:
    // Constructor
    Stack() : topNode(nullptr) {}

    // Destructor to clear the stack
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Push a new element onto the stack
    void push(const T& value) {
        Node<T>* newNode = new Node<T>(value); // Create a new node
        newNode->next = topNode;               // Point it to the current top
        topNode = newNode;                     // Update the top to the new node
    }

    // Remove the top element from the stack
    void pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty. Cannot pop.");
        }
        Node<T>* temp = topNode;  // Store the current top node
        topNode = topNode->next;   // Move top to the next node
        delete temp;               // Free the old top node
    }

    // Get the top element of the stack
    T top() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty. Cannot retrieve top element.");
        }
        return topNode->data; // Return the data of the top node
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return topNode == nullptr; // Returns true if stack is empty
    }

    // Print the stack (for demonstration purposes)
    void print() const {
        Node<T>* current = topNode; // Start from the top node
        while (current) {
            std::cout << current->data << " ";
            current = current->next; // Move to the next node
        }
        std::cout << std::endl;
    }
};

int main() {
    Stack<int> intStack;

    // Pushing elements onto the stack
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    // Printing the stack
    std::cout << "Stack elements: ";
    intStack.print(); // Output: 30 20 10

    // Accessing the top element
    std::cout << "Top element: " << intStack.top() << std::endl; // Output: 30

    // Popping an element
    intStack.pop();
    std::cout << "After pop, stack elements: ";
    intStack.print(); // Output: 20 10

    // Check if stack is empty
    std::cout << "Is stack empty? " << (intStack.isEmpty() ? "Yes" : "No") << std::endl; // Output: No

    // Popping remaining elements
    intStack.pop();
    intStack.pop();
    std::cout << "After popping all elements, is stack empty? " << (intStack.isEmpty() ? "Yes" : "No") << std::endl; // Output: Yes

    return 0;
}
