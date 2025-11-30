/*
CSC 134
M6T1 - Loops and Arrays (cars, Monday-Friday)
Author: adapted for user
Date: 11/10/25 (example)
*/

#include <iostream>
#include <iomanip>   // setprecision
#include <string>
#include <cmath>     // round

using namespace std;

// Function declarations
void part1_no_array();
void part2_with_array();

int main() {
    cout << "=== Part 1: No arrays (while loop) ===\n";
    part1_no_array();

    cout << "\n=== Part 2: With arrays (for loop) ===\n";
    part2_with_array();

    return 0;
}

// Part 1: while loop, no arrays
void part1_no_array() {
    const int SIZE = 5;
    int count = 0;
    int cars_today = 0;
    int total = 0;
    double average = 0.0;

    cout << "Enter the number of cars that passed the site each day.\n";
    cout << "(Days: 0 = Monday, 4 = Friday)\n";

    while (count < SIZE) {
        cout << "Day " << count << " (";
        switch(count) {
            case 0: cout << "Monday"; break;
            case 1: cout << "Tuesday"; break;
            case 2: cout << "Wednesday"; break;
            case 3: cout << "Thursday"; break;
            case 4: cout << "Friday"; break;
        }
        cout << "): ";
        cin >> cars_today;

        // simple input guard (non-negative)
        if (cars_today < 0) {
            cout << "Negative values are not allowed. Please enter 0 or a positive integer.\n";
            continue; // re-prompt same day
        }

        total += cars_today;
        count++;
    }

    average = static_cast<double>(total) / SIZE;
    cout << "Total cars = " << total << endl;
    cout << fixed << setprecision(2);
    cout << "Average per day = " << average << endl;
}

// Part 2: for loop, store daily values in an array, print table + ASCII bar chart
void part2_with_array() {
    const int SIZE = 5;
    string days[SIZE] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    int cars[SIZE] = {0};
    int total = 0;
    double average = 0.0;

    // Input using a for loop
    for (int i = 0; i < SIZE; ++i) {
        int value;
        cout << "Number of cars on " << days[i] << ": ";
        cin >> value;
        if (value < 0) {
            cout << "Negative values not allowed. Setting this day's count to 0.\n";
            value = 0;
        }
        cars[i] = value;
    }

    // Print table and compute total
    cout << "\nDay\t\tCars\n";
    cout << "----------------------\n";
    for (int i = 0; i < SIZE; ++i) {
        cout << left << setw(10) << days[i] << "\t" << cars[i] << "\n";
        total += cars[i];
    }

    average = static_cast<double>(total) / SIZE;
    cout << "\nTotal cars = " << total << endl;
    cout << fixed << setprecision(2);
    cout << "Average per day = " << average << endl;

    // ASCII bar chart (auto-scaled)
    cout << "\nASCII Bar Chart (scaled to fit width):\n";
    int maxCount = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (cars[i] > maxCount) maxCount = cars[i];
    }

    const int MAX_WIDTH = 50; // max characters for the longest bar
    double scale = 1.0;
    if (maxCount > MAX_WIDTH && maxCount > 0) {
        scale = static_cast<double>(MAX_WIDTH) / maxCount;
    }

    for (int i = 0; i < SIZE; ++i) {
        int barLen = 0;
        if (maxCount == 0) {
            barLen = 0;
        } else {
            barLen = static_cast<int>(round(cars[i] * scale));
            if (cars[i] > 0 && barLen == 0) barLen = 1; // ensure non-zero values show at least one char
        }

        cout << left << setw(10) << days[i] << " | " 
             << string(barLen, '*') << " (" << cars[i] << ")\n";
    }
}
