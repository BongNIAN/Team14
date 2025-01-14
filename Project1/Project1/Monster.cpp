#include "monster.h"
#include "item.h" 
#include "random.h"
#include <iostream>

using namespace std;


// Goblin Implementation
Goblin::Goblin(int level) {
    Name = "Goblin";
    Health = level * GenerateRandom(20, 30);
    Attack = level * GenerateRandom(5, 10);
}

string Goblin::GetName() const {
    return Name;
}

int Goblin::GetHealth() const {
    return Health;
}

int Goblin::GetAttack() const {
    return Attack;
}

void Goblin::TakeDamage(int damage) {
    Health -= damage;
    cout << "Goblin took " << damage << " damage. Remaining health: " << Health << endl;
}

shared_ptr<Item> Goblin::DropItem() {
    if (IsCreateEvent(30)) {
        if (IsCreateEvent(50)) {
            return make_shared<HealthPotion>();
        }
        else {
            return make_shared<AttackBoost>();
        }
    }
    cout << "I am Goblin, No Drop." << endl;
    return nullptr;
}

// Troll Implementation
Troll::Troll(int level) {
    Name = "Troll";
    Health = level * GenerateRandom(20, 30);
    Attack = level * GenerateRandom(5, 10);
}

string Troll::GetName() const {
    return Name;
}

int Troll::GetHealth() const {
    return Health;
}

int Troll::GetAttack() const {
    return Attack;
}

void Troll::TakeDamage(int damage) {
    Health -= damage;
    cout << "Troll took " << damage << " damage. Remaining health: " << Health << endl;
}

shared_ptr<Item> Troll::DropItem() {
    if (IsCreateEvent(30)) {
        if (IsCreateEvent(50)) {
            return make_shared<HealthPotion>();
        }
        else {
            return make_shared<AttackBoost>();
        }
    }
    cout << "I am Troll, No Drop." << endl;
    return nullptr;
}

// Orc Implementation
Orc::Orc(int level) {
    Name = "Orc";
    Health = level * GenerateRandom(20, 30);
    Attack = level * GenerateRandom(5, 10);
}

string Orc::GetName() const {
    return Name;
}

int Orc::GetHealth() const {
    return Health;
}

int Orc::GetAttack() const {
    return Attack;
}

void Orc::TakeDamage(int damage) {
    Health -= damage;
    cout << "Orc took " << damage << " damage. Remaining health: " << Health << endl;
}

shared_ptr<Item> Orc::DropItem() {
    if (IsCreateEvent(30)) {
        if (IsCreateEvent(50)) {
            return make_shared<HealthPotion>();
        }
        else {
            return make_shared<AttackBoost>();
        }
    }
    cout << "I am Orc, No Drop." << endl;
    return nullptr;
}

// MonsterDecorator Implementation
MonsterDecorator::MonsterDecorator(shared_ptr<Monster> m) : monster(move(m)) {}

MonsterDecorator::~MonsterDecorator() {
    cout << " byebyeDecorator" << endl;
}

string MonsterDecorator::GetName() const {
    return monster->GetName();
}

int MonsterDecorator::GetHealth() const {
    return monster->GetHealth();
}

int MonsterDecorator::GetAttack() const {
    return monster->GetAttack();
}

void MonsterDecorator::TakeDamage(int damage) {
    monster->TakeDamage(damage);
}

shared_ptr<Item> MonsterDecorator::DropItem() {
    return monster->DropItem();
}

// BossMonster Implementation
BossMonster::BossMonster(shared_ptr<Monster> m) : MonsterDecorator(move(m)) {
    Name = "Boss" + monster->GetName();
    Attack = static_cast<int>(monster->GetAttack() * 1.5);
    Health = static_cast<int>(monster->GetHealth() * 1.5);
}

string BossMonster::GetName() const {
    return Name;
}

int BossMonster::GetHealth() const {
    return Health;
}

int BossMonster::GetAttack() const {
    return Attack;
}

void BossMonster::TakeDamage(int damage) {
    Health -= damage;
    cout << "Boss took " << damage << " damage. Remaining health: " << Health << endl;
}

shared_ptr<Item> BossMonster::DropItem() {
    if (IsCreateEvent(10)) {
        cout << "QuestItem" << endl;
        return make_shared<ItemForQuest>();
    }
    else {
        if (IsCreateEvent(50)) {
            cout << "HealthPotion" << endl;
            return make_shared<HealthPotion>();
        }
        if (IsCreateEvent(40)) {
            cout << "AttackBoost" << endl;
            return make_shared<AttackBoost>();
        }
    }
    cout << "I am Boss, No Drop." << endl;
    return nullptr;
}

// PoisonMonster Implementation
PoisonMonster::PoisonMonster(shared_ptr<Monster> m) : MonsterDecorator(move(m)) {
    Name = "Poison" + monster->GetName();
    Attack = monster->GetAttack();
    Health = monster->GetHealth();
}

string PoisonMonster::GetName() const {
    return Name;
}

int PoisonMonster::GetHealth() const {
    return Health;
}

int PoisonMonster::GetAttack() const {
    if (IsCreateEvent(10)) {
        return Attack + 1;
    }
    return Attack;
}

void PoisonMonster::TakeDamage(int damage) {
    Health -= damage;
    cout << "PoisonMonster took " << damage << " damage. Remaining health: " << Health << endl;
}

shared_ptr<Item> PoisonMonster::DropItem() {
    if (IsCreateEvent(10)) {
        cout << "QuestItem" << endl;
        return make_shared<ItemForQuest>();
    }
    else {
        if (IsCreateEvent(50)) {
            cout << "HealthPotion" << endl;
            return make_shared<HealthPotion>();
        }
        if (IsCreateEvent(40)) {
            cout << "AttackBoost" << endl;
            return make_shared<AttackBoost>();
        }
    }
    cout << "I am " << GetName() << ", No Drop." << endl;
    return nullptr;
}

// MonsterFactory Implementation
shared_ptr<Monster> MonsterFactory::CreateMonster(int level) const {
    shared_ptr<Monster> tmp = CreateMonsterFunc(level);
    if (GenerateRandom(1, 10) == 1) {
        tmp = make_shared<PoisonMonster>(tmp);
        cout << "MonsterFactory Create New PoisonMonster" << endl;
    }
    return tmp;
}

// BossMonsterFactory Implementation
shared_ptr<Monster> BossMonsterFactory::CreateBossMonster(int level) const {
    shared_ptr<Monster> tmp = CreateMonsterFunc(level);
    tmp = make_shared<BossMonster>(tmp);
    cout << "Boss Name: " << tmp->GetName() << endl;
    return tmp;
}

// Helper Function
shared_ptr<Monster> CreateMonsterFunc(int level) {
    shared_ptr<Monster> tmp;
    int MonsterType = GenerateRandom(0, 2);

    switch (MonsterType) {
    case 0:
        tmp = make_shared<Goblin>(level);
        cout << "MonsterFactory Create New Goblin" << endl;
        break;
    case 1:
        tmp = make_shared<Orc>(level);
        cout << "MonsterFactory Create New Orc" << endl;
        break;
    case 2:
        tmp = make_shared<Troll>(level);
        cout << "MonsterFactory Create New Troll" << endl;
        break;
    default:
        cout << "Critical Error" << endl;
    }
    return tmp;
}