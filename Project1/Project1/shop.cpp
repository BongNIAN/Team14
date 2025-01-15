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

bool Shop::buyItem(Character& character, size_t itemIndex, int quantity) {
    if (itemIndex < 1 || itemIndex > shopItems.size()) {
        std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
        return false;
    }

    if (quantity <= 0) {
        std::cout << "������ 1 �̻��̾�� �մϴ�.\n";
        return false;
    }

    auto& item = shopItems[itemIndex - 1];
    int totalPrice = item->getPrice() * quantity;

    if (character.getGold() < totalPrice) {
        std::cout << "��尡 �����մϴ�! (�ʿ� ���: " << totalPrice << ")\n";
        return false;
    }

    // ���� ó��
    character.decreaseGold(totalPrice);  // �� ���ݸ�ŭ ��� ����
    character.addItem(item, quantity);  // ������ �����۰� ���� �߰�

    std::cout << item->getName() << "��(��) " << quantity << "�� �����ϼ̽��ϴ�.\n";
    return true;
}

bool Shop::sellItem(Character& character, size_t inventoryIndex, int quantity) {
    auto inventory = character.getInventory();

    if (inventoryIndex < 1 || inventoryIndex > inventory.size()) {
        std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
        return false;
    }

    if (quantity <= 0) {
        std::cout << "������ 1 �̻��̾�� �մϴ�.\n";
        return false;
    }

    auto item = inventory[inventoryIndex - 1];
    int currentQuantity = character.getItemQuantity(item);

    if (quantity > currentQuantity) {
        std::cout << "�κ��丮�� ����� ������ �����ϴ�.\n";
        return false;
    }

    int sellPrice = static_cast<int>(item->getPrice() * 0.6*quantity); // �Ǹ� ������ ������ 60%

    // �Ǹ� ó��
    character.increaseGold(sellPrice);
    character.deleteItem(item, quantity);

    std::cout << item->getName() << "��(��) " << quantity << "�� �Ǹ��ϼ̽��ϴ�. �Ǹ� �ݾ�: "<< sellPrice << " Gold\n";
    return true;
}

std::vector<std::shared_ptr<Item>> Shop::getShopItems() const {
    return shopItems;
}
