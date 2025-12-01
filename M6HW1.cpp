// M6HW1_lastname.cpp
// M6HW1 - Project Prototype (Gold)
// 12/1/2025
// CSC 134
// Damian Dotson
// A small choose-your-own-adventure with rooms, dialog, items, a locked door (key required),
// and multiple endings. Uses numbered choices and void functions for scenes.

#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

// Function prototypes (each scene is a void function)
void main_menu();
void front_yard();
void porch();
void living_room();
void kitchen();
void basement();
void attic();
void garden_shed();
void check_inventory();
int get_valid_choice(int min, int max);
void ending_escape();
void ending_trapped();
void ending_treasure();

// Game state (global for simplicity — easy to extend into a class later)
bool gameRunning = true;
vector<string> inventory;
bool frontDoorLocked = true;   // locked until player finds "front key"
bool atticLocked = true;       // attic locked (simulates a second lock)
bool chestLocked = true;       // chest in attic locked (example lock)
bool hasReadNote = false;      // small flag used in dialog

// Helper: checks if item exists in inventory
bool has_item(const string &name) {
    for (const auto &it : inventory) if (it == name) return true;
    return false;
}

// Helper: add item if not present
void add_item(const string &name) {
    if (!has_item(name)) inventory.push_back(name);
}

// Helper: remove item
void remove_item(const string &name) {
    for (size_t i = 0; i < inventory.size(); ++i) {
        if (inventory[i] == name) {
            inventory.erase(inventory.begin() + i);
            return;
        }
    }
}

int main() {
    cout << "M6HW1 - Project Prototype\n";
    cout << "Welcome to 'Midnight at Marlowe House' (prototype)\n";
    cout << "Goal: explore, find items, solve at least one lock to reach a winning ending.\n\n";
    main_menu();
    cout << "Thanks for playing!\n";
    return 0;
}

/* ----------------- Scenes and Menus ----------------- */

void main_menu() {
    while (gameRunning) {
        cout << "\n=== Main Menu ===\n";
        cout << "You stand at the end of a quiet lane. Moonlight shows an old house with a dim porch light.\n";
        cout << "What would you like to do?\n";
        cout << "1. Walk to the front yard\n";
        cout << "2. Walk toward the garden shed\n";
        cout << "3. Check your inventory\n";
        cout << "4. Quit\n";
        cout << "Choose: ";
        int c = get_valid_choice(1,4);
        if (c == 1) front_yard();
        else if (c == 2) garden_shed();
        else if (c == 3) check_inventory();
        else if (c == 4) {
            cout << "You leave the lane and decide it's time for bed.\n";
            gameRunning = false;
        }
    }
}

// Front yard -> leads to porch
void front_yard() {
    cout << "\nYou step into the front yard. A cold breeze brushes past the old hedges.\n";
    cout << "A brass plaque by the gate reads: \"Marlowe House - Beware Curiosity\"\n";
    cout << "There is a faint whisper of music from somewhere inside.\n\n";
    cout << "Choices:\n";
    cout << "1. Go up to the porch and try the front door\n";
    cout << "2. Circle around to the side of the house\n";
    cout << "3. Return to the main menu\n";
    cout << "Choose: ";
    int c = get_valid_choice(1,3);
    if (c == 1) porch();
    else if (c == 2) living_room();
    else if (c == 3) return;
}

// Porch scene: front door is locked (lock & key)
void porch() {
    cout << "\nYou stand on the creaky porch. The front door is old oak with a keyhole.\n";
    cout << "A small lockbox is bolted near the door (it looks like it could hold a house key).\n";
    cout << "An inscription near the door reads: \"Only one who listens to the house may enter.\"\n";
    cout << "\nChoices:\n";
    cout << "1. Try to open the front door";
    if (frontDoorLocked) cout << " (locked)";
    cout << "\n2. Inspect the lockbox\n";
    cout << "3. Knock on the door\n";
    cout << "4. Go back to the yard\n";
    cout << "Choose: ";
    int c = get_valid_choice(1,4);
    if (c == 1) {
        if (!frontDoorLocked) {
            cout << "You use the key and the lock clicks open. The front door swings inward.\n";
            ending_escape(); // escape through main door — winning ending
        } else {
            cout << "It's locked. You need a key to open this door.\n";
            porch();
        }
    } else if (c == 2) {
        cout << "The lockbox has a small keyhole but is padlocked shut. There's a faint rattle inside.\n";
        // small puzzle: if player has 'tiny lockpick' from shed they can open
        if (has_item("tiny lockpick")) {
            cout << "You have a tiny lockpick in your pack. Use it to open the box?\n";
            cout << "1. Yes\n2. No\nChoose: ";
            int y = get_valid_choice(1,2);
            if (y == 1) {
                cout << "You work the tiny lock. The padlock pops open and inside is a small brass key.\n";
                add_item("front key");
                cout << "You take the front key.\n";
                // the front key should unlock front door
                frontDoorLocked = true; // remains locked until used at option 1
                porch();
            } else porch();
        } else {
            cout << "You don't have anything small enough to open the padlock.\n";
            porch();
        }
    } else if (c == 3) {
        cout << "You knock. For a moment nothing — then a faint voice answers from inside:\n";
        cout << "\"If you wish to leave, find what you lack. If you seek the attic, light the dark.\"\n";
        hasReadNote = true; // interpret as receiving a hint/dialog
        porch();
    } else if (c == 4) {
        front_yard();
    }
}

