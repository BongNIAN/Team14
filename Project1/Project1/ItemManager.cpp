// ItemManager.cpp
#include "ItemManager.h"
#include "item.h"
#include "Character.h"



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
void ItemManager::useItem(int index, Character* character) {
    if (index >= 0 && index < inventory.size()) {
        std::shared_ptr<Item> item = inventory[index];
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


// 바꾼것은 오직 item* 을 shared로 사용하였고,
// displayInventory 와 map선언 헤더파일만 바꿨습니다.
// 
// 체크 바랍니다 승환님 ! Memo->아이템 헤더파일에 ItemCompare 조건 달아놨고
// 아이템 매니저 헤더파일에 map형식 바뀌었습니다 !
// 
// 재명님이랑 이야기를 했는데 , 스마트 포인터를 활용하는 연습을 하는게 좋다하더라구요 
// 그래서 승환님도 혹여나 도움이 될까 해서 스마트 포인터로 바꿔놨습니다
// 별로시면 다시 되돌리시고, 이야기만해주세요 ! 
// 
// 해당 메서드를 바꾼이유 : 
// 
// map은 비교를 할때, 키 값을 통해 비교를 하게되는데
// 그게 map에서 처음에 설정한 shared_ptr<Item>입니다
// 
// 예를 들어서 다음과 같이 
// map <shared_ptr <Item> , int > 로 선언하게 되면
// item shared_ptr이 키 값이 되어 add함수를 진행하게 됩니다.
// 
// add함수 내에서 같은지 비교를 하게 될때, shared_ptr로 비교를하는데
// 이는 포인터이기 때문에 주소로 비교를 하게됩니다
// 따라서 같은 아이템 이름이 나와도 , 다른 값으로 취급해버립니다
// 
// 예를들어 출력값이 다음과 같이 나오게 됩니다.
// Heal X 1
// Heal X 1
// Heal X 1
// BOOST X1
// BOOST X1
// BOOST X1
// BOOST X1
// 
// 그래서 MAP을 선언할때 3번째 인자로 제가 비교하고자하는 키 값을 집어넣었습니다.
// 해당 함수는 item.h 및 item.cpp에 있으며
// 해당 함수가 동작하는 원리는 다음과 같습니다.
// 
// 만일 왼쪽의 첫번째 포인터의 getName과 오른쪽 포인터의 getName 즉 스트링 비교를 하게됩니다.
// 그래서 아이템 이름이 같다면  비교함수에 false를 반환해
// map에 같은 아이템이 추가되지 않고, add함수에서 아이템의 수량만 올라가게됩니다.
// 
// 만일 아이템의 이름이 같지 않다면, 오름차순으로 정렬되게 해놨습니다.
// 내림차순을 원하신다면, item.cpp에 있는 

/**
* bool ItemCompare::operator()(const std::shared_ptr<Item>& left, const std::shared_ptr<Item>& right) const {
    // 아이템 이름을 기준으로 비교
    if (left->getName() == right->getName()) {
        return false;
    }

    // 이름이 다를 경우 내림차순 비교
    return left->getName() > right->getName();
}
이 함수에서 left->getName() < right-<getName(); 으로 바꿔주시면 됩니다.
*/

// 
// 
// 원본 함수  : 
// 
// 인벤토리 출력
//void ItemManager::displayInventory() const {
//    for (size_t i = 0; i < inventory.size(); ++i) {
//        std::cout << i + 1 << ". " << inventory[i]->getName() << " x" << itemQuantities.at(inventory[i]) << std::endl;
//    }
//}


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