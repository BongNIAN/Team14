#include "Shop.h" 
#include "Character.h" 
#include "Item.h" 
#include <iostream> 


Shop::Shop() {
    // �������� �Ǹ��ϴ� ������ ��� �ʱ�ȭ
    shopItems.push_back(std::make_shared<HealthPotion>());
    shopItems.push_back(std::make_shared<AttackBoost>());
   
}

Shop::~Shop() {
    // ����Ʈ ������ ���
}

void Shop::displayItems() const {
    std::cout << "\n���� ������ ���:\n";
    for (size_t i = 0; i < shopItems.size(); ++i) {
        auto& item = shopItems[i];
        std::cout << i + 1 << ". " << item->getName()
            << " (����: " << item->getPrice() << " Gold)\n";
    }

}

bool Shop::buyItem(Character& character, size_t itemIndex) {
    if (itemIndex < 1 || itemIndex > shopItems.size()) {
        std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
        return false;
    }

    auto& item = shopItems[itemIndex - 1];

    if (character.getGold() < item->getPrice()) {
        std::cout << "��尡 �����մϴ�!\n";
        return false;
    }

    // ���� ó��
    character.decreaseGold(item->getPrice());
    character.addItem(item, 1);

    std::cout << item->getName() << "��(��) �����ϼ̽��ϴ�.\n";
    return true;
}

bool Shop::sellItem(Character& character, size_t inventoryIndex) {
    auto inventory = character.getInventory();

    if (inventoryIndex < 1 || inventoryIndex > inventory.size()) {
        std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
        return false;
    }

    auto item = inventory[inventoryIndex - 1];
    int sellPrice = static_cast<int>(item->getPrice() * 0.6); // �Ǹ� ������ ������ 60%

    // �Ǹ� ó��
    character.increaseGold(sellPrice);

    character.deleteItem(item);

    std::cout << item->getName() << "��(��) �Ǹ��ϼ̽��ϴ�. �Ǹ� �ݾ�: " << sellPrice << " Gold\n";
    
    return true;
}

std::vector<std::shared_ptr<Item>> Shop::getShopItems() const {
    return shopItems;
}
