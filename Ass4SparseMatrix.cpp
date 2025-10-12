#include <iostream>
using namespace std;

int main() {
    int marks[3][3];
    cout << "Enter the marks of 3 students in 3 subjects: " << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "Student " << i + 1 << ", Subject " << j + 1 << ": ";
            cin >> marks[i][j];
        }
    }

    cout << "The marks of the students are: " << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << marks[i][j] << " ";
        }
        cout << endl;
    }

    int r[25], c[25], val[25];
    int cnt = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (marks[i][j] != 0) {
                r[cnt] = i;
                c[cnt] = j;
                val[cnt] = marks[i][j];
                cnt++;
            }
        }
    }

    cout << "The sparse matrix representation is: " << endl;
    cout << "Row\tColumn\tValue" << endl;
    for (int i = 0; i < cnt; i++) {
        cout << r[i] << "\t" << c[i] << "\t" << val[i] << endl;
    }

    double avg[3];
    for (int i = 0; i < 3; i++) {
        int sum = 0;
        int subjectsTaken = 0;
        for (int j = 0; j < 3; j++) {
            if (marks[i][j] != 0) {
                sum += marks[i][j];
                subjectsTaken++;
            }
        }
        if (subjectsTaken > 0)
            avg[i] = sum / (double)subjectsTaken;
        else
            avg[i] = 0;

        cout << "Student " << i + 1 << " average: " << avg[i] << endl;
    }

    cout << "Highest marks in each subject: " << endl;
    for (int j = 0; j < 3; j++) {
        int maxm = marks[0][j];
        for (int i = 1; i < 3; i++) {
            if (marks[i][j] > maxm) {
                maxm = marks[i][j];
            }
        }
        cout << "Subject " << j + 1 << ": " << maxm << endl;
    }

    return 0;
}
