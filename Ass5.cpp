#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

struct Product {
    int id;
    string name;
    int qty;
    float price;
    Product* related;
};

Product* inv[MAX];
int count = 0;

void addProd() {
    if (count >= MAX) {
        cout << "Inventory is full!\n";
        return;
    }

    Product* p = new Product;

    cout << "Enter Product ID: ";
    cin >> p->id;
    cin.ignore();
    cout << "Enter Product Name: ";
    getline(cin, p->name);
    cout << "Enter Quantity: ";
    cin >> p->qty;
    cout << "Enter Price: ";
    cin >> p->price;

    p->related = nullptr;
    inv[count++] = p;

    cout << "Product added.\n";
}

void updateQty() {
    int id, newQty;
    cout << "Enter Product ID to update: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (inv[i]->id == id) {
            cout << "Enter new quantity: ";
            cin >> newQty;
            inv[i]->qty = newQty;
            cout << "Quantity updated.\n";
            return;
        }
    }
    cout << "Product not found.\n";
}

void linkProd() {
    int id1, id2;
    cout << "Enter ID of first product: ";
    cin >> id1;
    cout << "Enter ID of related product: ";
    cin >> id2;

    Product* p1 = nullptr;
    Product* p2 = nullptr;

    for (int i = 0; i < count; i++) {
        if (inv[i]->id == id1) p1 = inv[i];
        if (inv[i]->id == id2) p2 = inv[i];
    }

    if (p1 && p2) {
        p1->related = p2;
        cout << "Products linked.\n";
    } else {
        cout << "One or both products not found.\n";
    }
}

void showInv() {
    cout << "\n--- Inventory ---\n";
    for (int i = 0; i < count; i++) {
        Product* p = inv[i];
        cout << "ID: " << p->id
             << " | Name: " << p->name
             << " | Qty: " << p->qty
             << " | Price: $" << p->price;

        if (p->related) {
            cout << " | Related: " << p->related->name << " (ID: " << p->related->id << ")";
        }
        cout << endl;
    }
}

void totalValue() {
    float total = 0;
    for (int i = 0; i < count; i++) {
        total += inv[i]->qty * inv[i]->price;
    }
    cout << "Total Inventory Value: $" << total << endl;
}

void cleanup() {
    for (int i = 0; i < count; i++) {
        delete inv[i];
    }
}

int main() {
    int choice;

    do {
        cout << "\n--- Inventory Menu ---\n";
        cout << "1. Add Product\n";
        cout << "2. Update Quantity\n";
        cout << "3. Link Related Products\n";
        cout << "4. Show Inventory\n";
        cout << "5. Total Inventory Value\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProd(); break;
            case 2: updateQty(); break;
            case 3: linkProd(); break;
            case 4: showInv(); break;
            case 5: totalValue(); break;
            case 6: cleanup(); cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}
