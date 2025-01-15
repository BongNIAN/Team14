
#ifndef SHOP_H
#define SHOP_H

#include <vector>
#include <memory>
#include "item.h"
#include "Character.h"

class Shop {
private:
    // 상점의 아이템을 저장하는 벡터
    std::vector<std::shared_ptr<Item>> shopItems;

public:
    Shop();
    ~Shop();

    void displayItems() const; // 상점의 아이템 목록 출력
    bool buyItem(Character& character, size_t itemIndex, int quantity); // 아이템 구매
    bool sellItem(Character& character, size_t inventoryIndex, int quantity); // 아이템 판매

    // 상점 아이템 목록 반환 (디버깅 또는 외부 참조용)
    std::vector<std::shared_ptr<Item>> getShopItems() const;
};

#endif
