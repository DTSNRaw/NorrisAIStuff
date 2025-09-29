// simple game: if-statement example (Program Two style)
#include <iostream>
#include <string>
#include <algorithm> // for transform

using namespace std;

int main() {
    cout << "Welcome to the quick showdown!" << endl;
    cout << "Do you choose to 'fight' or 'run'?" << endl;
    cout << "Type fight or run: ";

    string choice;
    cin >> choice;

    // normalize to lowercase for case-insensitive comparison
    transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

    if (choice == "fight") {
        cout << "You chose to fight!" << endl;
        cout << "You bravely stand your ground and win a mysterious sword!" << endl;
    }
    else if (choice == "run") {
        cout << "You chose to run!" << endl;
        cout << "You dash away and find a safe hiding place — you live to fight another day." << endl;
    }
    else {
        cout << "I'm sorry, that is not a valid choice." << endl;
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}
