#include <iostream>
using namespace std;

// Node structure for linked list
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

// CircularQueue class
template <typename T>
class CircularQueue {
private:
    Node<T>* front;
    Node<T>* rear;

public:
    CircularQueue() : front(nullptr), rear(nullptr) {}

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // Check if the queue is full (for linked list, we assume it's never full)
    bool isFull() {
        return false; // A linked list implementation is never full
    }

    // Enqueue operation
    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            front = rear = newNode;
            rear->next = front; // Point rear to front to make it circular
        }
        else {
            rear->next = newNode;
            rear = newNode;
            rear->next = front; // Maintain the circular property
        }
        cout << "Enqueued: " << value << endl;
    }

    // Dequeue operation
    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty!");
        }
        Node<T>* temp = front;
        T value = front->data;

        if (front == rear) {
            front = rear = nullptr; // Queue becomes empty
        }
        else {
            front = front->next;
            rear->next = front; // Maintain the circular property
        }
        delete temp; // Free the memory
        cout << "Dequeued: " << value << endl;
        return value;
    }

    // Display the queue
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node<T>* temp = front;
        cout << "Circular Queue: ";
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != front);
        cout << endl;
    }

    // Destructor to free memory
    ~CircularQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

// Example usage
int main() {
    CircularQueue<int> cq; // Create a circular queue of integers

    cq.enqueue(10);
    cq.enqueue(20);
    cq.enqueue(30);

    cq.display();

    cq.dequeue();
    cq.display();

    cq.enqueue(40);
    cq.display();

    return 0;
}
