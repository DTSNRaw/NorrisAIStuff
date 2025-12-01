#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

// Directions
enum Direction { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3, NUM_DIRECTIONS = 4 };
const string DIRECTION_NAMES[NUM_DIRECTIONS] = { "north", "east", "south", "west" };

// Rooms
enum RoomId { ENTRANCE_HALL = 0, LIBRARY = 1, KITCHEN = 2, GARDEN = 3, BASEMENT = 4, NUM_ROOMS = 5 };

// Helper utilities
static inline string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
    return s;
}

static inline vector<string> splitTokens(const string &line) {
    vector<string> tokens;
    istringstream iss(line);
    string tok;
    while (iss >> tok) tokens.push_back(toLower(tok));
    return tokens;
}

// Room struct
struct Room {
    string name;
    string description;
    array<int, NUM_DIRECTIONS> connections; // -1 = no connection
    vector<string> items; // item names present in room

    Room() {
        connections.fill(-1);
    }
};

// Global item descriptions (single place to add longer descriptions)
map<string, string> itemDescriptions = {
    {"book", "An old leather-bound book. The title is worn off."},
    {"key", "A small rusty key. It looks like it might open a simple lock."},
    {"apple", "A slightly bruised apple. Still edible."},
    {"lantern", "An old oil lantern. It could light dark places."}
};

void printHelp() {
    cout << "\nCommands:\n";
    cout << "  north|n|east|e|south|s|west|w    - move in a direction\n";
    cout << "  go <direction>                   - same as above\n";
    cout << "  look                             - describe the room and show items/exits\n";
    cout << "  inspect|examine <item>           - view item description (room or inventory)\n";
    cout << "  take|get <item>                  - pick up an item in the room\n";
    cout << "  drop <item>                      - drop an item from your inventory\n";
    cout << "  inventory|i                      - show carried items\n";
    cout << "  help                             - show this help\n";
    cout << "  quit|q                           - exit game\n\n";
}

void printExits(const Room &r) {
    bool first = true;
    for (int d = 0; d < NUM_DIRECTIONS; ++d) {
        if (r.connections[d] != -1) {
            if (!first) cout << ", ";
            cout << DIRECTION_NAMES[d];
            first = false;
        }
    }
    if (first) cout << "none";
    cout << endl;
}

void printRoom(const Room &r) {
    cout << "\n" << r.name << "\n";
    cout << r.description << "\n";
    cout << "Items here: ";
    if (r.items.empty()) cout << "none";
    else {
        for (size_t i = 0; i < r.items.size(); ++i) {
            if (i) cout << ", ";
            cout << r.items[i];
        }
    }
    cout << "\nExits: ";
    printExits(r);
}

