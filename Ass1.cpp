#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;

    cout << "How many contacts do you want to add to the phone book? ";
    cin >> n;

    string names[n];
    string phone_numbers[n];
    string cities[n];

    cout << "Enter the contacts:\n";
    for (int i = 0; i < n; i++) {
        cout << "Enter name for contact " << (i+1) << ": ";
        cin >> names[i];
        cout << "Enter phone number for " << names[i] << ": ";
        cin >> phone_numbers[i];
        cout << "Enter city for " << names[i] << ": ";
        cin >> cities[i];
    }

    string phone_to_find;
    cout << "Enter the phone number of the contact you want to search for: ";
    cin >> phone_to_find;

    bool found = false;
    for (int i = 0; i < n; i++) {
        if (phone_numbers[i] == phone_to_find) {
            cout << "Contact found: " << names[i] << " - " << phone_numbers[i] << " - " << cities[i] << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Contact not found!" << endl;
    }

    return 0;
}