// Living room (side of house) -> windows, kitchen inside via a side door
void living_room() {
    cout << "\nYou walk along the side of the house and find a boarded window and a side door to the kitchen.\n";
    cout << "A motionless portrait on the wall inside seems to watch you — you can see it through a gap.\n\n";
    cout << "Choices:\n";
    cout << "1. Try the side door to the kitchen\n";
    cout << "2. Peer through the boarded window at the portrait\n";
    cout << "3. Go back to the yard\n";
    cout << "Choose: ";
    int c = get_valid_choice(1,3);
    if (c == 1) kitchen();
    else if (c == 2) {
        cout << "You peek and the portrait is of an old woman holding a lantern. A tiny folded note is tucked in the frame.\n";
        cout << "Do you try to reach the note? (1 = yes, 2 = no)\n";
        int y = get_valid_choice(1,2);
        if (y == 1) {
            cout << "You manage to pry out the note. It reads: \"The basement hides what the porch conceals.\"\n";
            hasReadNote = true;
            // optionally add a clue item
            add_item("folded note");
        }
        living_room();
    } else return;
}

// Kitchen scene with item pickup and access to basement
void kitchen() {
    cout << "\nYou slip into the small kitchen. The stove is cold, and there are cupboards stacked with jars.\n";
    cout << "On the table lies a tarnished key and a half-eaten apple.\n\n";
    cout << "Choices:\n";
    cout << "1. Take the tarnished key\n";
    cout << "2. Eat the apple (why would you?)\n";
    cout << "3. Go down a steep hatch to the basement\n";
    cout << "4. Return outside\n";
    cout << "Choose: ";
    int c = get_valid_choice(1,4);
    if (c == 1) {
        if (!has_item("tarnished key")) {
            cout << "You pick up the key. It looks like it might fit an interior lock (it is labeled 'Attic').\n";
            add_item("tarnished key");
        } else {
            cout << "You already took the key.\n";
        }
        kitchen();
    } else if (c == 2) {
        cout << "The apple is bruised but edible. You gain a little courage.\n";
        add_item("apple");
        kitchen();
    } else if (c == 3) {
        basement();
    } else if (c == 4) {
        living_room();
    }
}

// Basement scene — contains the 'front key' inside an old chest locked (second lock)
void basement() {
    cout << "\nThe basement is dim and smells of damp wood. Shelves of jars line the walls.\n";
    cout << "In the center sits a battered chest with a heavy lock (it seems to hold something important).\n\n";
    cout << "Choices:\n";
    cout << "1. Inspect the chest\n";
    cout << "2. Search the shelves\n";
    cout << "3. Go back upstairs\n";
    cout << "Choose: ";
    int c = get_valid_choice(1,3);
    if (c == 1) {
        cout << "The chest has a padlock. There is a tag: 'For those who listen.'\n";
        if (has_item("tiny lockpick")) {
            cout << "You can try to pick the lock with your tiny lockpick. Use it?\n1. Yes\n2. No\nChoose: ";
            int y = get_valid_choice(1,2);
            if (y == 1) {
                cout << "Click. The lock yields. Inside is a small brass front-door key!\n";
                add_item("front key");
                chestLocked = false;
                // Once chest opened, front key available to pick up
            }
        } else if (has_item("tarnished key")) {
            cout << "You wonder if the tarnished key fits — but it is too small. The chest remains locked.\n";
        } else {
            cout << "It's locked and you don't have anything to open it yet.\n";
        }
        basement();
    } else if (c == 2) {
        cout << "You rummage the shelves and find an old toolbox. Inside: a tiny lockpick and a sealed envelope.\n";
        if (!has_item("tiny lockpick")) {
            add_item("tiny lockpick");
            cout << "You take the tiny lockpick.\n";
        } else cout << "There's nothing else you need here.\n";
        if (!has_item("sealed envelope")) {
            add_item("sealed envelope");
            cout << "You also take a sealed envelope (it might contain a clue).\n";
        }
        basement();
    } else if (c == 3) {
        kitchen();
    }
}

