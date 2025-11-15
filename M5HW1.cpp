// m5hw1.cpp
//Damian Dotson
//11/15/25
// CSC 134 - M5HW1
// All questions are functions

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// Helper: read a double, with optional minimum allowed value (inclusive).
double readDouble(const string &prompt, double minAllowed = -numeric_limits<double>::infinity()) {
    double value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (value < minAllowed) {
            if (minAllowed == 0.0)
                cout << "Only enter positive values (zero or greater) as required.\n";
            else
                cout << "Value must be at least " << minAllowed << ". Please try again.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush rest of line
        return value;
    }
}

// Helper: read an integer, with optional min/max inclusive bounds
int readInt(const string &prompt, int minAllowed = numeric_limits<int>::min(), int maxAllowed = numeric_limits<int>::max()) {
    int value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cout << "Invalid input. Please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (value < minAllowed || value > maxAllowed) {
            cout << "Please enter a value between " << minAllowed << " and " << maxAllowed << ".\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
}

// Q1: Average rainfall for three months
void question1() {
    cout << "\n--- Question 1: Average Rainfall ---\n";
    string m1, m2, m3;
    double r1, r2, r3;

    cout << "Enter month: ";
    getline(cin, m1);
    r1 = readDouble("Enter rainfall for " + m1 + ": ");

    cout << "Enter month: ";
    getline(cin, m2);
    r2 = readDouble("Enter rainfall for " + m2 + ": ");

    cout << "Enter month: ";
    getline(cin, m3);
    r3 = readDouble("Enter rainfall for " + m3 + ": ");

    double avg = (r1 + r2 + r3) / 3.0;
    cout << fixed << setprecision(2);
    cout << "The average rainfall for " << m1 << ", " << m2 << ", and " << m3
         << " is " << avg << " inches.\n\n";
    cout << defaultfloat; // restore default
}

// Q2: Volume of block (hyperrectangle)
void question2() {
    cout << "\n--- Question 2: Volume of a Block ---\n";
    // Input validation: no side can be zero or less.
    double width = readDouble("Enter width: ", numeric_limits<double>::min()); // allow any, then check
    while (width <= 0.0) {
        cout << "Width cannot be zero or less. Please enter a positive value.\n";
        width = readDouble("Enter width: ");
    }
    double length = readDouble("Enter length: ");
    while (length <= 0.0) {
        cout << "Length cannot be zero or less. Please enter a positive value.\n";
        length = readDouble("Enter length: ");
    }
    double height = readDouble("Enter height: ");
    while (height <= 0.0) {
        cout << "Height cannot be zero or less. Please enter a positive value.\n";
        height = readDouble("Enter height: ");
    }

    double volume = width * length * height;
    cout << "Volume of the block is: " << volume << "\n\n";
}

// Q3: Convert 1-10 to Roman numerals
void question3() {
    cout << "\n--- Question 3: Roman Numeral (1-10) ---\n";
    int n = readInt("Enter a number (1 - 10): ", 1, 10);

    string roman;
    switch (n) {
        case 1: roman = "I"; break;
        case 2: roman = "II"; break;
        case 3: roman = "III"; break;
        case 4: roman = "IV"; break;
        case 5: roman = "V"; break;
        case 6: roman = "VI"; break;
        case 7: roman = "VII"; break;
        case 8: roman = "VIII"; break;
        case 9: roman = "IX"; break;
        case 10: roman = "X"; break;
        default: roman = "?"; // shouldn't happen due to validation
    }

    cout << "The Roman numeral version of " << n << " is " << roman << ".\n\n";
}

// Q4: Geometry Calculator
void question4() {
    cout << "\n--- Question 4: Geometry Calculator ---\n";
    cout << "Geometry Calculator\n";
    cout << "1. Calculate the Area of a Circle\n";
    cout << "2. Calculate the Area of a Rectangle\n";
    cout << "3. Calculate the Area of a Triangle\n";
    cout << "4. Quit\n";

    int choice = readInt("Enter your choice (1-4): ", 1, 4);

    const double PI = 3.14159;
    switch (choice) {
        case 1: {
            double radius = readDouble("Enter the circle's radius: ");
            if (radius < 0) {
                cout << "The radius cannot be less than zero.\n\n";
                break;
            }
            double area = PI * radius * radius;
            cout << "The area is " << area << "\n\n";
            break;
        }
        case 2: {
            double length = readDouble("Enter the rectangle's length: ");
            if (length < 0) {
                cout << "Only enter positive values for length and width.\n\n";
                break;
            }
            double width = readDouble("Enter the rectangle's width: ");
            if (width < 0) {
                cout << "Only enter positive values for length and width.\n\n";
                break;
            }
            double area = length * width;
            cout << "The area is " << area << "\n\n";
            break;
        }
        case 3: {
            double base = readDouble("Enter the triangle's base: ");
            if (base < 0) {
                cout << "Only enter positive values for base and height.\n\n";
                break;
            }
            double height = readDouble("Enter the triangle's height: ");
            if (height < 0) {
                cout << "Only enter positive values for base and height.\n\n";
                break;
            }
            double area = 0.5 * base * height;
            cout << "The area is " << area << "\n\n";
            break;
        }
        case 4:
            cout << "Quitting Geometry Calculator.\n\n";
            break;
        default:
            // won't happen because of validation
            cout << "The valid choices are 1 through 4. Run the program again and select one of those.\n\n";
    }
}

// Q5: Distance Traveled
void question5() {
    cout << "\n--- Question 5: Distance Traveled ---\n";
    double speed;
    while (true) {
        speed = readDouble("What is the speed of the vehicle in mph? ");
        if (speed < 0.0) {
            cout << "Speed cannot be negative. Please re-enter.\n";
        } else break;
    }

    int hours;
    while (true) {
        hours = readInt("How many hours has it traveled? ");
        if (hours < 1) {
            cout << "Time traveled must be at least 1 hour. Please re-enter.\n";
        } else break;
    }

    cout << "\nHour   Distance Traveled\n";
    cout << "--------------------------------\n";
    for (int h = 1; h <= hours; ++h) {
        double dist = speed * h;
        cout << setw(4) << h << "   " << dist << "\n";
    }
    cout << "\n";
}

// Q6: Menu-based program calls Q1-Q5; exit on 6
void question6_menu() {
    while (true) {
        cout << "=== Main Menu ===\n";
        cout << "1. Average Rainfall (Question 1)\n";
        cout << "2. Volume of Block (Question 2)\n";
        cout << "3. Roman Numeral (Question 3)\n";
        cout << "4. Geometry Calculator (Question 4)\n";
        cout << "5. Distance Traveled (Question 5)\n";
        cout << "6. Exit\n";

        int choice = readInt("Enter your choice (1-6): ", 1, 6);

        switch (choice) {
            case 1: question1(); break;
            case 2: question2(); break;
            case 3: question3(); break;
            case 4: question4(); break;
            case 5: question5(); break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                return;
            default:
                // readInt already validates 1-6
                cout << "The valid choices are 1 through 6. Run the program again and select one of those.\n";
        }
    }
}

int main() {
    // Run the menu for Q6 which lets user call each question (1..5) or exit (6)
    cout << "CSC 134 - Assignment M5HW1 - Combined Program\n";
    question6_menu();
    return 0;
}
