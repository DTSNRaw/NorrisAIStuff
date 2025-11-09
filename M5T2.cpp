//Damian Dotson
//CSC134
//11/9/25

#include <iostream>
using namespace std;

// Function prototype declarations
int square(int num);
void printAnswerLine(int num); 

// Main function
int main() {
    cout << "Number\tSquare" << endl;
    cout << "----------------" << endl;

    // Loop from 1 to 10 and print each line
    for (int i = 1; i <= 10; i++) {
        printAnswerLine(i);
    }

    return 0;
}

// Function that returns the square of an integer
int square(int num) {
    return num * num;
}

// Function that prints one line of the output
void printAnswerLine(int num) {
    cout << num << "\t" << square(num) << endl;
}
