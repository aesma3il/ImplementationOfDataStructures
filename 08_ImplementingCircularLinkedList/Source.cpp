#include <iostream>
using namespace std;

// Node structure for circular linked list
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

// CircularLinkedList class
template <typename T>
class CircularLinkedList {
private:
    Node<T>* head;

public:
    CircularLinkedList() : head(nullptr) {}

    // Insert at the beginning
    void insertAtBeginning(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            newNode->next = head; // Point to itself
        }
        else {
            Node<T>* temp = head;
            while (temp->next != head) { // Traverse to the last node
                temp = temp->next;
            }
            temp->next = newNode; // Last node points to new node
            newNode->next = head; // New node points to head
            head = newNode; // Update head
        }
        cout << "Inserted at beginning: " << value << endl;
    }

    // Insert at the end
    void insertAtEnd(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            newNode->next = head; // Point to itself
        }
        else {
            Node<T>* temp = head;
            while (temp->next != head) { // Traverse to the last node
                temp = temp->next;
            }
            temp->next = newNode; // Last node points to new node
            newNode->next = head; // New node points to head
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
        Node<T>* prev = nullptr;

        // Check if head needs to be deleted
        if (head->data == value) {
            if (head->next == head) { // Only one node
                delete head;
                head = nullptr;
            }
            else {
                while (temp->next != head) {
                    temp = temp->next; // Find last node
                }
                temp->next = head->next; // Last node points to second node
                Node<T>* nodeToDelete = head;
                head = head->next; // Update head
                delete nodeToDelete; // Delete old head
            }
            cout << "Deleted node with value: " << value << endl;
            return;
        }

        // Search for the node to delete
        while (temp->next != head && temp->next->data != value) {
            temp = temp->next;
        }

        if (temp->next == head) {
            cout << "Node with value " << value << " not found!" << endl;
            return;
        }

        // Node is found; handle deletion
        Node<T>* nodeToDelete = temp->next;
        temp->next = nodeToDelete->next; // Bypass the node
        delete nodeToDelete; // Delete the node
        cout << "Deleted node with value: " << value << endl;
    }

    // Search for a value in the list
    bool search(T value) {
        if (head == nullptr) return false; // List is empty

        Node<T>* temp = head;
        do {
            if (temp->data == value) {
                return true; // Value found
            }
            temp = temp->next;
        } while (temp != head);

        return false; // Value not found
    }

    // Display the linked list
    void display() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        Node<T>* temp = head;
        cout << "Circular Linked List: ";
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(back to head: " << head->data << ")" << endl;
    }

    // Destructor to free memory
    ~CircularLinkedList() {
        if (head == nullptr) return; // List is empty

        Node<T>* current = head;
        Node<T>* nextNode;
        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head);
        head = nullptr; // Avoid dangling pointer
    }
};

// Example usage
int main() {
    CircularLinkedList<int> cll; // Create a circular linked list of integers

    cll.insertAtEnd(10);
    cll.insertAtEnd(20);
    cll.insertAtBeginning(5);
    cll.display();

    cll.deleteNode(20);
    cll.display();

    if (cll.search(10)) {
        cout << "10 found in the list." << endl;
    }
    else {
        cout << "10 not found in the list." << endl;
    }

    if (cll.search(25)) {
        cout << "25 found in the list." << endl;
    }
    else {
        cout << "25 not found in the list." << endl;
    }

    return 0;
}
