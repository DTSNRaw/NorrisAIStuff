/*
CSC 134
M1Lab
Damian Dotson
9/14/25

*/
#include <iostream>
using namespace std;
int main() {
// This program acts like a storefront
string item_name = "nuclear bombs";
int number_of_items = 20;
double cost_each = 0.99; 
double total_cost;
cout << "welcome to the " << item_name << " store!" << endl;
cout << "we have " << number_of_items << " " << item_name << endl;
cout << " Each costs $" << cost_each << endl;
total_cost = number_of_items * cost_each;
cout << "To purchase all " << number_of_items << " will cost $" << total_cost << " total" << endl;
cout << "Thank you for shopping with us!" << endl;
return 0; // no errors
}