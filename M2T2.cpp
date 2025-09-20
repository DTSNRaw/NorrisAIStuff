/*
CSC 134
M2T2 - Receipt calculator
Dotson Damian
9/20/25

*/
#include <iostream>
#include <iomanip> // for 2 decinal places
using namespace std;

int main() {
   //Purpose - create a simple receipt
   // unfortunately, I have to tax you

   // declare our variables
    string item = "🔋Batteries";
    double item_price = 9999.99;
    double tax_percent = 0.08; // 8% is 8/100
    double tax_amount; // tax in $
    double total; // price + tax
   // greet user and take the order
   cout << "Welcome to our CSC 134 BatteRestraunt!" << endl;
   cout << "You ordered one " << item << "." << endl;

   tax_amount = item_price * tax_percent; // take 8% of the item
   total = item_price + tax_amount;

   cout << setprecision(2) << fixed;
   cout << total << endl;






    return 0; // no errors



}