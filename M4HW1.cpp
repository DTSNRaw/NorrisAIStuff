#include <iostream>
using namespace std;

int main() {
    int number;   // The number for the times table
    int i = 1;    // Counter for the loop

    // --- Input Validation Loop ---
    cout << "Enter a number from 1 to 12: ";
    cin >> number;

    while (number < 1 || number > 12) {
        cout << "Invalid input. Please enter a number from 1 to 12: ";
        cin >> number;
    }

    // --- Times Table Loop ---
    while (i <= 12) {
        cout << number << " times " << i << " is " << (number * i) << "." << endl;
        i++;
    }

    return 0;
}
