#include "Game.h"
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

// TODO: Implement Game constructor
Game::Game() : player(NULL), current_room(NULL), 
               game_over(false), victory(false) {
}


// TODO: Implement Game destructor
Game::~Game() {
    // TODO: Clean up player and all rooms
    if(player) {
        delete player;
        player = NULL;
    }
    for(map<string, Room*>::const_iterator it = world.begin(); it != world.end(); ++it) {
        delete it->second;
    }
}


// TODO: Implement initializeWorld
// HINTS:
// - Create all rooms with new
// - Add each room to world using addRoom()
// - Connect rooms using connectRooms()
// - Add monsters to appropriate rooms using room->setMonster()
// - Add items to rooms using room->addItem()
// - Set current_room to starting room (entrance)
//
// SUGGESTED WORLD LAYOUT:
//                [Throne Room]
//                     |
//     [Armory] - [Hallway] - [Treasury]
//                     |
//                 [Entrance]
//
// MONSTERS:
// - Hallway: Goblin
// - Armory: Skeleton
// - Treasury: Skeleton
// - Throne Room: Dragon (boss!)
//
// ITEMS:
// - Entrance: Small Potion
// - Armory: Iron Sword, Chain Mail
// - Treasury: Health Potion
//
void Game::initializeWorld() {
    // TODO: Create rooms
    Room* entrance = new Room("Dungeon Entrance", "A dark stone corridor...");
    Room* hallway = new Room("Dungeon Hallway", "A long dreary hall, lit by the occasianal torch...");
    Room* armory = new Room("Dungeon Armory", "A small storage room filled with weapon and armor stands now mostly abandoned...");
    Room* treasury = new Room("Dungeon Treasury", "A cold stone room filled with chests and finery...");
    Room* throne_room = new Room("Throne Room","A grand hall filled with fractured stone columns and a singular gold laden throne atop a chiseled stair...");

    // TODO: Add rooms to world
    addRoom(entrance);
    addRoom(hallway);
    addRoom(armory);
    addRoom(treasury);
    addRoom(throne_room);

    // TODO: Connect rooms bidirectionally
    connectRooms(entrance->getName(), "north", hallway->getName());
    connectRooms(hallway->getName(), "west", armory->getName());
    connectRooms(hallway->getName(), "east", treasury->getName());
    connectRooms(hallway->getName(), "north", throne_room->getName());

    // TODO: Add monsters
    hallway->setMonster(new Goblin());
    armory->setMonster(new Skeleton());
    treasury->setMonster(new Skeleton());
    throne_room->setMonster(new Dragon());

    // TODO: Add items
    entrance->addItem(new Consumable("Small Potion", "A small healing potion", 10));
    armory->addItem(new Weapon("Iron Sword", "A sturdy blade", 5));
    armory->addItem(new Armor("Chain Mail", "Heavy protective armor", 3));
    treasury->addItem(new Consumable("Health Potion", "A powerful healing potion", 20));
    
    // TODO: Set starting room
    current_room = entrance;
}


// TODO: Implement createStartingInventory
// HINTS:
// - Give player starting weapon: Rusty Dagger (damage +2)
// - Give player starting food: Bread (heals 5 HP)
// - Use: player->addItem(new Weapon(...))
//
void Game::createStartingInventory() {
    // TODO: Give player starting items
    player->addItem(new Weapon("Rusty Dagger", "A crude shiv, rusted beyond belief", 2));
    player->addItem(new Consumable("Bread", "A small loaf of bread", 5));
}


// TODO: Implement addRoom
// HINTS:
// - Check if room pointer is not NULL
// - Add to world map using room's name as key
// - Use: world[room->getName()] = room
//
void Game::addRoom(Room* room) {
    // TODO: Add room to world map
    if(!room) {return;}
    world[room->getName()] = room;
}


