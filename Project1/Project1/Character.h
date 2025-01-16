#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
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
    int battleCount;            // ���� Ƚ��(�������� ����)
    bool IsPoison;
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
    
    //������ ��� 
 

    // ĳ���� ���� ���
    void displayStatus() const;

    // ĳ���� ���
    void levelUp();
    void increaseHP(int amount);
    void takeDamage(int damage);
    void increaseATK(int amount);
    void setEXP(int exp); //�߰�

    // Getter
    int getLevel() const;
    int getHP() const;
    int getATK() const;
    int getGold() const;
    int getEXP() const; //�߰�
    int getMaxHp() const; // �����߰�
    std::vector<std::shared_ptr<Item>> getInventory() const; 
    
    // ��� ����
    void decreaseGold(int amount);
    void increaseGold(int amount);
    
    // �������� ����
    void increasebattleCount();
    int getBattleCount() const;


    // ������ ����
    void addItem(std::shared_ptr<Item> newItem, int quantity = 1);
    void useItem(int index);
    void displayInventory() const;
    void deleteItem(std::shared_ptr<Item> itemToDelete, int quantity);
    int getItemQuantity(std::shared_ptr<Item> item) const;
   

    // ���� �湮
    void visitShop();

    // �� ���� Ȯ��
    bool isPoison() const;
    void setPoison(bool state);
    // Destructor
    ~Character();
};

#endif
