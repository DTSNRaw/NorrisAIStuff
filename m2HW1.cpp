#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <chrono>
#include <limits>

using namespace std;

// Helper function to read a double with validation
double read_double(const string &prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Invalid input. Please enter a numeric value.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Helper function to read an integer with validation
int read_int(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Invalid input. Please enter an integer value.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    cout << "==============================\n";
    cout << "   QUESTION 1: BANK PROGRAM\n";
    cout << "==============================\n";

    // Question 1 – Banking simulation
    cout << "Enter account holder's name: ";
    string name;
    getline(cin, name);

    double starting_balance = read_double("Starting account balance ($): ");
    double deposit_amount = read_double("Amount of deposit ($): ");
    double withdrawal_amount = read_double("Amount of withdrawal ($): ");
    double final_balance = starting_balance + deposit_amount - withdrawal_amount;

    // Generate a random 8-digit account number
    auto seed = static_cast<unsigned long>(
        chrono::high_resolution_clock::now().time_since_epoch().count()
    );
    mt19937_64 rng(seed);
    uniform_int_distribution<long long> dist(10000000LL, 99999999LL);
    long long account_number = dist(rng);

    // Output results
    cout << "\n--- Account Summary ---\n";
    cout << "Name on account: " << name << "\n";
    cout << "Account number : " << account_number << "\n";
    cout << fixed << setprecision(2);
    cout << "Starting balance : $" << starting_balance << "\n";
    cout << "Deposit amount   : $" << deposit_amount << "\n";
    cout << "Withdrawal amount: $" << withdrawal_amount << "\n";
    cout << "Final balance    : $" << final_balance << "\n";

    cout << "\n==============================\n";
    cout << "   PIZZA PARTY CALCULATOR\n";
    cout << "==============================\n";

    // Pizza Party program
    int pizzas = read_int("How many pizzas are you ordering? ");
    int slices_per_pizza = read_int("How many slices per pizza? ");
    int visitors = read_int("How many visitors are coming? ");

    int total_slices = pizzas * slices_per_pizza;
    int slices_needed = visitors * 3;
    int leftovers = total_slices - slices_needed;

    cout << "\nTotal slices available: " << total_slices << endl;
    cout << "Slices needed (3 per visitor): " << slices_needed << endl;

    if (leftovers >= 0)
        cout << "Slices left over: " << leftovers << endl;
    else
        cout << "Not enough slices! You need " << -leftovers << " more slices.\n";

    cout << "\n==============================\n";
    cout << "   QUESTION 4: FTCC CHEER PROGRAM\n";
    cout << "==============================\n";

    // Cheer Program with string concatenation restrictions
    string letsGo = "Let's go ";
    string school = "FTCC";
    string team = "Trojans";
    string cheerOne = letsGo + school;
    string cheerTwo = letsGo + team;

    cout << cheerOne << endl;
    cout << cheerOne << endl;
    cout << cheerOne << endl;
    cout << cheerTwo << endl;

    cout << "\nProgram complete.\n";
    return 0;
}
