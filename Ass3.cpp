#include <iostream>
using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string condition;
    Patient* next;
};

Patient* createPatient(int id, string name, int age, string condition) {
    Patient* newPatient = new Patient();
    newPatient->id = id;
    newPatient->name = name;
    newPatient->age = age;
    newPatient->condition = condition;
    newPatient->next = nullptr;
    return newPatient;
}

Patient* addPatient(Patient* head) {
    int id, age;
    string name, condition;
    cout << "Enter patient id: ";
    cin >> id;
    cout << "Enter patient name: ";
    cin >> name;
    cout << "Enter patient age: ";
    cin >> age;
    cout << "Enter patient condition: ";
    cin >> condition;
   
    Patient* newPatient = createPatient(id, name, age, condition);
    if (!head) return newPatient;
    Patient* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newPatient;
    return head;
}

Patient* removePatient(Patient* head) {
    if (!head) {
        cout << "No patients in the queue.\n";
        return nullptr;
    }
    Patient* temp = head;
    head = head->next;
    delete temp;
    cout << "Patient removed from the queue.\n";
    return head;
}

void display(Patient* head) {
    if (!head) {
        cout << "No patients in the queue.\n";
        return;
    }
    Patient* temp = head;
    cout << "Current patient queue:\n";
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Name: " << temp->name << ", Age: " << temp->age
             << ", Condition: " << temp->condition << endl;
        temp = temp->next;
    }
}

Patient* searchPatient(Patient* head, int id) {
    Patient* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            cout << "Patient found: ID: " << temp->id << ", Name: " << temp->name << ", Age: "
                 << temp->age << ", Condition: " << temp->condition << endl;
            return temp;
        }
        temp = temp->next;
    }
    cout << "Patient with ID " << id << " not found.\n";
    return nullptr;
}

Patient* movePatientUp(Patient* head, int id) {
    if (!head || head->id == id) {
        cout << "The patient is already at the front or no patients in the queue.\n";
        return head;
    }
    Patient* temp = head;
    Patient* prev = nullptr;
    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        cout << "Patient not found.\n";
        return head;
    }
    prev->next = temp->next;
    temp->next = head;
    head = temp;
    cout << "Patient moved up in the queue.\n";
    return head;
}

Patient* updatePatient(Patient* head) {
    if (!head) {
        cout << "No patients in the queue.\n";
        return head;
    }

    int id;
    cout << "Enter patient ID to update: ";
    cin >> id;

    Patient* temp = head;
    while (temp) {
        if (temp->id == id) {
            int updateChoice;
            do {
                cout << "\nCurrent Patient Details:\n";
                cout << "ID: " << temp->id << ", Name: " << temp->name 
                     << ", Age: " << temp->age << ", Condition: " << temp->condition << "\n";

                cout << "Select what you want to update:\n";
                cout << "1. Update Name\n";
                cout << "2. Update Age\n";
                cout << "3. Update Condition\n";
                cout << "4. Exit Update Menu\n";
                cout << "Enter your choice: ";
                cin >> updateChoice;

                switch (updateChoice) {
                    case 1: {
                        cout << "Enter new name: ";
                        cin >> temp->name;
                        cout << "Name updated successfully.\n";
                        break;
                    }
                    case 2: {
                        cout << "Enter new age: ";
                        cin >> temp->age;
                        cout << "Age updated successfully.\n";
                        break;
                    }
                    case 3: {
                        cout << "Enter new condition: ";
                        cin >> temp->condition;
                        cout << "Condition updated successfully.\n";
                        break;
                    }
                    case 4:
                        cout << "Exiting update menu.\n";
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                }
            } while (updateChoice != 4);
            return head;
        }
        temp = temp->next;
    }

    cout << "Patient with ID " << id << " not found.\n";
    return head;
}

int main() {
    Patient* head = nullptr;
    int choice;
   
    do {
        cout << "\nEnter a choice from the following:\n"
             << "1. Add a new patient\n"
             << "2. Remove a patient\n"
             << "3. Display patient queue\n"
             << "4. Search for a patient\n"
             << "5. Move a patient up in the queue\n"
             << "6. Update patient information\n"
             << "7. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                head = addPatient(head);
                break;
            case 2:
                head = removePatient(head);
                break;
            case 3:
                display(head);
                break;
            case 4: {
                int id;
                cout << "Enter patient ID to search: ";
                cin >> id;
                searchPatient(head, id);
                break;
            }
            case 5: {
                int id;
                cout << "Enter patient ID to move up: ";
                cin >> id;
                head = movePatientUp(head, id);
                break;
            }
            case 6:{
                head = updatePatient(head);
                break;
            }
            case 7:{
                cout << "Exiting program.\n";
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 7);

    while (head) {
        Patient* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
