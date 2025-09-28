#include <iostream>
using namespace std;

int main() {
    // declare the variables
    int widthOne, lengthOne,widthTwo, lengthTwo;
    int areaOne, areaTwo;
    // ask for user input
    cout << "Please enter the width and height of the first" << endl;
    cout << "rectangle, separated by a space or newline" << endl;
    cin >> widthOne >> lengthOne;

    cout << "Please enter the width and height of the Second" << endl;
    cout << "rectangle, separated by a space or newline" << endl;
    cin >> widthTwo >> lengthTwo;

    // calculate answer
    areaOne = widthOne * lengthOne;
    areaTwo = widthTwo * lengthTwo;


    // display results
    cout << "rectangle one has area of " << areaOne << endl;
    cout << "rectangle two has area of " << areaTwo << endl;


}