/*
M5Lab2
11/4/2025
Damian Dotson
*/

#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// Function prototypes
double getLength();
double getWidth();
double getArea(double length, double width);
void displayData(double length, double width, double area);

// Helper prototype (for input validation)
double getDouble(const string &prompt);

int main()
{
    // This program calculates the area of a rectangle.

    double length,    // The rectangle's length
           width,     // The rectangle's width
           area;      // The rectangle's area

    // Get the rectangle's length.
    length = getLength();

    // Get the rectangle's width.
    width = getWidth();

    // Get the rectangle's area.
    area = getArea(length, width);

    // Display the rectangle's data.
    displayData(length, width, area);

    return 0;
}

//*********************************************************
// Reads a double from the user with a prompt and validates
// that the input is numeric. Returns the double value.
//*********************************************************
double getDouble(const string &prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            // valid numeric input
            return value;
        } else {
            // invalid input: clear and discard
            cout << "Invalid input. Please enter a numeric value." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Asks the user to enter a rectangle's length, and returns it.
double getLength() {
    // If you want to enforce positive lengths, you can loop until > 0.
    double len = getDouble("Enter the rectangle's length: ");
    return len;
}

// Asks the user to enter a rectangle's width, and returns it.
double getWidth() {
    double w = getDouble("Enter the rectangle's width: ");
    return w;
}

// Calculates area from length and width and returns it.
double getArea(double length, double width) {
    return length * width;
}

// Displays length, width, and area in a nicely formatted way.
void displayData(double length, double width, double area) {
    cout << fixed << setprecision(2) << endl;
    cout << "Rectangle Data" << endl;
    cout << "--------------" << endl;
    cout << left << setw(12) << "Length:" << right << setw(8) << length << endl;
    cout << left << setw(12) << "Width:"  << right << setw(8) << width  << endl;
    cout << left << setw(12) << "Area:"   << right << setw(8) << area   << endl;
    cout << endl;
}
