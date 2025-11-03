#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Structure for Contact
struct Contact {
    int id;
    string name;
    string phone;
    string email;
};

// AVL Tree Node
struct Node {
    Contact data;
    Node* left;
    Node* right;
    int height;
    Node(Contact c) : data(c), left(nullptr), right(nullptr), height(1) {}
};

// Get height of node
int getHeight(Node* n) {
    return n ? n->height : 0;
}

// Get balance factor
int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

// Right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

// Left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

// Insert by name (primary key)
Node* insert(Node* root, Contact contact) {
    if (!root)
        return new Node(contact);

    if (contact.name < root->data.name)
        root->left = insert(root->left, contact);
    else if (contact.name > root->data.name)
        root->right = insert(root->right, contact);
    else {
        cout << "Duplicate name not allowed.\n";
        return root;
    }

    // Update height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Balance the node
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && contact.name < root->left->data.name)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && contact.name > root->right->data.name)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && contact.name > root->left->data.name) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && contact.name < root->right->data.name) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search by Name
Node* searchByName(Node* root, string name) {
    if (!root) return nullptr;
    if (name == root->data.name) return root;
    if (name < root->data.name) return searchByName(root->left, name);
    return searchByName(root->right, name);
}

// Search by Phone
Node* searchByPhone(Node* root, string phone) {
    if (!root) return nullptr;
    if (root->data.phone == phone) return root;
    Node* left = searchByPhone(root->left, phone);
    if (left) return left;
    return searchByPhone(root->right, phone);
}

// Search by Email
Node* searchByEmail(Node* root, string email) {
    if (!root) return nullptr;
    if (root->data.email == email) return root;
    Node* left = searchByEmail(root->left, email);
    if (left) return left;
    return searchByEmail(root->right, email);
}

// Update contact
void updateContact(Node* root, string name) {
    Node* contactNode = searchByName(root, name);
    if (!contactNode) {
        cout << "Contact not found.\n";
        return;
    }

    cout << "Updating contact for: " << contactNode->data.name << "\n";
    cout << "Enter new phone number: ";
    cin >> contactNode->data.phone;
    cout << "Enter new email: ";
    cin >> contactNode->data.email;
    cout << "Contact updated successfully!\n";
}

// Inorder traversal (for displaying sorted contacts)
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << "ID: " << root->data.id
         << " | Name: " << root->data.name
         << " | Phone: " << root->data.phone
         << " | Email: " << root->data.email << endl;
    inorder(root->right);
}

int main() {
    Node* root = nullptr;

    // Initial contacts
    Contact c1 = {101, "Rahul Sharma", "9876543210", "rahul@example.com"};
    Contact c2 = {102, "Priya Patel", "1234567890", "priya@example.com"};
    Contact c3 = {103, "Aarav Gupta", "8765432109", "aarav@example.com"};

    root = insert(root, c1);
    root = insert(root, c2);
    root = insert(root, c3);

    int choice;
    do {
        cout << "\n--- Contact Management System (AVL Tree) ---\n";
        cout << "1. Add Contact\n";
        cout << "2. Search by Name\n";
        cout << "3. Search by Phone\n";
        cout << "4. Search by Email\n";
        cout << "5. Update Contact\n";
        cout << "6. Display All Contacts\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Contact newContact;
            cout << "Enter Contact ID: ";
            cin >> newContact.id;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, newContact.name);
            cout << "Enter Phone Number: ";
            cin >> newContact.phone;
            cout << "Enter Email: ";
            cin >> newContact.email;

            root = insert(root, newContact);
            cout << "Contact added successfully!\n";

        } else if (choice == 2) {
            string name;
            cin.ignore();
            cout << "Enter Name to search: ";
            getline(cin, name);
            Node* res = searchByName(root, name);
            if (res)
                cout << "Found: " << res->data.name << " | " << res->data.phone << " | " << res->data.email << endl;
            else
                cout << "Contact not found.\n";

        } else if (choice == 3) {
            string phone;
            cout << "Enter Phone Number: ";
            cin >> phone;
            Node* res = searchByPhone(root, phone);
            if (res)
                cout << "Found: " << res->data.name << " | " << res->data.phone << " | " << res->data.email << endl;
            else
                cout << "Contact not found.\n";

        } else if (choice == 4) {
            string email;
            cout << "Enter Email: ";
            cin >> email;
            Node* res = searchByEmail(root, email);
            if (res)
                cout << "Found: " << res->data.name << " | " << res->data.phone << " | " << res->data.email << endl;
            else
                cout << "Contact not found.\n";

        } else if (choice == 5) {
            string name;
            cin.ignore();
            cout << "Enter Name of contact to update: ";
            getline(cin, name);
            updateContact(root, name);

        } else if (choice == 6) {
            cout << "\n--- All Contacts (Sorted by Name) ---\n";
            inorder(root);
        }

    } while (choice != 0);

    cout << "Exiting Contact Management System.\n";
    return 0;
}

