
#ifndef SHOP_H
#define SHOP_H

#include <vector>
#include <memory>
#include "item.h"
#include "Character.h"

class Shop {
private:
    // ������ �������� �����ϴ� ����
    std::vector<std::shared_ptr<Item>> shopItems;

public:
    Shop();
    ~Shop();

    void displayItems() const; // ������ ������ ��� ���
    bool buyItem(Character& character, size_t itemIndex, int quantity); // ������ ����
    bool sellItem(Character& character, size_t inventoryIndex, int quantity); // ������ �Ǹ�

    // ���� ������ ��� ��ȯ (����� �Ǵ� �ܺ� ������)
    std::vector<std::shared_ptr<Item>> getShopItems() const;
};

#endif
