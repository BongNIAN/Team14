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
    //if (index >= 0 && index < inventory.size()) {

    //    std::shared_ptr<Item> item = inventory[index-1]; // 인덱스 수정 완료
    //    item->use(character); // 아이템 사용 로직
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
    std::advance(it, index - 1); // Map 인덱스 기반 탐색 

    std::shared_ptr<Item> item = it->first; // 아이템 포인터 가져오기
    int& quantity = it->second;             // 아이템 개수 참조

    // 아이템 사용 로직
    if (item && quantity > 0) {
        item->use(character); // 캐릭터에게 아이템 효과 적용
        quantity--;           // 사용 후 개수 감소

        // 개수가 0이 되면 아이템 삭제
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


// 아이템 삭제 및 수량 감소
void ItemManager::deleteItem(std::shared_ptr<Item> itemToDelete, int quantity) {
    if (quantity <= 0) {
        std::cout << "제거할 수량이 1 이상이어야 합니다.\n";
        return;
    }

    auto it = itemQuantities.find(itemToDelete);
    if (it == itemQuantities.end()) {
        std::cout << "해당 아이템이 인벤토리에 없습니다.\n";
        return;
    }

    if (it->second <= quantity) {
        // 수량이 부족하거나 정확히 일치 -> 아이템 완전히 삭제
        itemQuantities.erase(it);

        // `inventory`에서도 제거
        auto vecIt = std::find(inventory.begin(), inventory.end(), itemToDelete);
        if (vecIt != inventory.end()) {
            inventory.erase(vecIt);
        }

      
    }
    else {
        // 수량 감소
        it->second -= quantity;;
    }
}

int ItemManager::getItemQuantity(std::shared_ptr<Item> item) const {
    auto it = itemQuantities.find(item);
    if (it != itemQuantities.end()) {
        return it->second;  // 현재 수량 반환
    }
    return 0;  // 아이템이 없으면 0 반환
}

std::vector<std::shared_ptr<Item>> ItemManager::getInventory() {
    return inventory;
}