// TODO: Implement connectRooms
// HINTS:
// - Look up both rooms in world map
// - If both exist:
//   - Add forward direction: room1->addExit(direction, room2)
//   - Determine reverse direction:
//     * north ↔ south
//     * east ↔ west
//   - Add reverse direction: room2->addExit(reverse, room1)
//
void Game::connectRooms(const std::string& room1_name, const std::string& direction,
                       const std::string& room2_name) {
    // TODO: Connect rooms bidirectionally
    if(!world[room1_name] || !world[room2_name]) {return;}
    else if(direction == "north") {
        world[room1_name]->addExit("north", world[room2_name]);
        world[room2_name]->addExit("south", world[room1_name]);
    }
    else if(direction == "south") {
        world[room1_name]->addExit("south", world[room2_name]);
        world[room2_name]->addExit("north", world[room1_name]);
    }
    else if(direction == "west") {
        world[room1_name]->addExit("west", world[room2_name]);
        world[room2_name]->addExit("east", world[room1_name]);
    }
    else if(direction == "east") {
        world[room1_name]->addExit("east", world[room2_name]);
        world[room2_name]->addExit("west", world[room1_name]);
    }
    else {return;}
}


// TODO: Implement run - main game loop
// HINTS:
// - Print welcome message and game title
// - Get player name from input 
// - Create player: player
// - Call initializeWorld()
// - Call createStartingInventory()
// - Display starting room
// - Mark starting room as visited
// - Main loop: 
//   - Print prompt: "> "
//   - Get command (use std::getline)
//   - Convert to lowercase (use std::transform)
//   - Call processCommand()
//   - Check victory condition
//   - Check defeat condition (player dead)
//
void Game::run() {
    // TODO: Implement main game loop
    string playerName, input;
    cout << "-~-~-~-~-~-~-~WELCOME TO THE DUNGEON-~-~-~-~-~-~-~" << endl;
    cout << "What is your name, adventurer? " << endl;
    getline(cin, playerName);
    player = new Player(playerName);
    cout << "" << endl;
    initializeWorld();
    createStartingInventory();
    current_room->display();
    current_room->markVisited();
    while(1) {
        cout << "> ";
        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        processCommand(input);
        if(!world["Throne_Room"]->getMonster()->isAlive()) {
            cout << "-~-~-~-~-~-~-~YOU WIN!-~-~-~-~-~-~-~" << endl;
            cout << "ECE 312 Final Project" << endl;
            cout << "Programmed by: Elijah Spadini" << endl;
            cout << "Thanks to: Prof. Speight, Asvin Kumar, Logan Bristol, and Jonathan Cats" << endl;
            break;
        }
        else if(game_over || !player->isAlive()) {
            cout << "-~-~-~-~-~-~-~YOU LOSE!-~-~-~-~-~-~-~" << endl;
            cout << "skill issue buddy. this game is supposed to be easy lol" << endl;
            break;
        }
    }   
}


// TODO: Implement processCommand
// HINTS:
// - Parse command into verb and object
// - Extract first word as verb
// - Rest of line is object
// - Dispatch to appropriate method based on verb:
//   * "go" or "move" → move(object)
//   * "look" or "l" → look()
//   * "attack" or "fight" → attack()
//   * "pickup" or "get" or "take" → pickupItem(object)
//   * "inventory" or "i" → inventory()
//   * "use" → useItem(object)
//   * "equip" or "e" → equip(object)
//   * "stats" → player->displayStats()
//   * "help" or "h" or "?" → help()
//   * "quit" or "exit" → set game_over to true
//
void Game::processCommand(const std::string& command) {
    // TODO: Parse and dispatch command
    string verb, object;
    if(command.empty()) {return;}
    istringstream iss(command);
    iss >> verb;
    getline(iss, object);
    size_t pos = object.find_first_not_of(' '); //AI helped me with syntax here.
    if (pos != string::npos) {object = object.substr(pos);} // if found (not "no position") extract from that position onward
    else {object.clear();}   // if not found (all spaces)
    if(verb == "go" || verb == "move") {move(object);}
    else if(verb == "look" || verb == "l") {look();}
    else if(verb == "attack" || verb == "fight") {attack();}
    else if(verb == "pickup" || verb == "get" || verb == "take") {pickupItem(object);}
    else if(verb == "inventory" || verb == "i") {inventory();}
    else if(verb == "use") {useItem(object);}
    else if(verb == "equip" || verb == "e") {equip(object);}
    else if(verb == "stats") {player->displayStats();}
    else if(verb == "help" || verb == "h" || verb == "?") {help();}
    else if(verb == "quit" || verb == "exit") {game_over = true;}
}


