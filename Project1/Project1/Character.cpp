

#include "Character.h"
#include "ItemManager.h"
#include "item.h"
#include <memory>

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
    itemManager.reset();
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
}

// ������ ó��
void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

// ���ݷ� ����
void Character::increaseATK(int amount) {
    attack += amount;
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
void Character::visitShop() const {
    std::cout << "Welcome to the shop!\n";
}

// �� ���� Ȯ��
bool Character::isPoison() const {
    return false;
}
