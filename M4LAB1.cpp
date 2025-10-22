#include <iostream>
using namespace std;

int main() {
    int height, width;

    cout << "Enter height: ";
    if (!(cin >> height)) {
        cerr << "Invalid input for height.\n";
        return 1;
    }

    cout << "Enter width: ";
    if (!(cin >> width)) {
        cerr << "Invalid input for width.\n";
        return 1;
    }

    if (height <= 0 || width <= 0) {
        cout << "Height and width must be positive integers.\n";
        return 0;
    }

    // Outer loop: for each row (0 .. height-1)
    for (int i = 0; i < height; ++i) {
        // Inner loop: print width asterisks on the same line
        for (int j = 0; j < width; ++j) {
            cout << "*";
            // print a space between stars but not after the last one
            if (j != width - 1) cout << " ";
        }
        cout << endl; // after finishing the row, move to next line
    }

    return 0;
}
