#include <iostream>
using namespace std;

// Node structure for doubly linked list
template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};

// DoublyLinkedList class
template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;

public:
    DoublyLinkedList() : head(nullptr) {}

    // Insert at the beginning
    void insertAtBeginning(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        cout << "Inserted at beginning: " << value << endl;
    }

    // Insert at the end
    void insertAtEnd(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
        cout << "Inserted at end: " << value << endl;
    }

    // Delete a node by value
    void deleteNode(T value) {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        Node<T>* temp = head;
        while (temp != nullptr && temp->data != value) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Node with value " << value << " not found!" << endl;
            return;
        }

        // Node is found; handle deletion
        if (temp->prev != nullptr) {
            temp->prev->next = temp->next;
        }
        else {
            head = temp->next; // If the node to delete is the head
        }

        if (temp->next != nullptr) {
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout << "Deleted node with value: " << value << endl;
    }

    // Search for a value in the list
    bool search(T value) {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == value) {
                return true; // Value found
            }
            temp = temp->next;
        }
        return false; // Value not found
    }

    // Display the linked list in forward direction
    void displayForward() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        Node<T>* temp = head;
        cout << "Doubly Linked List (Forward): ";
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    // Display the linked list in reverse direction
    void displayBackward() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        Node<T>* temp = head;
        // Move to the last node
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        cout << "Doubly Linked List (Backward): ";
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        cout << "nullptr" << endl;
    }

    // Destructor to free memory
    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Example usage
int main() {
    DoublyLinkedList<int> dll; // Create a doubly linked list of integers

    dll.insertAtEnd(10);
    dll.insertAtEnd(20);
    dll.insertAtBeginning(5);
    dll.displayForward();
    dll.displayBackward();

    dll.deleteNode(20);
    dll.displayForward();
    dll.displayBackward();

    if (dll.search(10)) {
        cout << "10 found in the list." << endl;
    }
    else {
        cout << "10 not found in the list." << endl;
    }

    if (dll.search(25)) {
        cout << "25 found in the list." << endl;
    }
    else {
        cout << "25 not found in the list." << endl;
    }

    return 0;
}
