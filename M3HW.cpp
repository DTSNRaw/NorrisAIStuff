// csc 134
// M3HW1 - Gold
// Damian
// 10/14/2025

#include <iostream>
#include <string>
#include <algorithm> // for transform
#include <ctime>     // for time()
#include <cstdlib>   // for srand, rand
#include <iomanip>   // for setprecision

int main() {
    // --- Question 1: Simple chat bot ---
    std::cout << "=== Question 1: Simple chat bot ===\n";
    std::cout << "Hello, I'm a C++ program!\n";
    std::cout << "Do you like me? Please type yes or no.\n";
    std::string q1_answer;
    std::getline(std::cin, q1_answer);
    // normalize to lowercase
    std::transform(q1_answer.begin(), q1_answer.end(), q1_answer.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    if (q1_answer == "yes") {
        std::cout << "That's great! I'm sure we'll get along.\n";
    } else if (q1_answer == "no") {
        std::cout << "Well, maybe you'll learn to like me later.\n";
    } else {
        std::cout << "If you're not sure... that's OK.\n";
    }

    std::cout << "\n";

    // --- Question 2: Receipt calculator (meal price, tax, tip if dine-in) ---
    // NOTE: Tax rate is set as a constant here. Change if your instructor expects another rate.
    const double TAX_RATE = 0.13; // 13% tax (change if needed)
    const double DINE_IN_TIP_RATE = 0.15; // 15% tip for dine-in

    std::cout << "=== Question 2: Receipt calculator ===\n";
    double mealPrice = 0.0;
    std::cout << "Enter the price of the meal (e.g. 12.50): ";
    while (!(std::cin >> mealPrice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input. Please enter a numeric meal price: ";
    }

    int dineChoice = 0;
    std::cout << "Please enter 1 if the order is dine in, 2 if it is to go: ";
    while (!(std::cin >> dineChoice) || (dineChoice != 1 && dineChoice != 2)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid choice. Enter 1 for dine in, 2 for takeaway: ";
    }

    double taxAmount = mealPrice * TAX_RATE;
    double tipAmount = 0.0;
    if (dineChoice == 1) {
        // dine in -> add 15% tip
        tipAmount = mealPrice * DINE_IN_TIP_RATE;
    } else {
        // takeaway -> no tip added
        tipAmount = 0.0;
    }
    double total = mealPrice + taxAmount + tipAmount;

    // print receipt
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n----- RECEIPT -----\n";
    std::cout << "Meal price: $" << std::setw(7) << mealPrice << "\n";
    std::cout << "Tax (" << (TAX_RATE * 100) << "%): $" << std::setw(7) << taxAmount << "\n";
    if (tipAmount > 0.0) {
        std::cout << "Tip (" << (DINE_IN_TIP_RATE * 100) << "%):  $" << std::setw(7) << tipAmount << "\n";
    } else {
        std::cout << "Tip:                $" << std::setw(7) << tipAmount << "\n";
    }
    std::cout << "-------------------\n";
    std::cout << "Total due:  $" << std::setw(7) << total << "\n";
    std::cout << "-------------------\n\n";

    // clear newline left in input buffer before using getline next
    std::cin.ignore(10000, '\n');

    // --- Question 3: Choose Your Own Adventure (CYOA) ---
    std::cout << "=== Question 3: Choose Your Own Adventure ===\n";
    std::cout << "You wake up in a dim forest clearing. You can either (A) follow a path\n";
    std::cout << "that leads deeper into the woods, or (B) try to climb a nearby hill\n";
    std::cout << "to get your bearings. Type A or B and press Enter: ";
    std::string q3_choice1;
    std::getline(std::cin, q3_choice1);
    std::transform(q3_choice1.begin(), q3_choice1.end(), q3_choice1.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    if (q3_choice1 == "a" || q3_choice1 == "a)") {
        // following the path -> leads to second choice
        std::cout << "You follow the path and come to a rickety wooden bridge over a stream.\n";
        std::cout << "Do you (C) cross the bridge or (D) walk along the streambank? Type C or D: ";
        std::string q3_choice2;
        std::getline(std::cin, q3_choice2);
        std::transform(q3_choice2.begin(), q3_choice2.end(), q3_choice2.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        if (q3_choice2 == "c" || q3_choice2 == "c)") {
            // crossing the bridge -> defeat (bridge collapses)
            std::cout << "You carefully step onto the bridge. Halfway across it snaps!\n";
            std::cout << "You fall into the stream and get swept away. Game Over.\n";
        } else if (q3_choice2 == "d" || q3_choice2 == "d)") {
            // walking along streambank -> victory
            std::cout << "Walking along the bank you find a friendly ranger who helps you.\n";
            std::cout << "You are safe and escorted back to the trailhead. You win!\n";
        } else {
            std::cout << "That's not a valid option. While you hesitate, a thunderstorm starts and\n";
            std::cout << "you decide to head back to the clearing. The adventure ends for now.\n";
        }
    } else if (q3_choice1 == "b" || q3_choice1 == "b)") {
        // climbing the hill -> immediate game over (steep slope)
        std::cout << "You try to climb the hill but the slope is slippery and you tumble back down.\n";
        std::cout << "You injure your ankle and cannot continue. Game Over.\n";
    } else {
        std::cout << "You didn't pick A or B. While you stand there thinking, night falls and the\n";
        std::cout << "sounds of the forest grow. The adventure pauses. (Restart to try again.)\n";
    }

    std::cout << "\n";

    // --- Question 4: Math practice (random addition of two single-digit numbers) ---
    std::cout << "=== Question 4: Math practice ===\n";
    // seed random
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int num1 = std::rand() % 10; // 0..9
    int num2 = std::rand() % 10; // 0..9

    std::cout << "What is " << num1 << " plus " << num2 << "?\n";
    int userAnswer;
    while (!(std::cin >> userAnswer)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Please enter an integer answer: ";
    }

    int correct = num1 + num2;
    if (userAnswer == correct) {
        std::cout << "Correct.\n";
    } else {
        std::cout << "Incorrect. The correct answer is " << correct << ".\n";
    }

    std::cout << "\nEnd of program. Thanks for running all questions!\n";

    return 0;
}
