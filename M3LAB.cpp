#include <iostream>
using namespace std;

int main() {
    // Declare variable to store the numerical grade
    int grade;

    // Prompt the user for input
    cout << "Enter your numerical grade: ";
    cin >> grade;

    // Check if input is valid (grade between 0 and 100)
    if (grade < 0 || grade > 100) {
        cout << "Invalid input. Please enter a grade between 0 and 100." << endl;
        return 1; // Exit program with an error code
    }

    char letterGrade; // Variable to store the letter grade

    // Determine the letter grade using conditional statements
    if (grade >= 90 && grade <= 100)
        letterGrade = 'A';
    else if (grade >= 80 && grade <= 89)
        letterGrade = 'B';
    else if (grade >= 70 && grade <= 79)
        letterGrade = 'C';
    else if (grade >= 60 && grade <= 69)
        letterGrade = 'D';
    else
        letterGrade = 'F';

    // Display the result
    cout << "Your letter grade is: " << letterGrade << endl;

    return 0; // End of program
}
