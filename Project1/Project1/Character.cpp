#include "Character.h" 
#include "ItemManager.h" 
#include "Item.h"
#include "Shop.h"
#include "print.h"
#include <iostream> 
#include <algorithm> 

// ���� ��� �ʱ�ȭ
Character* Character::instance = nullptr;

// ������
Character::Character(std::string name) : name(name) {
    level = 1;
    maxHealth = 200;
    health = maxHealth;
    attack = 30;
    experience = 0;
    defense = 0;
    gold = 0;
    battleCount = 0;
    itemManager = std::make_shared<ItemManager>();
    IsPoison = false;
}

// Singleton �ν��Ͻ� ��ȯ
Character* Character::getInstance(std::string name) {
    if (instance == nullptr) {
        instance = new Character(name);
    }
    return instance;
}

// Singleton �ν��Ͻ� ����
void Character::destroyInstance() {
    delete instance;
    instance = nullptr;
}

// �Ҹ���
Character::~Character() {
     
    //HasitemManger 
    if (itemManager) {
        std::cout << "Before delete useCount : " << itemManager.use_count() << std::endl;

        
        itemManager.reset();

        // use_count()�� 0�� �Ǿ����� Ȯ��
        if (itemManager == nullptr) {
            std::cout << "ItemManagerDelete" << std::endl;
        }
        else {
            std::cout << "Error: ItemManager NO RESET " << std::endl;
        }
    }
    
}




// ĳ���� ���� ���
void Character::displayStatus() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Level: " << level << std::endl;
    drawHpBar(health, maxHealth); 
    drawExpBar(experience, 100);
    std::cout << "Attack: " << attack << std::endl;
    std::cout << "Gold: " << gold << std::endl;
    std::cout << "stage " << battleCount << std::endl;
    std::cout << "Defense " << defense << std::endl;
    std::cout << "IsPoison " << IsPoison << std::endl;

}

// ���� ��
void Character::levelUp() {
    if (level < maxLevel) {
    maxHealth += level * 20;
    attack += level * 5;
    level++;
    health = maxHealth;
}
}

// ü�� ����
void Character::increaseHP(int amount) 
{
    health = std::min(health + amount, maxHealth);
}

// defense getter
int Character::getDefense() const {
    return defense;
}

// defense Setter
void Character::setDefense(int amount) {
    if (amount < 0) {
        std::cout << "������ ������ �� �� �����ϴ�.\n";
        defense = 0; // ������ �ּ� 0���� ����
    }
    else {
        defense = amount;
    }
}


// ������ ó��
void Character::takeDamage(int damage) {

    health -= damage;
    //�̺κ� �����ε� ���������°Ͷ����� �ȵɰͰ����� 
    if (health < 0) 
    {
        health = 0;
        std::cout << "im character , Player Death" << std::endl;
    }
}

// ���ݷ� ����
void Character::increaseATK(int amount) {
    attack += amount;
}
// �߰�: ����ġ set
void Character::setEXP(int exp) {
    if (experience + exp >= 100)
    {
        levelUp();
        experience +=  (exp - 100);
    }
    else
    {
        experience += exp;
    }
}


// Getter �޼����
int Character::getLevel() const {
    return level;
}

int Character::getHP() const {
    return health;
}

int Character::getATK() const {
    return attack;
}

int Character::getGold() const {
    return gold;
}
// �߰�: ����ġ ��ȯ
int Character::getEXP() const {
    return experience;
}
// ���� �߰� : MaxHp ��ȯ�޼���
int Character::getMaxHp() const {
    return maxHealth;
}

//�߰�: �÷��̾� �κ��丮 ��ȯ 
std::vector<std::shared_ptr<Item>> Character::getInventory() const{
    return itemManager->getInventory();
}

//�߰� : ��Ʋī��Ʈ(�������� ������ �ʿ�)
int Character::getBattleCount() const {
    return battleCount;
}

void Character::increasebattleCount() {
    battleCount++;
}


// ��� ���� �޼����
void Character::decreaseGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
    }
    else {
        std::cout << "Not enough gold.\n";
    }
}

// ��� ����
void Character::increaseGold(int amount) {
    gold += amount;
}

// ������ ���� �޼����
void Character::addItem(std::shared_ptr<Item> newItem, int quantity) {
    itemManager->addItem(newItem, quantity);
}

void Character::useItem(int index) {
    itemManager->useItem(index, this);
}

void Character::displayInventory() const {
    itemManager->displayInventory();
}

void Character::deleteItem(std::shared_ptr<Item> itemToDelete, int quantity) {
    itemManager->deleteItem(itemToDelete, quantity);
}

int Character::getItemQuantity(std::shared_ptr<Item> item) const {
    return itemManager->getItemQuantity(item);
}

// ���� �湮
void Character::visitShop() {
    Shop shop;  // ���� �ν��Ͻ� ����
    bool inShop = true;
    int choice;

    while (inShop) {
        // �޴� ǥ�� (���� �������� ���� ���� �ÿ��� ǥ��)
        std::cout << "\n==== ������ ���� ���� ȯ���մϴ�! ====\n";
        std::cout << "1. ������ ����\n";
        std::cout << "2. ������ �Ǹ�\n";
        std::cout << "3. ���� ������\n";
        std::cout << "��ȣ�� �����ϼ���: ";
        std::cin >> choice;

        switch (choice) {
            // ������ ���� ó��
        case 1: {
            shop.displayItems();  // �������� ���� ������ ������ ǥ��
            std::cout << "������ ������ ��ȣ�� �Է��ϼ���: ";
            int buyChoice;
            std::cin >> buyChoice;
            std::cout << "������ �������� ������ �Է��ϼ���: ";
            int quantity;
            std::cin >> quantity;
            if (!shop.buyItem(*this, buyChoice, quantity)) {// ������ ������ ����
                std::cout << "���ſ� �����߽��ϴ�.\n";
            }
            std::cout << "===============================" << std::endl;
            std::cout << "�� ���: " << gold << std::endl;
            std::cout << " " << std::endl;
            std::cout << "�� ����: " << getItemQuantity(std::make_shared<HealthPotion>()) << std::endl;
            std::cout << " " << std::endl;
            std::cout << "�� ����: " << getItemQuantity(std::make_shared<AttackBoost>()) << std::endl;
            std::cout << "===============================" << std::endl;
            break;
        }//
              // ������ �Ǹ� ó��
        case 2: {
            std::cout << "����� �κ��丮:\n";
            displayInventory();  // �κ��丮 ������ ǥ��
            if (!itemManager->getItemSize())
            {
                std::cout << "�κ��丮�� ����ֽ��ϴ� " << std::endl;
                break;
            }
            std::cout << "�Ǹ��� ������ ��ȣ�� �Է��ϼ���: ";
            int sellChoice;
            std::cin >> sellChoice;
            std::cout << "�Ǹ��� �������� ������ �Է��ϼ���: ";
            int quantity;
            std::cin >> quantity;
            if (!shop.sellItem(*this, sellChoice, quantity)) {// ������ ������ �Ǹ�
                std::cout << "�Ǹſ� �����߽��ϴ�.\n";
            }
            break;
        }
              // ���� ������
        case 3:
            inShop = false;
            std::cout << "������ �����̽��ϴ�. �����մϴ�!\n";
            break;
        default:
            std::cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���.\n";
            break;
        }
    }
}

// �� ���� Ȯ��
bool Character::isPoison() const {
    return IsPoison;
}

void Character::setPoison(bool state)
{
    IsPoison = state;
}