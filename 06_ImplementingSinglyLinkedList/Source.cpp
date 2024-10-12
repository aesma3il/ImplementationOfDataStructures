#include <iostream>
using namespace std;

// Node structure for linked list
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

// SinglyLinkedList class
template <typename T>
class SinglyLinkedList {
private:
    Node<T>* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    // Insert at the beginning
    void insertAtBeginning(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        cout << "Inserted at beginning: " << value << endl;
    }

    // Insert at the end
    void insertAtEnd(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            cout << "Inserted at end: " << value << endl;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        cout << "Inserted at end: " << value << endl;
    }

    // Delete a node by value
    void deleteNode(T value) {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            cout << "Deleted node with value: " << value << endl;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != nullptr && temp->next->data != value) {
            temp = temp->next;
        }
        if (temp->next == nullptr) {
            cout << "Node with value " << value << " not found!" << endl;
            return;
        }
        Node<T>* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
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

    // Display the linked list
    void display() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        Node<T>* temp = head;
        cout << "Linked List: ";
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    // Destructor to free memory
    ~SinglyLinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Example usage
int main() {
    SinglyLinkedList<int> sll; // Create a singly linked list of integers

    sll.insertAtEnd(10);
    sll.insertAtEnd(20);
    sll.insertAtBeginning(5);
    sll.display();

    sll.deleteNode(20);
    sll.display();

    if (sll.search(10)) {
        cout << "10 found in the list." << endl;
    }
    else {
        cout << "10 not found in the list." << endl;
    }

    if (sll.search(25)) {
        cout << "25 found in the list." << endl;
    }
    else {
        cout << "25 not found in the list." << endl;
    }

    return 0;
}
