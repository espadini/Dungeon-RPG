#include "Room.h"
#include <iostream>
#include <algorithm>
using namespace std;


// TODO: Implement Room constructor
Room::Room(const std::string& name, const std::string& description)
    : name(name), description(description), visited(false), monster(NULL) {
}


// TODO: Implement Room destructor
Room::~Room() {
    // TODO: Clean up monster and items
    if(monster) {
        delete monster;
        monster = NULL;
    }
    for (int i = 0; i < items.size(); i++) {delete items[i];}
    items.clear();
}


// TODO: Implement display
// HINTS:
// - Print formatted room information with decorative borders
// - Format:
//   ========================================
//   Room Name
//   ========================================
//   Description text
//   
//   [If monster] A MonsterName blocks your path!
//   
//   [If items] Items here:
//     - item1
//     - item2
//   
//   Exits: north, south, east
//   ========================================
//
void Room::display() const {
    // TODO: Display room information
    cout << "========================================" << endl;
    cout << getName() << endl;
    cout << "========================================" << endl;
    cout << getDescription() << "\n" << endl;
    if(monster) {cout << "A " << monster->getName() << " blocks your path!\n" << endl;}
    if(items.size() > 0) {
        cout << "Items here:" << endl;
        for(int i = 0; i < items.size(); i++) {
            cout << "- " << items[i]->getName() << endl;
        }
        cout << "" << endl;
    }
    cout << "Exits: ";
    bool first = true;
    for(map<string, Room*>::const_iterator it = exits.begin(); it != exits.end(); ++it) {
        if(!first) cout << ", ";
        cout << it->first;
        first = false;
    }
    cout << endl;
    cout << "========================================" << endl;
}


// TODO: Implement displayExits
// HINTS:
// - Print "Exits: "
// - Iterate through exits map using iterator
// - Print each direction (the key) separated by commas
// - Example output: "Exits: north, south, east"
//
void Room::displayExits() const {
    // TODO: Display available exits
    cout << "Exits: ";
    bool first = true;
    for(map<string, Room*>::const_iterator it = exits.begin(); it != exits.end(); ++it) {
        if(!first) cout << ", ";
        cout << it->first;
        first = false;
    }
    cout << endl;
}


// TODO: Implement addExit
// HINTS:
// - Check if room pointer is not NULL
// - Add to exits map: exits[direction] = room
//
void Room::addExit(const std::string& direction, Room* room) {
    // TODO: Add exit to map
    if(!room) {return;}
    exits[direction] = room;
}


// TODO: Implement getExit
// HINTS:
// - Look up direction in exits map
// - Use exits.find(direction)
// - If not found, return NULL
//
Room* Room::getExit(const std::string& direction) const {
    // TODO: Look up and return exit
    map<string, Room*>::const_iterator it = exits.find(direction);
    if(it == exits.end()) {return NULL;}
    return it->second;
}


// TODO: Implement hasExit
// HINTS:
// - Check if direction exists in exits map
bool Room::hasExit(const std::string& direction) const {
    // TODO: Check if exit exist
    map<string, Room*>::const_iterator it = exits.find(direction);
    if(it == exits.end()) {return false;}
    return true;  // REPLACE THIS
}


// TODO: Implement clearMonster
// HINTS:
// - If monster exists, delete it
// - Set monster pointer to NULL
//
void Room::clearMonster() {
    // TODO: Delete and clear monster
    if(monster){delete monster;}
    monster = NULL;
}


// TODO: Implement addItem
// HINTS:
// - Check if item pointer is not NULL
// - Add to items vector using push_back()
//
void Room::addItem(Item* item) {
    // TODO: Add item to room
    if(!item) {return;}
    items.push_back(item);
}


// TODO: Implement removeItem
// HINTS:
// - Search items vector for item by name (case-insensitive)
// - If found: erase from vector (DON'T delete - ownership transferred)
//
void Room::removeItem(const std::string& item_name) {
    // TODO: Find and remove item from room
    for(int i = 0; i < items.size(); i++) {
        string current = items[i]->getName();
        string currentLower = "";
        string itemLower = "";
        for(int j = 0; j < current.size(); j++) {currentLower += tolower(current[j]);}
        for(int k = 0; k < item_name.size(); k++) {itemLower += tolower(item_name[k]);}
        if(itemLower == currentLower) {
            items.erase(items.begin() + i);
            break;
        }
    }
}


// TODO: Implement displayItems
// HINTS:
// - Print each item's name in a list
// - Format: "  - ItemName"
//
void Room::displayItems() const {
    // TODO: Display all items in room
    for(int i = 0; i < items.size(); i++) {cout << " -" << items[i]->getName() << endl;}
}


// TODO: Implement getItem
// HINTS:
// - Search items vector for item by name (case-insensitive)
// - If found, return pointer to item
// - If not found, return NULL
//
Item* Room::getItem(const std::string& item_name) {
    // TODO: Find and return item pointer
        for(int i = 0; i < items.size(); i++) {
        string current = items[i]->getName();
        string currentLower = "";
        string itemLower = "";
        for(int j = 0; j < current.size(); j++) {currentLower += tolower(current[j]);}
        for(int k = 0; k < item_name.size(); k++) {itemLower += tolower(item_name[k]);}
        if(itemLower == currentLower) {
            return items[i];
            break;
        }
    }
    return NULL;
}
