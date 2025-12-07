#include "Player.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string.h>

using namespace std;

// TODO: Implement Player constructor
// HINTS:
// - MUST call Character base constructor. 
//
Player::Player(const std::string& name)
    : Character(name, 100, 10, 5),
      level(1), experience(0), gold(0),
      equipped_weapon(NULL), equipped_armor(NULL) {
}


// TODO: Implement Player destructor
// HINTS:
// - CRITICAL: Must delete all items in inventory to prevent memory leaks!
// - DON'T delete equipped_weapon or equipped_armor - they point to items
//   already in the inventory, so they're already deleted!
//
Player::~Player() {
    // TODO: Delete all inventory items
    for(int i = 0; i < inventory.size(); i++) {
        delete inventory[i];
    }
}


// TODO: Override displayStats
// HINTS:
// - Show player-specific information
// - Include: level, HP, attack (with weapon bonus), defense (with armor bonus), gold, experience
// - Show equipped weapon and armor names if any
// - Use decorative formatting (borders, headers)
// - Use getters to access inherited Character data
//
void Player::displayStats() const {
    // TODO: Display comprehensive player stats
    cout << "-~-~-~-~-~-~-~PLAYER STATS-~-~-~-~-~-~-~" << endl;
    cout << "Level: [" << getLevel() << "]" << endl;
    cout << "HP: [" << getCurrentHP() << "/" << getMaxHP() << "]" << endl;
    if(equipped_weapon) {cout << "Attack: [" << getAttack() << " + (" << equipped_weapon->getValue() << ")]" << endl;}
    else {cout << "Attack: [" << getAttack() << "]" << endl;}
    if(equipped_armor) {cout << "Defense: [" << getDefense() << " + (" << equipped_armor->getValue() << ")]" << endl;}
    else {cout << "Defense: [" << getDefense() << "]" << endl;}
    cout << "Gold: [" << getGold() << "]" << endl;
    cout << "Experience: [" << getExperience() << "]" << endl;
    if(equipped_weapon) {cout << "Weapon: [" << equipped_weapon->getName() << "]" << endl;}
    if(equipped_armor) {cout << "Armor: [" << equipped_armor->getName() << "]" << endl;}
    cout << "-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~" << endl;
}


// TODO: Override calculateDamage to include weapon bonus
// HINTS:
// - If weapon is equipped, add weapon's damage bonus
// - Return total damage
//
int Player::calculateDamage() const {
    // TODO: Calculate damage with weapon bonus
    int totalDamage;
    if(equipped_weapon) {totalDamage = getAttack() + equipped_weapon->getValue();}
    else {totalDamage = getAttack();}
    return totalDamage;
}


// TODO: Implement addItem
// HINTS:
// - Add item to inventory vector using push_back()
// - Print pickup message with item name
//
void Player::addItem(Item* item) {
    // TODO: Add item to inventory
    inventory.push_back(item);
    cout << "You picked up the " << item->getName() << "!" << endl;
}


// TODO: Implement removeItem
// HINTS:
// - Search inventory for item by name (case-insensitive comparison)
// - If found: delete the item, then erase from vector
// - If not found: print error message
// - Remember: inventory.erase(inventory.begin() + i) to remove at index i
//


void Player::removeItem(const std::string& item_name) {
    // TODO: Find and remove item from inventory
    bool found = false;
    for(int i = 0; i < inventory.size(); i++) {
        string current = inventory[i]->getName();
        string currentLower = "";
        string itemLower = "";
        for(int j = 0; j < current.size(); j++) {currentLower += tolower(current[j]);}
        for(int k = 0; k < item_name.size(); k++) {itemLower += tolower(item_name[k]);}
        if(itemLower == currentLower) {
            found = true;
            delete inventory[i];
            inventory.erase(inventory.begin() + i);
            cout << "The item has been removed!" << endl;
            break;
        }
    }
    if(!found) {cout << "Item not found!" << endl;}
}

// TODO: Implement displayInventory
// HINTS:
// - Print header: "----- Inventory -----"
// - If inventory is empty, print "Empty"
// - Otherwise, loop through and print each item's name and type
// - Format: "- ItemName (ItemType)"
// - Print footer: "--------------------"
//
void Player::displayInventory() const {
    // TODO: Display all items in inventory
    cout << "----- Inventory -----" << endl;
    if(inventory.empty()) {cout << "Empty" << endl;}
    else {
        for(int i = 0; i < inventory.size(); i++) {
            cout << inventory[i]->getName() << " (" << inventory[i]->getType() << ")" <<  endl;
        }
    }
    cout << "--------------------" << endl;
}


// TODO: Implement hasItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return true if found, false otherwise
// - Use same case-insensitive comparison as removeItem
//
bool Player::hasItem(const std::string& item_name) const {
    // TODO: Check if item exists in inventory
    bool found = false;
    for(int i = 0; i < inventory.size(); i++) {
        string current = inventory[i]->getName();
        string currentLower = "";
        string itemLower = "";
        for(int j = 0; j < current.size(); j++) {currentLower += tolower(current[j]);}
        for(int k = 0; k < item_name.size(); k++) {itemLower += tolower(item_name[k]);}
        if(itemLower == currentLower) {
            found = true;
            break;
        }
    }
    return found;
}



// TODO: Implement getItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return pointer to item if found
// - Return NULL if not found
//
Item* Player::getItem(const std::string& item_name) {
    // TODO: Find and return item pointer
    for(int i = 0; i < inventory.size(); i++) {
        string current = inventory[i]->getName();
        string currentLower = "";
        string itemLower = "";
        for(int j = 0; j < current.size(); j++) {currentLower += tolower(current[j]);}
        for(int k = 0; k < item_name.size(); k++) {itemLower += tolower(item_name[k]);}
        if(itemLower == currentLower) {
            return inventory[i];
        }
    }
    return NULL;
}


