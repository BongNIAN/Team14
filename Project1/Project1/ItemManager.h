#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <vector>
#include <map>
#include "Item.h" // Item 헤더 포함

class ItemManager {
private:
    std::vector<Item*> inventory;
    std::map<Item*, int> itemQuantities;

public:
    void addItem(Item* newItem, int quantity = 1);
    void useItem(int index, class Character* character);
    void displayInventory();
    void deleteItem(Item* itemToDelete);
};

#endif
