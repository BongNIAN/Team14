#include "Character.h" 
#include "ItemManager.h" 
#include "Item.h" 
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
    experience = exp;
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
void Character::visitShop() const {
    std::cout << "Welcome to the shop!\n";
}

// �� ���� Ȯ��
bool Character::isPoison() const {
    return false;
}
