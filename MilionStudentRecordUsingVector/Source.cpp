#include <iostream>
#include <stdexcept>  // for std::out_of_range
#include <string>     // for std::string
#include <cstdlib>    // for rand()
#include <iomanip>    // for std::setprecision
using namespace std;
template <typename T>
class MyVector {
private:
    T* data;
    size_t capacity;
    size_t size;

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    MyVector(size_t initialCapacity = 2)
        : size(0), capacity(initialCapacity) {
        data = new T[capacity];
    }

    ~MyVector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size >= capacity) {
            resize(capacity * 2);
        }
        data[size++] = value;
    }

    T& at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void pop_back() {
        if (size == 0) {
            throw std::out_of_range("Vector is empty");
        }
        --size;
    }

    size_t getCapacity() const {
        return capacity;
    }

    void clear() {
        size = 0;
    }

    T& operator[](size_t index) {
        return at(index);
    }

    const T& operator[](size_t index) const {
        return at(index);
    }
};

// Student class
class Student {
public:
    int ID;
    std::string firstName;
    std::string lastName;
    double GPA;


    Student(){}
    // Constructor
    Student(int id, const std::string& fname, const std::string& lname, double gpa)
        : ID(id), firstName(fname), lastName(lname), GPA(gpa) {}

    // Overload the << operator for easy printing
    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "ID: " << student.ID << ", Name: " << student.firstName << " " << student.lastName
            << ", GPA: " << std::fixed << std::setprecision(2) << student.GPA;
        return os;
    }
};

// Function to generate random student records
void generateStudentRecords(MyVector<Student>& vec, int numRecords) {
    const std::string firstNames[] = { "John", "Jane", "Alice", "Bob", "Charlie" };
    const std::string lastNames[] = { "Smith", "Doe", "Johnson", "Brown", "Williams" };

    for (int i = 1; i <= numRecords; ++i) {
        // Generate random first and last names
        std::string firstName = firstNames[rand() % 5];
        std::string lastName = lastNames[rand() % 5];

        // Generate random GPA between 2.0 and 4.0
        double gpa = 2.0 + static_cast<double>(rand()) / (RAND_MAX / 2.0);

        // Create a new Student object and add it to the vector
        vec.push_back(Student(i, firstName, lastName, gpa));
    }
}
// Function to display a specific page of records
void displayPage(const MyVector<Student>& vec, int pageNumber, int pageSize) {
    int startIndex = pageNumber * pageSize;
    int endIndex = std::min(startIndex + pageSize, static_cast<int>(vec.getSize()));

    if (startIndex >= vec.getSize()) {
        std::cout << "Page number out of range!" << std::endl;
        return;
    }

    for (int i = startIndex; i < endIndex; ++i) {
        std::cout << vec[i] << std::endl;
    }

    std::cout << "Showing page " << pageNumber + 1 << " of "
        << (vec.getSize() + pageSize - 1) / pageSize << std::endl;
}
int main() {
    MyVector<Student> studentRecords;

    // Generate 1 million student records (from previous example)
    generateStudentRecords(studentRecords, 1000);

    int pageSize = 100;  // Number of records per page
    int currentPage = 0;
    int sizeOfRecords = studentRecords.getSize() - 1;
    char choice;

   // cout << "Number of pages is " << sizeOfRecords / pageSize << endl;
    do {
        // Display the current page
        displayPage(studentRecords, currentPage, pageSize);

        // Ask user to navigate
        std::cout << "Enter 'n' for next page, 'p' for previous page, 'q' to quit: ";
        std::cin >> choice;
        // check for the last page
        if (choice == 'n' && currentPage < sizeOfRecords / pageSize) {
            ++currentPage;
        }
        else if (choice == 'p' && currentPage > 0) {
            --currentPage;
        }
    } while (choice != 'q');
    return 0;
}
