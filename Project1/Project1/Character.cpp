#include "Character.h"
#include "ItemManager.h"
#include <iostream>
#include <algorithm>

Character* Character::instance = nullptr;

Character::Character(std::string Name) : name(Name), itemManager(new ItemManager) {
    level = 1;
    maxHealth = 200;
    health = maxHealth;
    attack = 30;
    experience = 0;
    gold = 0;
}

Character* Character::getinstance(std::string name) {
    if (instance == nullptr) {
        instance = new Character(name);
    }
    return instance;
}

void Character::displayStatus() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "Health: " << health << "/" << maxHealth << std::endl;
    std::cout << "Attack: " << attack << std::endl;
    std::cout << "Experience: " << experience << std::endl;
    std::cout << "Gold: " << gold << std::endl;
}

void Character::levelUp() {
    maxHealth += level * 20;
    attack += level * 5;
    level++;
    health = maxHealth;
}

void Character::increaseHP(int amount) {
    health = std::min(health + amount, maxHealth);
}

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

void Character::increaseATK(int amount) {
    attack += amount;
}

int Character::getLevel() {
    return level;
}

int Character::getHP() {
    return health;
}

int Character::getATK() {
    return attack;
}

// °ñµå °¨¼Ò
void Character::decreaseGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
    }
    else {
        std::cout << "Not enough gold.\n";
    }
}

// °ñµå Áõ°¡
void Character::increaseGold(int amount) {
    gold += amount;
}

// °ñµå ¹ÝÈ¯
int Character::getGold() const {
    return gold;
}

void Character::addItem(Item* newItem, int quantity) {
    itemManager->addItem(newItem, quantity);
}

void Character::useItem(int index) {
    itemManager->useItem(index, this);
}

void Character::displayInventory() {
    itemManager->displayInventory();
}

void Character::deleteItem(Item* itemToDelete) {
    itemManager->deleteItem(itemToDelete);
}

void Character::visitShop() {
    std::cout << "welcome to the shop" << std::endl;
}

bool Character::isPoison() {
    return false;
}
