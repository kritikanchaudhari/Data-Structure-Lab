#include <iostream>
#include <string>
using namespace std;

// Structure for student record
struct Student {
    int id;
    string name;
    int age;
    string course;
};

// Node for linked list (used in separate chaining)
struct Node {
    Student data;
    Node* next;
    Node(Student s) : data(s), next(nullptr) {}
};

// Hash Table class
class HashTable {
private:
    static const int TABLE_SIZE = 10;  // fixed hash table size
    Node* table[TABLE_SIZE];

    // Simple hash function
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = nullptr;
    }

    // Insert new student
    void insert(Student s) {
        int index = hashFunction(s.id);
        Node* newNode = new Node(s);

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node* temp = table[index];
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = newNode;
        }
        cout << "Student added successfully!\n";
    }

    // Search student by ID
    void search(int id) {
        int index = hashFunction(id);
        Node* temp = table[index];

        while (temp != nullptr) {
            if (temp->data.id == id) {
                cout << "\n--- Student Found ---\n";
                cout << "ID: " << temp->data.id << endl;
                cout << "Name: " << temp->data.name << endl;
                cout << "Age: " << temp->data.age << endl;
                cout << "Course: " << temp->data.course << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Student ID not found.\n";
    }

    // Delete student record
    void remove(int id) {
        int index = hashFunction(id);
        Node* temp = table[index];
        Node* prev = nullptr;

        while (temp != nullptr && temp->data.id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Student not found.\n";
            return;
        }

        if (prev == nullptr)  // deleting first node
            table[index] = temp->next;
        else
            prev->next = temp->next;

        delete temp;
        cout << "Student record deleted successfully.\n";
    }

    // Display all student records
    void displayAll() {
        cout << "\n--- All Student Records ---\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* temp = table[i];
            if (temp != nullptr) {
                cout << "Index " << i << ":\n";
                while (temp != nullptr) {
                    cout << "  ID: " << temp->data.id
                         << " | Name: " << temp->data.name
                         << " | Age: " << temp->data.age
                         << " | Course: " << temp->data.course << endl;
                    temp = temp->next;
                }
            }
        }
    }
};

// Main program
int main() {
    HashTable ht;
    int choice;

    do {
        cout << "\n====== Student Information System (Hashing) ======\n";
        cout << "1. Add New Student\n";
        cout << "2. Search Student by ID\n";
        cout << "3. Delete Student Record\n";
        cout << "4. Display All Students\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Student s;
            cout << "Enter Student ID: ";
            cin >> s.id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, s.name);
            cout << "Enter Age: ";
            cin >> s.age;
            cin.ignore();
            cout << "Enter Course: ";
            getline(cin, s.course);
            ht.insert(s);

        } else if (choice == 2) {
            int id;
            cout << "Enter Student ID to search: ";
            cin >> id;
            ht.search(id);

        } else if (choice == 3) {
            int id;
            cout << "Enter Student ID to delete: ";
            cin >> id;
            ht.remove(id);

        } else if (choice == 4) {
            ht.displayAll();
        }

    } while (choice != 0);

    cout << "Exiting Student Information System.\n";
    return 0;
}
