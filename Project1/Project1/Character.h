#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <map>
#include "Item.h" // Item 헤더 포함

class ItemManager;

class Character {
private:
    static Character* instance;
    std::string name;
    int level;
    int maxLevel = 10;
    int health;
    int maxHealth;
    int attack;
    int experience;
    int maxExp = 100;
    int gold;

    ItemManager* itemManager; // 아이템 관리자 포인터

protected:
    Character(std::string Name);

public:
    static Character* getinstance(std::string name = "DefaultCharacter");

    void displayStatus();
    void levelUp();
    void increaseHP(int amount);
    void takeDamage(int damage);
    void increaseATK(int amount);
    int getLevel();
    int getHP();
    int getATK();

    void increaseGold(int amount);
    void decreaseGold(int amount);

    void addItem(Item* newItem, int quantity = 1);
    void useItem(int index);
    void displayInventory();
    void deleteItem(Item* itemToDelete);

    void visitShop();
    bool isPoison();
};

#endif
