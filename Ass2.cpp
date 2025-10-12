#include <iostream>
using namespace std;

void bubbleSort(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of temperature readings: ";
    cin >> n;

    float temps[n]; 

    cout << "Enter the temperature readings:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> temps[i];
    }

    bubbleSort(temps, n);

    cout << "Sorted temperatures:" << endl;
    for (int i = 0; i < n; i++) {
        cout << temps[i] << " ";
    }
    cout << endl;

    return 0;
}