// TODO: Implement move
// HINTS:
// - Check if monster blocks path (current_room->hasMonster())
// - If blocked, print message and return
// - Get exit in specified direction
// - If exit exists:
//   - Update current_room
//   - Display new room
//   - Mark as visited
// - Otherwise print error: "You can't go that way!"
//
void Game::move(const std::string& direction) {
    // TODO: Move to adjacent room
    if(!current_room) {return;}
    if(current_room->hasMonster()) {cout << "A monster blocks your path!" << endl;}
    if(current_room->hasExit(direction)) {
        current_room = current_room->getExit(direction);
        current_room->display();
        current_room->markVisited();
    }
    else {cout << "You cannot go that way!" << endl;}
}


// TODO: Implement look
// HINTS:
// - Simply display current room
//
void Game::look() {
    // TODO: Display current room
    if(!current_room) {return;}
    current_room->display();
}


// TODO: Implement attack
// HINTS:
// - Check if monster in room
// - If no monster, print message and return
// - If monster present, call combat()
//
void Game::attack() {
    // TODO: Attack monster in room
    if(!current_room) {return;}
    if(current_room->hasMonster()) {combat(current_room->getMonster());}
    else {cout << "There is no monster to fight!" << endl;}
}


// TODO: Implement combat
// HINTS:
// - Print "=== COMBAT BEGINS ==="
// - Combat loop: while both player and monster are alive
//   - Prompt for player action: attack/use <item>/flee
//   - If attack:
//     * Calculate player damage
//     * Monster takes damage
//     * If monster dead:
//       - Print victory
//       - Player gains exp and gold
//       - Get loot from monster
//       - Add loot to current room
//       - Check if Dragon 
//       - Clear monster from room
//       - Break from loop
//   - If use:
//     * Extract item name from command
//     * Call player->useItem()
//   - If flee:
//     * Print message and break
//   - Monster turn (if alive):
//     * Print attack message
//     * Calculate monster damage
//     * Player takes damage
// - Print "=== COMBAT ENDS ==="
//
void Game::combat(Monster* monster) {
    // Simple turn-based combat loop
    if (!player || !monster) return;
    cout << "=== COMBAT BEGINS ===" << endl;

    while (player->isAlive() && monster->isAlive()) {
        // Player turn
        cout << "Your move (attack/use <item>/flee): ";
        string input;
        getline(cin, input);
        // parse verb and object
        string verb, object;
        if (input.empty()) { verb = "attack"; }
        else {
            istringstream iss(input);
            iss >> verb;
            getline(iss, object);
            // trim leading spaces
            size_t p = object.find_first_not_of(' ');
            if (p != string::npos) object = object.substr(p);
            else object.clear();
            transform(verb.begin(), verb.end(), verb.begin(), ::tolower);
            transform(object.begin(), object.end(), object.begin(), ::tolower);
        }

        if (verb == "use") {
            if (object.empty()) cout << "Use what?" << endl;
            else player->useItem(object);
        } else if (verb == "flee") {
            cout << "You flee from combat!" << endl;
            break;
        } else { // default: attack
            int dmg = player->calculateDamage();
            cout << "You attack the " << monster->getName() << " for " << dmg << " damage." << endl;
            monster->takeDamage(dmg);
            if (!monster->isAlive()) {
                cout << "You have defeated the " << monster->getName() << "!" << endl;
                // rewards
                int exp = monster->getExperienceReward();
                int gold = monster->getGoldReward();
                if (player) player->gainExperience(exp);
                if (player) player->addGold(gold);
                cout << "You gain " << exp << " experience and " << gold << " gold." << endl;
                // collect loot before deleting monster
                std::vector<Item*> loot = monster->dropLoot();
                // remove and delete monster via room helper
                if (current_room) {
                    // add loot to room
                    for (size_t i = 0; i < loot.size(); ++i) {
                        current_room->addItem(loot[i]);
                    }
                    // delete monster and clear room pointer
                    current_room->clearMonster();
                } else {
                    // no room reference: delete monster and transfer loot ownership lost
                    delete monster;
                }
                break;
            }
        }

        // Monster turn (if still alive)
        if (monster->isAlive()) {
            cout << monster->getAttackMessage() << endl;
            int mdmg = monster->calculateDamage();
            cout << "The " << monster->getName() << " hits you for " << mdmg << " damage." << endl;
            player->takeDamage(mdmg);
            if (!player->isAlive()) {
                cout << "You have been slain... Game over." << endl;
                game_over = true;
                break;
            }
        }
    }

    cout << "=== COMBAT ENDS ===" << endl;
}


