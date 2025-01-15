#include "ItemManager.h"
#include "item.h"
#include "Character.h"
#include <iostream>


// 아이템 추가
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

// 아이템 사용
//이부분을 string기반으로 받을까 말까
void ItemManager::useItem(int index, Character* character) {
    if (index >= 0 && index < inventory.size()) {
        std::shared_ptr<Item> item = inventory[index-1]; // 인덱스 수정 완료
        item->use(character); // 아이템 사용 로직
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


// 아이템 삭제
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