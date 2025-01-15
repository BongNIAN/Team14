#include "Character.h" 
#include "ItemManager.h" 
#include "Item.h"
#include "Shop.h"
#include "Observer.h" 
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
    gold = 0;
    itemManager = std::make_shared<ItemManager>();
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

void Character::Attach(const std::shared_ptr<IPlayerObserver>& observer) {
    observers.push_back(observer); // �������� ����Ʈ�� �߰�
}

void Character::Detach(const std::shared_ptr<IPlayerObserver>& observer) {
    // �������� ����Ʈ���� ����
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Character::Notify() {
    // ��� ���������� ���� ���¸� �˸�
    for (const auto& observer : observers) {
        PlayerHp hp = { health, maxHealth }; 
        observer->UpdatePlayer(hp);          // �������� UpdatePlayer ȣ��
    }
}



// ĳ���� ���� ���
void Character::displayStatus() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "Health: " << health << "/" << maxHealth << std::endl;
    std::cout << "Attack: " << attack << std::endl;
    std::cout << "Experience: " << experience << std::endl;
    std::cout << "Gold: " << gold << std::endl;
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
void Character::increaseHP(int amount) {
    health = std::min(health + amount, maxHealth);
    PlayerHp hpp = { health,maxHealth };
    Character::Notify();
}

// ������ ó��
void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
    Character::Notify();
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

void Character::deleteItem(std::shared_ptr<Item> itemToDelete) {
    itemManager->deleteItem(itemToDelete);
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
            shop.buyItem(*this, buyChoice);  // ������ ������ ����
            break;
        }
              // ������ �Ǹ� ó��
        case 2: {
            std::cout << "����� �κ��丮:\n";
            displayInventory();  // �κ��丮 ������ ǥ��

            std::cout << "�Ǹ��� ������ ��ȣ�� �Է��ϼ���: ";
            int sellChoice;
            std::cin >> sellChoice;
            shop.sellItem(*this, sellChoice);  // ������ ������ �Ǹ�
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
    return false;
}