// TODO: Implement pickupItem
// HINTS:
// - Get item from current room
// - If exists:
//   - Add to player inventory
//   - Remove from room (ownership transfer!)
// - Otherwise print error
//
void Game::pickupItem(const std::string& item_name) {
    if (!current_room || !player) { cout << "Nothing to pick up." << endl; return; }
    Item* it = current_room->getItem(item_name);
    if (!it) { cout << "No such item here." << endl; return; }
    player->addItem(it);
    current_room->removeItem(item_name); // ownership transferred
    cout << "You pick up the " << it->getName() << "." << endl;
}

// TODO: Implement inventory
//
void Game::inventory() {
    if (!player) { cout << "You have no inventory." << endl; return; }
    player->displayInventory();
}

// TODO: Implement useItem
// HINTS:
// - Call player->useItem(item_name)
//
void Game::useItem(const std::string& item_name) {
    if (!player) { cout << "You have no items." << endl; return; }
    player->useItem(item_name);
}


// TODO: Implement equip
// HINTS:
// - Get item from player inventory
// - Check if item exists
// - Check item type:
//   - If "Weapon": call player->equipWeapon()
//   - If "Armor": call player->equipArmor()
//   - Otherwise: print error (can't equip consumables)
//
void Game::equip(const std::string& item_name) {
    if (!player) { cout << "You have nothing to equip." << endl; return; }
    Item* it = player->getItem(item_name);
    if (!it) { cout << "You don't have that item." << endl; return; }
    std::string type = it->getType();
    if (type == "Weapon") {
        player->equipWeapon(item_name);
    } else if (type == "Armor") {
        player->equipArmor(item_name);
    } else {
        cout << "You can't equip that." << endl;
    }
}


// TODO: Implement help
// HINTS:
// - Print all available commands with descriptions
// - Format nicely with headers
// - Commands:
//   * go <direction> - Move
//   * look - Look around
//   * attack - Attack monster
//   * pickup <item> - Pick up item
//   * inventory - Show inventory
//   * use <item> - Use consumable
//   * equip <item> - Equip weapon/armor
//   * stats - Show character stats
//   * help - Show this help
//   * quit - Exit game
//
void Game::help() {
    cout << "Available commands:" << endl;
    cout << "  go <direction> - Move (north/south/east/west)" << endl;
    cout << "  look - Look around" << endl;
    cout << "  attack - Attack the monster in the room" << endl;
    cout << "  pickup <item> - Pick up an item" << endl;
    cout << "  inventory - Show your inventory" << endl;
    cout << "  use <item> - Use a consumable item" << endl;
    cout << "  equip <item> - Equip a weapon or armor" << endl;
    cout << "  stats - Show your character stats" << endl;
    cout << "  help - Show this help" << endl;
    cout << "  quit - Exit the game" << endl;
}
