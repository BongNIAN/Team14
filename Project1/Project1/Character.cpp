

#include "Character.h"
#include "ItemManager.h"
#include "item.h"
#include <memory>

// 정적 멤버 초기화
Character* Character::instance = nullptr;

// 생성자
Character::Character(std::string name) : name(name) {
    level = 1;
    maxHealth = 200;
    health = maxHealth;
    attack = 30;
    experience = 0;
    gold = 0;
    itemManager = std::make_shared<ItemManager>();
}

// Singleton 인스턴스 반환
Character* Character::getInstance(std::string name) {
    if (instance == nullptr) {
        instance = new Character(name);
    }
    return instance;
}

// Singleton 인스턴스 제거
void Character::destroyInstance() {
    delete instance;
    instance = nullptr;
}

// 소멸자
Character::~Character() {
    itemManager.reset();
}

// 캐릭터 상태 출력
void Character::displayStatus() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "Health: " << health << "/" << maxHealth << std::endl;
    std::cout << "Attack: " << attack << std::endl;
    std::cout << "Experience: " << experience << std::endl;
    std::cout << "Gold: " << gold << std::endl;
}

// 레벨 업
void Character::levelUp() {
    if (level < maxLevel) {
    maxHealth += level * 20;
    attack += level * 5;
    level++;
    health = maxHealth;
}
}

// 체력 증가
void Character::increaseHP(int amount) {
    health = std::min(health + amount, maxHealth);
}

// 데미지 처리
void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

// 공격력 증가
void Character::increaseATK(int amount) {
    attack += amount;
}

// Getter 메서드들
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

// 골드 조작 메서드들
void Character::decreaseGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
    }
    else {
        std::cout << "Not enough gold.\n";
    }
}

// 골드 증가
void Character::increaseGold(int amount) {
    gold += amount;
}

// 아이템 관리 메서드들
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

// 상점 방문
void Character::visitShop() const {
    std::cout << "Welcome to the shop!\n";
}

// 독 상태 확인
bool Character::isPoison() const {
    return false;
}
