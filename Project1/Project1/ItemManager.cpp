#include "ItemManager.h"
#include "item.h"
#include "Character.h"
#include <iostream>


// ������ �߰�
void ItemManager::addItem(std::shared_ptr<Item> newItem, int quantity) {
    if (newItem != nullptr) {

        if (itemQuantities.find(newItem) != itemQuantities.end()) {
            itemQuantities[newItem] += quantity;
        }
        else {
            inventory.push_back(newItem);
            itemQuantities[newItem] = quantity;
        }
    }
    else { std::cout << "NewItem is NULL " << std::endl; }

}

// ������ ���
//�̺κ��� string������� ������ ����
void ItemManager::useItem(int index, Character* character) {
    if (index >= 0 && index < inventory.size()) {
        std::shared_ptr<Item> item = inventory[index-1]; // �ε��� ���� �Ϸ�
        item->use(character); // ������ ��� ����
        itemQuantities[item]--;
        if (itemQuantities[item] <= 0) {
            deleteItem(item);
        }
    }
    else {
        std::cout << "Invalid item index.\n";
    }
}


void ItemManager::displayInventory() const {
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << i + 1 << ". " << inventory[i]->getName() << " x" << itemQuantities.at(inventory[i]) << std::endl;
    }
}


// ������ ����
void ItemManager::deleteItem(std::shared_ptr<Item> itemToDelete) {
    auto it = std::find(inventory.begin(), inventory.end(), itemToDelete);
    if (it != inventory.end()) {
        inventory.erase(it);
        itemQuantities.erase(itemToDelete);

    }
}

std::vector<std::shared_ptr<Item>> ItemManager::getInventory() {
    return inventory;
}