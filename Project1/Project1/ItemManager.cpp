#include "ItemManager.h"
#include "Character.h"
#include <iostream>
#include <algorithm>

void ItemManager::addItem(Item* newItem, int quantity) {
    if (itemQuantities.find(newItem) != itemQuantities.end()) {
        itemQuantities[newItem] += quantity;
    }
    else {
        inventory.push_back(newItem);
        itemQuantities[newItem] = quantity;
    }
}

void ItemManager::useItem(int index, Character* character) {
    if (index < 0 || index >= inventory.size()) {
        std::cout << "아이템 사용할 수 없음." << std::endl;
        return;
    }

    Item* itemToUse = inventory[index];
    itemToUse->use(character);
    itemQuantities[itemToUse]--;
    if (itemQuantities[itemToUse] <= 0) {
        delete itemToUse;
        inventory.erase(inventory.begin() + index);
        itemQuantities.erase(itemToUse);
    }
}

void ItemManager::deleteItem(Item* itemToDelete) {
    auto it = itemQuantities.find(itemToDelete);
    if (it != itemQuantities.end()) {
        if (it->second > 1) {
            it->second--;
        }
        else {
            inventory.erase(std::remove(inventory.begin(), inventory.end(), itemToDelete), inventory.end());
            itemQuantities.erase(it);
            delete itemToDelete;
        }
    }
}

void ItemManager::displayInventory() {
    std::cout << "현재 인벤토리:" << std::endl;
    for (int i = 0; i < inventory.size(); ++i) {
        Item* item = inventory[i];
        std::cout << i + 1 << ": " << item->getName() << " x" << itemQuantities[item] << std::endl;
    }
}