// Attic — requires tarnished key to unlock; contains chest with treasure (alternate ending)
void attic() {
    cout << "\nYou climb the narrow ladder into the attic. Dust motes float through a single cracked window.\n";
    cout << "An old wooden trunk sits beneath the eaves.\n\n";
    cout << "Choices:\n";
    cout << "1. Try to open the attic trunk (locked)\n";
    cout << "2. Look out the window\n";
    cout << "3. Go back down\n";
    cout << "Choose: ";
    int c = get_valid_choice(1,3);
    if (c == 1) {
        if (has_item("tarnished key")) {
            cout << "You insert the tarnished key. The trunk opens with a sigh. Inside is a velvet bag of coins and a small carved amulet.\n";
            add_item("velvet bag");
            add_item("amulet");
            chestLocked = false;
            cout << "You found a treasure!\n";
            ending_treasure();
        } else {
            cout << "The trunk is locked and needs a key labeled 'Attic'.\n";
            attic();
        }
    } else if (c == 2) {
        cout << "Through the window you see the garden and distant lane. The moon looks close tonight.\n";
        attic();
    } else if (c == 3) {
        cout << "You climb down.\n";
        living_room(); // returns to side of house
    }
}

// Garden shed: contains tiny lockpick or message and NPC (old gardener)
void garden_shed() {
    cout << "\nYou approach the creaky garden shed. The door hangs half-open and a rusty rake leans inside.\n";
    cout << "An old man sits on an overturned bucket — he looks up and smiles.\n\n";
    cout << "\"Ah, a late visitor,\" he says. \"If you want to get back out, sometimes you must listen and bring light.\"\n";
    cout << "He gestures to a small table with a candle and a folded paper.\n";
    cout << "\nChoices:\n";
    cout << "1. Talk to the old man\n";
    cout << "2. Inspect the table (candle & paper)\n";
    cout << "3. Steal the rake and run (you monster)\n";
    cout << "4. Go back to main menu\n";
    cout << "Choose: ";
    int c = get_valid_choice(1,4);
    if (c == 1) {
        cout << "\"Many folks come here and think they must break locks. Listen instead: the house hums when music plays.\"\n";
        cout << "He hands you a small tin whistle.\n";
        add_item("tin whistle");
        garden_shed();
    } else if (c == 2) {
        cout << "The candle could be used to light a dark place. The paper has a scribble: 'Basement—box—brass.'\n";
        add_item("candle");
        garden_shed();
    } else if (c == 3) {
        cout << "You take the rake and sprint away in shame. The old man chuckles and calls after you.\n";
        add_item("rake");
        garden_shed();
    } else return;
}

// Inventory display
void check_inventory() {
    cout << "\n--- Inventory ---\n";
    if (inventory.empty()) cout << "You carry nothing.\n";
    else {
        for (size_t i = 0; i < inventory.size(); ++i) {
            cout << (i+1) << ". " << inventory[i] << "\n";
        }
    }
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
}

/* ----------------- Endings ----------------- */

void ending_escape() {
    cout << "\nYou unlock the front door with the brass key. Fresh night air floods your lungs.\n";
    cout << "Congratulations — you walk out of Marlowe House into the moonlit lane.\n";
    cout << "(Ending: You escaped! - Gold requirement: used a key to open a locked door.)\n";
    // Reset or quit to main menu
    cout << "Return to main menu? 1. Yes  2. Quit\nChoose: ";
    int c = get_valid_choice(1,2);
    if (c == 2) gameRunning = false;
    else return; // return to main menu loop
}

void ending_trapped() {
    cout << "\nYou chose poorly. The house's whisper fades to a scream and the door slams shut.\n";
    cout << "You are trapped in a looping dream — maybe next time you'll be braver.\n";
    cout << "(Ending: Trapped.)\n";
    cout << "Return to main menu? 1. Yes  2. Quit\nChoose: ";
    int c = get_valid_choice(1,2);
    if (c == 2) gameRunning = false;
    else return;
}

void ending_treasure() {
    cout << "\nWith treasure in hand, you find the attic ladder leads to a small rooftop hatch.\n";
    cout << "You pry it open and climb out onto the roof. From here you shimmy across to safety and escape with riches.\n";
    cout << "(Ending: Treasure escape — alternate winning ending.)\n";
    cout << "Return to main menu? 1. Yes  2. Quit\nChoose: ";
    int c = get_valid_choice(1,2);
    if (c == 2) gameRunning = false;
    else return;
}

/* ----------------- Input Helper ----------------- */

// Read an integer and validate range; consumes bad input and prompts again
int get_valid_choice(int min, int max) {
    int choice;
    while (true) {
        if (cin >> choice) {
            if (choice >= min && choice <= max) {
                // consume leftover newline so subsequent getline/ignores work smoothly
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return choice;
            } else {
                cout << "Please enter a number between " << min << " and " << max << ": ";
            }
        } else {
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
