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
    //if (index >= 0 && index < inventory.size()) {

    //    std::shared_ptr<Item> item = inventory[index-1]; // �ε��� ���� �Ϸ�
    //    item->use(character); // ������ ��� ����
    //    itemQuantities[item]--;
    //   
    //    if (itemQuantities[item] <= 0) {
    //        deleteItem(item, 1);
    //    }
    //}
    //else {
    //    std::cout << "Invalid item index.\n";
    //}
    if (index < 1 || index > static_cast<int>(itemQuantities.size())) {
        std::cout << "Invalid item index.\n";
        return;
    }

    
    auto it = itemQuantities.begin();
    std::advance(it, index - 1); // Map �ε��� ��� Ž�� 

    std::shared_ptr<Item> item = it->first; // ������ ������ ��������
    int& quantity = it->second;             // ������ ���� ����

    // ������ ��� ����
    if (item && quantity > 0) {
        item->use(character); // ĳ���Ϳ��� ������ ȿ�� ����
        quantity--;           // ��� �� ���� ����

        // ������ 0�� �Ǹ� ������ ����
        if (quantity <= 0) {
            deleteItem(item, 1);
        }
    }
    else {
        std::cout << "Item not exist or invalid quantity.\n";
    }
}


void ItemManager::displayInventory() const {
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << i + 1 << ". " << inventory[i]->getName() << " x" << itemQuantities.at(inventory[i]) << std::endl;
    }
}


// ������ ���� �� ���� ����
void ItemManager::deleteItem(std::shared_ptr<Item> itemToDelete, int quantity) {
    if (quantity <= 0) {
        std::cout << "������ ������ 1 �̻��̾�� �մϴ�.\n";
        return;
    }

    auto it = itemQuantities.find(itemToDelete);
    if (it == itemQuantities.end()) {
        std::cout << "�ش� �������� �κ��丮�� �����ϴ�.\n";
        return;
    }

    if (it->second <= quantity) {
        // ������ �����ϰų� ��Ȯ�� ��ġ -> ������ ������ ����
        itemQuantities.erase(it);

        // `inventory`������ ����
        auto vecIt = std::find(inventory.begin(), inventory.end(), itemToDelete);
        if (vecIt != inventory.end()) {
            inventory.erase(vecIt);
        }

      
    }
    else {
        // ���� ����
        it->second -= quantity;;
    }
}

int ItemManager::getItemQuantity(std::shared_ptr<Item> item) const {
    auto it = itemQuantities.find(item);
    if (it != itemQuantities.end()) {
        return it->second;  // ���� ���� ��ȯ
    }
    return 0;  // �������� ������ 0 ��ȯ
}

std::vector<std::shared_ptr<Item>> ItemManager::getInventory() {
    return inventory;
}