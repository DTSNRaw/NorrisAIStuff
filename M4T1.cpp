// CSC 134
// M4T1 - While
// Damian Dotson
// 3/10/2025

# include <iostream>
using namespace std;

int main(){



int number = 5;

int i = 0;
while (i < number){
    cout << "Hello" << endl;
    //i = i + 1;
    i++; //Shorter version

}
cout << "That's all!" << endl;
const int MIN_NUMBER = 1;
const int MAX_NUMBER = 10;

int num = MIN_NUMBER;
// print a table header
cout << "Number     Number Squared" << endl;
while (num <= MAX_NUMBER){
    cout << num << " " << num * num << endl;
    num++;


}
}
