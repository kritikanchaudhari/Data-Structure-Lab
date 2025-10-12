#include <iostream>
#include <string>

using namespace std;

const int MAX = 100;

struct ServiceRequest {
    int requestID;
    string customerName;
    string serviceType;
};

class RequestQueue {
private:
    ServiceRequest requests[MAX];
    int front;
    int rear;

public:
    RequestQueue() {
        front = 0;
        rear = 0;
    }

    bool isEmpty() {
        return front == rear;
    }

    bool isFull() {
        return rear == MAX;
    }

    void enqueue(ServiceRequest request) {
        if (isFull()) {
            cout << "Queue is full! Cannot add more requests.\n";
            return;
        }
        requests[rear] = request;
        rear++;
        cout << "Request added successfully.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "No requests to process.\n";
            return;
        }
        cout << "\nProcessing Request:\n";
        displayRequest(requests[front]);
        front++;
    }

    void displayAll() {
        if (isEmpty()) {
            cout << "No pending requests.\n";
            return;
        }

        cout << "\nPending Requests:\n";
        for (int i = front; i < rear; i++) {
            displayRequest(requests[i]);
        }
    }

    void displayRequest(ServiceRequest request) {
        cout << "Request ID: " << request.requestID << endl;
        cout << "Customer Name: " << request.customerName << endl;
        cout << "Service Type: " << request.serviceType << endl;
        cout << "-----------------------------" << endl;
    }
};

int main() {
    RequestQueue rq;
    int choice;

    rq.enqueue({101, "John Doe", "Technical Support"});
    rq.enqueue({102, "Jane Smith", "Billing Inquiry"});
    rq.enqueue({103, "David Brown", "Product Information"});

    do {
        cout << "\n--- Call Center Request Management ---\n";
        cout << "1. Add New Request\n";
        cout << "2. Process Next Request\n";
        cout << "3. View All Pending Requests\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                ServiceRequest newReq;
                cout << "Enter Request ID: ";
                cin >> newReq.requestID;
                cin.ignore();
                cout << "Enter Customer Name: ";
                getline(cin, newReq.customerName);
                cout << "Enter Service Type: ";
                getline(cin, newReq.serviceType);
                rq.enqueue(newReq);
                break;
            }

            case 2:
                rq.dequeue();
                break;

            case 3:
                rq.displayAll();
                break;

            case 4:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please enter a number from 1 to 4.\n";
        }

    } while (choice != 4);

    return 0;
}