// TODO: Implement equipWeapon
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Weapon"
// - If current weapon equipped, print unequip message
// - Set equipped_weapon pointer to this item
// - Print equip message
//
void Player::equipWeapon(const std::string& weapon_name) {
    // TODO: Equip weapon from inventory
    Item* currWeapon = getItem(weapon_name);
    if(!currWeapon || currWeapon->getType() != "Weapon") {
        cout << "That's not a weapon!" << endl;
        return;
    }
    else {
        if(equipped_weapon) {cout << "Unequipping the " << equipped_weapon->getName() << "..." << endl;}
        equipped_weapon = currWeapon;
        cout << "The " << currWeapon->getName() << " is now equipped!" << endl;
    }
}


// TODO: Implement equipArmor
// HINTS:
// - Similar to equipWeapon but for armor
// - Check if item type is "Armor"
// - Set equipped_armor pointer
//
void Player::equipArmor(const std::string& armor_name) {
    // TODO: Equip armor from inventory
    Item* currArmor = getItem(armor_name);
    if(!currArmor || currArmor->getType() != "Armor") {
        cout << "That's not a piece of Armor!" << endl;
        return;
    }
    else {
        if(equipped_armor) {cout << "Unequipping the " << equipped_armor->getName() << "..." << endl;}
        equipped_armor = currArmor;
        cout << "The " << currArmor->getName() << " is now equipped!" << endl;
    }
}


// TODO: Implement unequipWeapon
// HINTS:
// - Check if weapon is currently equipped
// - If so, print message and set equipped_weapon to NULL
// - If not, print error message
//
void Player::unequipWeapon() {
    // TODO: Unequip current weapon
    if(equipped_weapon) {
        cout << equipped_weapon->getName() << " was unequipped!" << endl;
        equipped_weapon = NULL;
    }
    else {cout << "You don't have a weapon currently equipped!" << endl;}
}


// TODO: Implement unequipArmor
// HINTS:
// - Similar to unequipWeapon
// - Set equipped_armor to NULL
//
void Player::unequipArmor() {
    // TODO: Unequip current armor
    if(equipped_armor) {
        cout << equipped_armor->getName() << " was unequipped!" << endl;
        equipped_armor = NULL;
    }
    else {cout << "You don't have any armor currently equipped!" << endl;}
}


// TODO: Implement useItem
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Consumable"
// - Cast to Consumable*: Consumable* consumable = static_cast<Consumable*>(item)
// - Check if already used: consumable->isUsed()
// - Get healing amount: consumable->getHealingAmount()
// - Call heal() with that amount
// - Call consumable->use() to mark as used
// - Remove item from inventory (it's been consumed!)
//
void Player::useItem(const std::string& item_name) {
    // TODO: Use consumable item
    Item* currItem = getItem(item_name);
    if(!currItem || currItem->getType() != "Consumable") {
        cout << "That's not a consumable!" << endl;
        return;
    }
    Consumable* consumable = static_cast<Consumable*>(currItem);
    if(consumable->isUsed()) {
        cout << "You've already used this!" << endl;
        return;
    }
    int healingAmount = consumable->getHealingAmount();
    heal(healingAmount);
    consumable->use();
    removeItem(consumable->getName());
}


// TODO: Implement gainExperience
// HINTS:
// - Add experience points
// - Print message showing exp gained
// - Check if enough exp to level up: if (experience >= level * 100)
// - If so, call levelUp()
//
void Player::gainExperience(int exp) {
    // TODO: Add experience and check for level up
    experience += exp;
    cout << "You gained " << exp << " experience!" << endl;
    if(experience >= level * 100) {
        levelUp();
    }
}


// TODO: Implement levelUp
// HINTS:
// - Increment level
// - Reset experience to 0
// - Increase stats:
//   * Increase max_hp by 10 (use setMaxHP())
//   * Set current_hp to max (full heal on level up)
//   * Increase attack by 2
//   * Increase defense by 1
// - Print celebratory level up message
// - Display new stats
//
void Player::levelUp() {
    // TODO: Level up the player
    level++;
    experience = 0;
    setMaxHP(getMaxHP() + 10);
    setCurrentHP(getMaxHP());
    setAttack(getAttack() + 2);
    setDefense(getDefense() + 1);
    cout << "-~-~-~-~-~-~LEVEL UP-~-~-~-~-~-~" << endl;
    displayStats();
}

/*
int main() {
    Player hero("Alice");
    hero.displayStats();
    hero.takeDamage(20);  // Inherited method
    hero.displayStats();
    hero.addItem(new Weapon("Sword", "Sharp", 5));
    hero.addItem(new Consumable("Potion", "Heals", 20));
    hero.displayInventory();
    hero.removeItem("potion");  // Case insensitive
    hero.displayInventory();
    hero.addItem(new Weapon("Sword", "Sharp", 5));
    hero.addItem(new Armor("Chainmail", "Strong", 3));
    
    hero.equipWeapon("sword");
    hero.equipArmor("chainmail");
    
    hero.displayStats();
    
    int dmg = hero.calculateDamage();
    std::cout << "Damage: " << dmg << std::endl;  // Should include weapon bonus
    hero.displayStats();
    hero.gainExperience(100);  // Should trigger level up
    hero.displayStats();

    return 0;
}
    */