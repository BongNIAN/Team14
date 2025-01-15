#include "Shop.h" 
#include "Character.h" 
#include "Item.h" 
#include <iostream> 


Shop::Shop() {
    // 상점에서 판매하는 아이템 목록 초기화
    shopItems.push_back(std::make_shared<HealthPotion>());
    shopItems.push_back(std::make_shared<AttackBoost>());
   
}

Shop::~Shop() {
    // 스마트 포인터 사용
}

void Shop::displayItems() const {
    std::cout << "\n상점 아이템 목록:\n";
    for (size_t i = 0; i < shopItems.size(); ++i) {
        auto& item = shopItems[i];
        std::cout << i + 1 << ". " << item->getName()
            << " (가격: " << item->getPrice() << " Gold)\n";
    }

}

bool Shop::buyItem(Character& character, size_t itemIndex, int quantity) {
    if (itemIndex < 1 || itemIndex > shopItems.size()) {
        std::cout << "잘못된 아이템 번호입니다.\n";
        return false;
    }

    if (quantity <= 0) {
        std::cout << "수량은 1 이상이어야 합니다.\n";
        return false;
    }

    auto& item = shopItems[itemIndex - 1];
    int totalPrice = item->getPrice() * quantity;

    if (character.getGold() < totalPrice) {
        std::cout << "골드가 부족합니다! (필요 골드: " << totalPrice << ")\n";
        return false;
    }

    // 구매 처리
    character.decreaseGold(totalPrice);  // 총 가격만큼 골드 차감
    character.addItem(item, quantity);  // 선택한 아이템과 수량 추가

    std::cout << item->getName() << "을(를) " << quantity << "개 구매하셨습니다.\n";
    return true;
}

bool Shop::sellItem(Character& character, size_t inventoryIndex, int quantity) {
    auto inventory = character.getInventory();

    if (inventoryIndex < 1 || inventoryIndex > inventory.size()) {
        std::cout << "잘못된 아이템 번호입니다.\n";
        return false;
    }

    if (quantity <= 0) {
        std::cout << "수량은 1 이상이어야 합니다.\n";
        return false;
    }

    auto item = inventory[inventoryIndex - 1];
    int currentQuantity = character.getItemQuantity(item);

    if (quantity > currentQuantity) {
        std::cout << "인벤토리에 충분한 수량이 없습니다.\n";
        return false;
    }

    int sellPrice = static_cast<int>(item->getPrice() * 0.6*quantity); // 판매 가격은 원가의 60%

    // 판매 처리
    character.increaseGold(sellPrice);
    character.deleteItem(item, quantity);

    std::cout << item->getName() << "을(를) " << quantity << "개 판매하셨습니다. 판매 금액: "<< sellPrice << " Gold\n";
    return true;
}

std::vector<std::shared_ptr<Item>> Shop::getShopItems() const {
    return shopItems;
}
