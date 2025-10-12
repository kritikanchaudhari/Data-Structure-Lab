#include <iostream>
#include <string>
using namespace std;

const int SIZE = 5; // Max number of orders

struct Order {
    int orderID;
    string customerName;
    string items;
    string status; // Pending / Processed
};

class CircularQueue {
private:
    Order queue[SIZE];
    int front, rear;
    int count;

public:
    CircularQueue() {
        front = -1;
        rear = -1;
        count = 0;
    }

    bool isFull() {
        return count == SIZE;
    }

    bool isEmpty() {
        return count == 0;
    }

    // Manual insertion for predefined orders (no user input)
    void addInitialOrder(int id, string name, string items) {
        if (isFull()) {
            cout << "Drive-thru queue is full! Cannot add order ID " << id << endl;
            return;
        }

        Order newOrder;
        newOrder.orderID = id;
        newOrder.customerName = name;
        newOrder.items = items;
        newOrder.status = "Pending";

        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % SIZE;
        }

        queue[rear] = newOrder;
        count++;
    }

    // User input for new orders
    void addOrder() {
        if (isFull()) {
            cout << "Drive-thru queue is full! Cannot add more orders.\n";
            return;
        }

        Order newOrder;
        cout << "Enter Order ID: ";
        cin >> newOrder.orderID;
        cin.ignore(); // flush newline
        cout << "Enter Customer Name: ";
        getline(cin, newOrder.customerName);
        cout << "Enter Items (comma separated): ";
        getline(cin, newOrder.items);
        newOrder.status = "Pending";

        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % SIZE;
        }

        queue[rear] = newOrder;
        count++;

        cout << "Order added successfully!\n";
    }

    void processOrder() {
        if (isEmpty()) {
            cout << "No orders to process.\n";
            return;
        }

        cout << "Processing Order ID: " << queue[front].orderID << " for " << queue[front].customerName << endl;
        queue[front].status = "Processed";

        if (front == rear) {
            // Only one order
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }

        count--;
    }

    void displayOrders() {
        if (isEmpty()) {
            cout << "No ongoing orders in the queue.\n";
            return;
        }

        cout << "\n--- Current Orders in Queue ---\n";
        int i = front;
        int num = count;
        while (num--) {
            cout << "Order ID: " << queue[i].orderID << "\n";
            cout << "Customer: " << queue[i].customerName << "\n";
            cout << "Items: " << queue[i].items << "\n";
            cout << "Status: " << queue[i].status << "\n";
            cout << "-------------------------------\n";
            i = (i + 1) % SIZE;
        }
    }
};

int main() {
    CircularQueue cq;

    // Automatically add initial 3 orders (no user input)
    cout << "Loading initial orders...\n";
    cq.addInitialOrder(101, "Rahul Sharma", "Burger, Fries, Drink");
    cq.addInitialOrder(102, "Priya Patel", "Chicken Sandwich, Salad, Drink");
    cq.addInitialOrder(103, "Aarav Gupta", "Pizza, Wings, Drink");

    int choice;
    do {
        cout << "\n====== Drive-Thru Order System ======\n";
        cout << "1. Add New Order\n";
        cout << "2. Process Next Order\n";
        cout << "3. View Ongoing Orders\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
        case 1:
            cq.addOrder();
            break;
        case 2:
            cq.processOrder();
            break;
        case 3:
            cq.displayOrders();
            break;
        case 4:
            cout << "Exiting Drive-Thru System. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
