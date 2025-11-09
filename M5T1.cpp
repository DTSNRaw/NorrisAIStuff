//Damian Dotson
//CSC134
//11/9/25


#include <iostream>
#include <string>
using namespace std;


// declare our functions
string formatAnswer(int answer);
void printAnswer(const string &msg);

int main() {
    int answer = 5;
    string message;
    message = formatAnswer(answer);
    printAnswer(message);
    return 0;
}

// define functions
string formatAnswer (int answer) {
    // Make a nice looking string containing the answer
    string answerMessage;
    answerMessage = "The answer is ";
    answerMessage += to_string(answer);
    return answerMessage;
}

void printAnswer(const string &msg) {
    // display our message
    cout << msg << endl;
}
