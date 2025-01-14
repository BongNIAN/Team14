// ItemManager.cpp
#include "ItemManager.h"
#include "item.h"
#include "Character.h"



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
void ItemManager::useItem(int index, Character* character) {
    if (index >= 0 && index < inventory.size()) {
        std::shared_ptr<Item> item = inventory[index];
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


// �ٲ۰��� ���� item* �� shared�� ����Ͽ���,
// displayInventory �� map���� ������ϸ� �ٲ���ϴ�.
// 
// üũ �ٶ��ϴ� ��ȯ�� ! Memo->������ ������Ͽ� ItemCompare ���� �޾Ƴ���
// ������ �Ŵ��� ������Ͽ� map���� �ٲ�����ϴ� !
// 
// �����̶� �̾߱⸦ �ߴµ� , ����Ʈ �����͸� Ȱ���ϴ� ������ �ϴ°� �����ϴ��󱸿� 
// �׷��� ��ȯ�Ե� Ȥ���� ������ �ɱ� �ؼ� ����Ʈ �����ͷ� �ٲ�����ϴ�
// ���νø� �ٽ� �ǵ����ð�, �̾߱⸸���ּ��� ! 
// 
// �ش� �޼��带 �ٲ����� : 
// 
// map�� �񱳸� �Ҷ�, Ű ���� ���� �񱳸� �ϰԵǴµ�
// �װ� map���� ó���� ������ shared_ptr<Item>�Դϴ�
// 
// ���� �� ������ ���� 
// map <shared_ptr <Item> , int > �� �����ϰ� �Ǹ�
// item shared_ptr�� Ű ���� �Ǿ� add�Լ��� �����ϰ� �˴ϴ�.
// 
// add�Լ� ������ ������ �񱳸� �ϰ� �ɶ�, shared_ptr�� �񱳸��ϴµ�
// �̴� �������̱� ������ �ּҷ� �񱳸� �ϰԵ˴ϴ�
// ���� ���� ������ �̸��� ���͵� , �ٸ� ������ ����ع����ϴ�
// 
// ������� ��°��� ������ ���� ������ �˴ϴ�.
// Heal X 1
// Heal X 1
// Heal X 1
// BOOST X1
// BOOST X1
// BOOST X1
// BOOST X1
// 
// �׷��� MAP�� �����Ҷ� 3��° ���ڷ� ���� ���ϰ����ϴ� Ű ���� ����־����ϴ�.
// �ش� �Լ��� item.h �� item.cpp�� ������
// �ش� �Լ��� �����ϴ� ������ ������ �����ϴ�.
// 
// ���� ������ ù��° �������� getName�� ������ �������� getName �� ��Ʈ�� �񱳸� �ϰԵ˴ϴ�.
// �׷��� ������ �̸��� ���ٸ�  ���Լ��� false�� ��ȯ��
// map�� ���� �������� �߰����� �ʰ�, add�Լ����� �������� ������ �ö󰡰Ե˴ϴ�.
// 
// ���� �������� �̸��� ���� �ʴٸ�, ������������ ���ĵǰ� �س����ϴ�.
// ���������� ���ϽŴٸ�, item.cpp�� �ִ� 

/**
* bool ItemCompare::operator()(const std::shared_ptr<Item>& left, const std::shared_ptr<Item>& right) const {
    // ������ �̸��� �������� ��
    if (left->getName() == right->getName()) {
        return false;
    }

    // �̸��� �ٸ� ��� �������� ��
    return left->getName() > right->getName();
}
�� �Լ����� left->getName() < right-<getName(); ���� �ٲ��ֽø� �˴ϴ�.
*/

// 
// 
// ���� �Լ�  : 
// 
// �κ��丮 ���
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