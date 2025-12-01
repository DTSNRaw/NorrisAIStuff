#include <iostream>
#include <limits>
using namespace std;

/*
11/4/2025
CSC 134
M5LAB1 - Choose Your Own Adventure

*/

// Function Prototypes
void main_menu();
void choice_front_door();
void choice_back_door();
void choice_go_home();
void explore_basement();
void talk_to_ghost();
int get_valid_choice(int min, int max); // helper for input validation

int main() {
  cout << "M5LAB1 - Choose Your Own Adventure" << endl;
  // load up the main menu
  main_menu();
  // when we return here, we're done
  cout << "Thanks for playing!" << endl;
  return 0; // finished with no errors
}

void main_menu() {
  // Simple menu that lets the user choose 1,2, or 3, or 4 to quit.
  cout << "\n=== Main Menu ===" << endl;
  cout << "You're in front of a spooky old house..." << endl;
  cout << "Do you:" << endl;
  cout << "1. Try the front door" << endl;
  cout << "2. Sneak around back" << endl;
  cout << "3. Forget it, and go home" << endl;
  cout << "4. [Quit]" << endl;
  cout << "Choose: ";

  int choice = get_valid_choice(1, 4);

  if (1 == choice) {
    choice_front_door();
  } else if (2 == choice) {
    choice_back_door();
  } else if (3 == choice) {
    choice_go_home();
  } else if (4 == choice) {
    cout << "Ok, quitting game" << endl;
    return; // go back to main()
  }
}

// FUNCTION DEFINITIONS

// Helper - get an integer in [min,max] with validation
int get_valid_choice(int min, int max) {
  int choice;
  while (true) {
    if (cin >> choice) {
      if (choice >= min && choice <= max) {
        // valid
        return choice;
      } else {
        cout << "That's not a valid choice, please enter a number between "
             << min << " and " << max << ": ";
      }
    } else {
      // non-integer input
      cout << "Invalid input. Please enter a number between " << min << " and "
           << max << ": ";
      cin.clear(); // clear error flags
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
    }
  }
}

void choice_front_door() {
  cout << "\nYou try the front door." << endl;
  cout << "It's locked. " << endl;
  cout << "Do you:" << endl;
  cout << "1. Check around back" << endl;
  cout << "2. Give up and go home" << endl;
  cout << "Choose: ";
  int choice = get_valid_choice(1, 2);

  if (1 == choice) {
    choice_back_door();
  } else if (2 == choice) {
    choice_go_home();
  }
}

void choice_back_door() {
  cout << "\nYou sneak around to the back of the house." << endl;
  cout << "There is an old wooden back door and a small basement window with "
          "frosted glass." << endl;
  cout << "Do you:" << endl;
  cout << "1. Try the back door" << endl;
  cout << "2. Peer through the basement window" << endl;
  cout << "3. Go back to the front" << endl;
  cout << "Choose: ";
  int choice = get_valid_choice(1, 3);

  if (1 == choice) {
    cout << "The back door is slightly ajar — you slip inside quietly..." << endl;
    explore_basement();
  } else if (2 == choice) {
    cout << "You kneel and look through the frosted glass. Shadows move inside..." << endl;
    talk_to_ghost();
  } else if (3 == choice) {
    cout << "You walk back to the front of the house." << endl;
    main_menu();
  }
}

void choice_go_home() {
  cout << "\nYou decide this house is too creepy. You start to walk away." << endl;
  cout << "Halfway down the street, you wonder if you missed something. Do you:" << endl;
  cout << "1. Turn around and go back" << endl;
  cout << "2. Keep going home" << endl;
  cout << "Choose: ";
  int choice = get_valid_choice(1, 2);

  if (1 == choice) {
    cout << "You can't resist — curiosity wins. You head back to the house." << endl;
    main_menu();
  } else if (2 == choice) {
    cout << "You go home safely. Maybe another night..." << endl;
    cout << "(End: You went home.)" << endl;
    // After an ending, return to main menu so player can play again or quit.
    main_menu();
  }
}

void explore_basement() {
  cout << "\nYou find a creaky staircase leading down to the basement." << endl;
  cout << "The air is cold and smells like old books." << endl;
  cout << "Do you:" << endl;
  cout << "1. Follow the sound (a faint humming)" << endl;
  cout << "2. Search the shelves of old jars and books" << endl;
  cout << "3. Leave immediately" << endl;
  cout << "Choose: ";
  int choice = get_valid_choice(1, 3);

  if (1 == choice) {
    cout << "You follow the humming and find a small glowing music box. "
            "When you open it, the music puts your mind at ease." << endl;
    cout << "(Ending: You discovered a mysterious magical keepsake.)" << endl;
  } else if (2 == choice) {
    cout << "You browse the shelves and pull out a dusty diary. Inside is a "
            "map of the house with a big X on the attic." << endl;
    cout << "You tuck the diary in your jacket and head back upstairs." << endl;
    cout << "(You might want to check the attic next time.)" << endl;
  } else if (3 == choice) {
    cout << "A shiver runs down your spine and you decide to get out while you can." << endl;
  }

  // After finishing this branch, return to main menu
  main_menu();
}

void talk_to_ghost() {
  cout << "\nAs you peer through the window, a pale face presses against the glass!" << endl;
  cout << "It smiles sadly but does not move. The hairs on your neck stand up." << endl;
  cout << "Do you:" << endl;
  cout << "1. Knock on the window" << endl;
  cout << "2. Call out 'Hello?'" << endl;
  cout << "3. Run away" << endl;
  cout << "Choose: ";
  int choice = get_valid_choice(1, 3);

  if (1 == choice) {
    cout << "You knock. The face tilts, and then the window cracks open. A soft voice "
            "thanks you for waking it." << endl;
    cout << "(Ending: You freed a lonely spirit.)" << endl;
  } else if (2 == choice) {
    cout << "You call 'Hello?' The face mouths words you cannot hear, then points "
            "toward the garden shed." << endl;
    cout << "Curiosity pulls you toward the shed..." << endl;
    cout << "(You can follow up with an extra scene if you want to expand.)" << endl;
  } else if (3 == choice) {
    cout << "You run — and trip on the lawn. When you look back, the face is gone." << endl;
    cout << "(Ending: You escaped, heart pounding.)" << endl;
  }

  
  main_menu();
}
