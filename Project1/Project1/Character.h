// Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <map>
#include <memory>



// ���� ����
class ItemManager;
class Item;

class Character {
private:
    static Character* instance; // Singleton �ν��Ͻ�
    std::string name;           // ĳ���� �̸�
    int level;                  // ���� ����
    int maxLevel = 10;          // �ִ� ����
    int health;                 // ���� ü��
    int maxHealth;              // �ִ� ü��
    int attack;                 // ���ݷ�
    int experience;             // ���� ����ġ
    int maxExp = 100;           // �ִ� ����ġ
    int gold;                   // ��� ������
    int statePoison = false;
    std::shared_ptr<ItemManager> itemManager; // ������ �����ڸ� ���� ������

    // Private constructor for singleton
    Character(std::string name);

public:
    // ������ ���� �����ڿ� ���� ������
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;

    // Singleton �ν��Ͻ� ��ȯ
    static Character* getInstance(std::string name = "DefaultCharacter");
    static void destroyInstance(); // Singleton �ν��Ͻ� ����

    // ĳ���� ���� ���
    void displayStatus() const;

    // ĳ���� ���
    void levelUp();
    void increaseHP(int amount);
    void takeDamage(int damage);
    void increaseATK(int amount);

    // Getter
    int getLevel() const;
    int getHP() const;
    int getATK() const;
    int getGold() const;

    // ��� ����
    void decreaseGold(int amount);
    void increaseGold(int amount);

    // ������ ����
    void addItem(std::shared_ptr<Item> newItem, int quantity = 1);
    void useItem(int index);
    void displayInventory() const;
    void deleteItem(std::shared_ptr<Item> itemToDelete);

    // ���� �湮
    void visitShop() const;

    // �� ���� Ȯ��
    bool isPoison() const;

    // Destructor
    ~Character();
};

#endif
