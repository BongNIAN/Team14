#include "Character.h" 
#include "ItemManager.h" 
#include "Item.h"
#include "Shop.h"
#include "Observer.h" 
#include "stageManager.h"
#include "print.h"
#include <iostream> 
#include <algorithm> 

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
    battleCount = 0;
    itemManager = std::make_shared<ItemManager>();
    IsPoison = false;
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
     
    //HasitemManger 
    if (itemManager) {
        std::cout << "Before delete useCount : " << itemManager.use_count() << std::endl;

        
        itemManager.reset();

        // use_count()가 0이 되었는지 확인
        if (itemManager == nullptr) {
            std::cout << "ItemManagerDelete" << std::endl;
        }
        else {
            std::cout << "Error: ItemManager NO RESET " << std::endl;
        }
    }
    
}

void Character::Attach(const std::shared_ptr<IPlayerObserver>& observer) {
    observers.push_back(observer); // 옵저버를 리스트에 추가
}

void Character::Detach(const std::shared_ptr<IPlayerObserver>& observer) {
    // 옵저버를 리스트에서 제거
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Character::Notify() {
    // 모든 옵저버에게 현재 상태를 알림
    for (const auto& observer : observers) {
        PlayerHp hp = { health, maxHealth }; 
        observer->UpdatePlayer(hp);          // 옵저버의 UpdatePlayer 호출
    }
}



// 캐릭터 상태 출력
void Character::displayStatus() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Level: " << level << std::endl;
    drawHpBar(health, maxHealth);
    std::cout << "Attack: " << attack << std::endl;
    drawExpBar(experience, 100);
    std::cout << "Gold: " << gold << std::endl;
    std::cout << "stage " << battleCount << std::endl;
    std::cout << "IsPoison " << IsPoison << std::endl;
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
    PlayerHp hpp = { health,maxHealth };
    Character::Notify();
}

// 데미지 처리
void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
    Character::Notify();
}

// 공격력 증가
void Character::increaseATK(int amount) {
    attack += amount;
}
// 추가: 경험치 set
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
// 추가: 경험치 반환
int Character::getEXP() const {
    return experience;
}
// 원명 추가 : MaxHp 반환메서드
int Character::getMaxHp() const {
    return maxHealth;
}

//추가: 플레이어 인벤토리 반환 
std::vector<std::shared_ptr<Item>> Character::getInventory() const{
    return itemManager->getInventory();
}

//추가 : 배틀카운트(스테이지 관리시 필요)
int Character::getBattleCount() const {
    return battleCount;
}

void Character::increasebattleCount() {
    battleCount++;
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

void Character::deleteItem(std::shared_ptr<Item> itemToDelete, int quantity) {
    itemManager->deleteItem(itemToDelete, quantity);
}

int Character::getItemQuantity(std::shared_ptr<Item> item) const {
    return itemManager->getItemQuantity(item);
}

// 상점 방문
void Character::visitShop() {
    Shop shop;  // 상점 인스턴스 생성
    bool inShop = true;
    int choice;

    while (inShop) {
        // 메뉴 표시 (상점 아이템은 구매 선택 시에만 표시)
        std::cout << "\n==== 상점에 오신 것을 환영합니다! ====\n";
        std::cout << "1. 아이템 구매\n";
        std::cout << "2. 아이템 판매\n";
        std::cout << "3. 상점 나가기\n";
        std::cout << "번호를 선택하세요: ";
        std::cin >> choice;

        switch (choice) {
            // 아이템 구매 처리
        case 1: {
            shop.displayItems();  // 상점에서 구매 가능한 아이템 표시
            std::cout << "구매할 아이템 번호를 입력하세요: ";
            int buyChoice;
            std::cin >> buyChoice;
            std::cout << "구매할 아이템의 수량을 입력하세요: ";
            int quantity;
            std::cin >> quantity;
            if (!shop.buyItem(*this, buyChoice, quantity)) {// 선택한 아이템 구매
                std::cout << "구매에 실패했습니다.\n";
            }
            std::cout << "===============================" << std::endl;
            std::cout << "ⓖ 골드: " << gold << std::endl;
            std::cout << " " << std::endl;
            std::cout << "♥ 물약: " << getItemQuantity(std::make_shared<HealthPotion>()) << std::endl;
            std::cout << " " << std::endl;
            std::cout << "↑ 공증: " << getItemQuantity(std::make_shared<AttackBoost>()) << std::endl;
            std::cout << "===============================" << std::endl;
            break;
        }//
              // 아이템 판매 처리
        case 2: {
            std::cout << "당신의 인벤토리:\n";
            displayInventory();  // 인벤토리 아이템 표시
            if (!itemManager->getItemSize())
            {
                std::cout << "인벤토리가 비어있습니다 " << std::endl;
                break;
            }
            std::cout << "판매할 아이템 번호를 입력하세요: ";
            int sellChoice;
            std::cin >> sellChoice;
            std::cout << "판매할 아이템의 수량을 입력하세요: ";
            int quantity;
            std::cin >> quantity;
            if (!shop.sellItem(*this, sellChoice, quantity)) {// 선택한 아이템 판매
                std::cout << "판매에 실패했습니다.\n";
            }
            break;
        }
              // 상점 나가기
        case 3:
            inShop = false;
            std::cout << "상점을 떠나셨습니다. 감사합니다!\n";
            break;
        default:
            std::cout << "잘못된 선택입니다. 다시 시도해주세요.\n";
            break;
        }
    }
}

// 독 상태 확인
bool Character::isPoison() const {
    return IsPoison;
}

void Character::setPoison(bool state)
{
    IsPoison = state;
}