// find an item in a vector (case-insensitive compare)
int findItemIndex(const vector<string> &vec, const string &item) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (toLower(vec[i]) == toLower(item)) return (int)i;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Setup rooms
    vector<Room> rooms(NUM_ROOMS);

    rooms[ENTRANCE_HALL].name = "Entrance Hall";
    rooms[ENTRANCE_HALL].description = "A grand entrance hall with a dusty chandelier hanging above.";
    rooms[ENTRANCE_HALL].connections[NORTH] = LIBRARY;
    rooms[ENTRANCE_HALL].connections[EAST]  = KITCHEN;
    rooms[ENTRANCE_HALL].connections[WEST]  = GARDEN;
    rooms[ENTRANCE_HALL].items = {"lantern"};

    rooms[LIBRARY].name = "Library";
    rooms[LIBRARY].description = "Walls lined with ancient books. The air smells of old paper.";
    rooms[LIBRARY].connections[SOUTH] = ENTRANCE_HALL;
    rooms[LIBRARY].items = {"book"};

    rooms[KITCHEN].name = "Kitchen";
    rooms[KITCHEN].description = "A spacious kitchen with an old stove and wooden counter.";
    rooms[KITCHEN].connections[WEST] = ENTRANCE_HALL;
    rooms[KITCHEN].connections[SOUTH] = BASEMENT;
    rooms[KITCHEN].items = {"apple", "key"};

    rooms[GARDEN].name = "Garden";
    rooms[GARDEN].description = "An overgrown garden with stone pathways and a small fountain.";
    rooms[GARDEN].connections[EAST] = ENTRANCE_HALL;
    rooms[GARDEN].items = {};

    rooms[BASEMENT].name = "Basement";
    rooms[BASEMENT].description = "A dark, damp basement with cobwebs in the corners.";
    rooms[BASEMENT].connections[NORTH] = KITCHEN;
    rooms[BASEMENT].items = {};

    int currentRoom = ENTRANCE_HALL;
    vector<string> inventory;

    cout << "Welcome! Type 'help' for commands.\n";
    printRoom(rooms[currentRoom]);

    bool running = true;
    string line;
    while (running) {
        cout << "\n> ";
        if (!std::getline(cin, line)) break; // EOF
        auto tokens = splitTokens(line);
        if (tokens.empty()) continue;

        string cmd = tokens[0];

        // movement shorthand: n, s, e, w or full words or "go <dir>"
        if (cmd == "n" || cmd == "north" || (cmd == "go" && tokens.size() > 1 && tokens[1] == "north")) {
            int dest = rooms[currentRoom].connections[NORTH];
            if (dest != -1) { currentRoom = dest; printRoom(rooms[currentRoom]); }
            else cout << "You can't go north from here.";
        }
        else if (cmd == "e" || cmd == "east" || (cmd == "go" && tokens.size() > 1 && tokens[1] == "east")) {
            int dest = rooms[currentRoom].connections[EAST];
            if (dest != -1) { currentRoom = dest; printRoom(rooms[currentRoom]); }
            else cout << "You can't go east from here.";
        }
        else if (cmd == "s" || cmd == "south" || (cmd == "go" && tokens.size() > 1 && tokens[1] == "south")) {
            int dest = rooms[currentRoom].connections[SOUTH];
            if (dest != -1) { currentRoom = dest; printRoom(rooms[currentRoom]); }
            else cout << "You can't go south from here.";
        }
        else if (cmd == "w" || cmd == "west" || (cmd == "go" && tokens.size() > 1 && tokens[1] == "west")) {
            int dest = rooms[currentRoom].connections[WEST];
            if (dest != -1) { currentRoom = dest; printRoom(rooms[currentRoom]); }
            else cout << "You can't go west from here.";
        }
        // look
        else if (cmd == "look") {
            printRoom(rooms[currentRoom]);
        }
        // take / get
        else if (cmd == "take" || cmd == "get") {
            if (tokens.size() < 2) {
                cout << "Take what?";
                continue;
            }
            // join remaining tokens into item name (support multi-word)
            string item = line.substr(line.find_first_of(" \t") + 1);
            item = toLower(item);
            int idx = findItemIndex(rooms[currentRoom].items, item);
            if (idx != -1) {
                inventory.push_back(rooms[currentRoom].items[idx]);
                cout << "You take the " << rooms[currentRoom].items[idx] << ".";
                rooms[currentRoom].items.erase(rooms[currentRoom].items.begin() + idx);
            } else {
                cout << "There is no '" << item << "' here.";
            }
        }
        // drop
        else if (cmd == "drop") {
            if (tokens.size() < 2) {
                cout << "Drop what?";
                continue;
            }
            string item = line.substr(line.find_first_of(" \t") + 1);
            item = toLower(item);
            int idx = findItemIndex(inventory, item);
            if (idx != -1) {
                rooms[currentRoom].items.push_back(inventory[idx]);
                cout << "You drop the " << inventory[idx] << ".";
                inventory.erase(inventory.begin() + idx);
            } else {
                cout << "You don't have '" << item << "'.";
            }
        }
        // inspect / examine
        else if (cmd == "inspect" || cmd == "examine") {
            if (tokens.size() < 2) {
                cout << "Inspect what?";
                continue;
            }
            string item = line.substr(line.find_first_of(" \t") + 1);
            item = toLower(item);
            // look in room
            int idxRoom = findItemIndex(rooms[currentRoom].items, item);
            int idxInv  = findItemIndex(inventory, item);
            if (idxRoom != -1) {
                string nm = rooms[currentRoom].items[idxRoom];
                auto it = itemDescriptions.find(toLower(nm));
                if (it != itemDescriptions.end()) cout << it->second;
                else cout << "It's a " << nm << ".";
            } else if (idxInv != -1) {
                string nm = inventory[idxInv];
                auto it = itemDescriptions.find(toLower(nm));
                if (it != itemDescriptions.end()) cout << it->second;
                else cout << "It's a " << nm << " in your pack.";
            } else {
                cout << "No '" << item << "' to inspect here or in your inventory.";
            }
        }
        // inventory
        else if (cmd == "inventory" || cmd == "i") {
            cout << "You are carrying: ";
            if (inventory.empty()) cout << "nothing";
            else {
                for (size_t i = 0; i < inventory.size(); ++i) {
                    if (i) cout << ", ";
                    cout << inventory[i];
                }
            }
            cout << endl;
        }
        else if (cmd == "help") {
            printHelp();
        }
        else if (cmd == "quit" || cmd == "q") {
            running = false;
        }
        else {
            cout << "I don't understand that command. Type 'help' for a list of commands.";
        }
    }

    cout << "\nThanks for playing!\n";
    return 0;
}
