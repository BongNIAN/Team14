// ItemManager.h
#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H


#include <vector>
#include <map>
#include <memory>
#include "item.h"

class Item;
class Character; // ���� ����


class ItemManager {
private:
    std::vector<std::shared_ptr<Item>> inventory;           // �κ��丮 ����
    std::map<std::shared_ptr<Item>, int, ItemCompare> itemQuantities;    // �����۰� ���� ����

public:
    void addItem(std::shared_ptr<Item> newItem, int quantity = 1);
    void useItem(int index, Character* character);
    void displayInventory() const;
    void deleteItem(std::shared_ptr<Item> itemToDelete, int quantity);
    int getItemQuantity(std::shared_ptr<Item> item) const;
    int getItemSize();
    std::vector<std::shared_ptr<Item>> getInventory();
};


#endif
