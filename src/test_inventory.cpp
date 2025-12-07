#include <vector>
#include "Item.h"
#include <iostream> 
#include <cctype>   
#include <string.h>
using namespace std;

int main() {
    std::vector<Item*> inventory;
    
    // Add items
    inventory.push_back(new Weapon("Sword", "Sharp blade", 5));
    inventory.push_back(new Armor("Shield", "Wooden shield", 2));
    inventory.push_back(new Consumable("Potion", "Heals", 20));
    
    // Display all
    for (int i = 0; i < inventory.size(); i++) {
        inventory[i]->displayInfo();
    }
    
    
    string item_name = "Potion";
    cout << "Deleting: " << item_name << endl;
    for(int i = 0; i < inventory.size(); i++) {
        string current = inventory[i]->getName();
        string currentLower = "";
        string itemLower = "";
        for(int j = 0; j < current.size(); j++) {currentLower += tolower(current[j]);}
        for(int k = 0; k < item_name.size(); k++) {itemLower += tolower(item_name[k]);}
        if(itemLower == currentLower) {
            delete inventory[i];
            inventory.erase(inventory.begin() + i);
            break;
        }
    }

    // Display all
    for (int i = 0; i < inventory.size(); i++) {
        inventory[i]->displayInfo();
    }
    

    // Clean up - VERY IMPORTANT!
    for (int i = 0; i < inventory.size(); i++) {
        delete inventory[i];
    }
    inventory.clear();
    
    return 0;
}