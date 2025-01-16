#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <memory>




// 전방 선언
class ItemManager;
class Item;


class Character {
private:
    static Character* instance; // Singleton 인스턴스
    std::string name;           // 캐릭터 이름
    int level;                  // 현재 레벨
    int maxLevel = 10;          // 최대 레벨
    int health;                 // 현재 체력
    int maxHealth;              // 최대 체력
    int attack;                 // 공격력
    int experience;             // 현재 경험치
    int maxExp = 100;           // 최대 경험치
    int gold;                   // 골드 소지량
    int battleCount;            // 전투 횟수(스테이지 관리)
    bool IsPoison;
    std::shared_ptr<ItemManager> itemManager; // 아이템 관리자를 위한 포인터
   


    // Private constructor for singleton
    Character(std::string name);

public:
    // 삭제된 복사 생성자와 대입 연산자
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;

    // Singleton 인스턴스 반환
    static Character* getInstance(std::string name = "DefaultCharacter");
    static void destroyInstance(); // Singleton 인스턴스 제거
    
    //옵저버 등록 
 

    // 캐릭터 상태 출력
    void displayStatus() const;

    // 캐릭터 기능
    void levelUp();
    void increaseHP(int amount);
    void takeDamage(int damage);
    void increaseATK(int amount);
    void setEXP(int exp); //추가

    // Getter
    int getLevel() const;
    int getHP() const;
    int getATK() const;
    int getGold() const;
    int getEXP() const; //추가
    int getMaxHp() const; // 원명추가
    std::vector<std::shared_ptr<Item>> getInventory() const; 
    
    // 골드 조작
    void decreaseGold(int amount);
    void increaseGold(int amount);
    
    // 스테이지 관리
    void increasebattleCount();
    int getBattleCount() const;


    // 아이템 관리
    void addItem(std::shared_ptr<Item> newItem, int quantity = 1);
    void useItem(int index);
    void displayInventory() const;
    void deleteItem(std::shared_ptr<Item> itemToDelete, int quantity);
    int getItemQuantity(std::shared_ptr<Item> item) const;
   

    // 상점 방문
    void visitShop();

    // 독 상태 확인
    bool isPoison() const;
    void setPoison(bool state);
    // Destructor
    ~Character();
};

#endif
