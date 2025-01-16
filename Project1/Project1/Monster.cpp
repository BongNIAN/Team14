#include "monster.h"
#include "item.h" 
#include "random.h"
#include <iostream>

using namespace std;


// Goblin Implementation
Goblin::Goblin(int level) {
    Name = "고블린";
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
    if (Health <= 0)
    {
        Health = 0;
    }

    cout << Name <<"  took " << damage << " damage. Remaining health: " << Health << endl;
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
bool Goblin::IsPoison() const
{
    return false;
}


// Troll Implementation
Troll::Troll(int level) {
    Name = "트롤";
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
    if (Health <= 0)
    {
        Health = 0;
    }

    cout << Name << "  took " << damage << " damage. Remaining health: " << Health << endl;

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
    
    return nullptr;
}
bool Troll::IsPoison() const
{
    return false;
}
// Orc Implementation
Orc::Orc(int level) {
    Name = "오크";
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
    if (Health <= 0)
    {
        Health = 0;
    }

    cout << Name << "  took " << damage << " damage. Remaining health: " << Health << endl;
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
    
    return nullptr;
}
bool Orc::IsPoison() const
{
    return false;
}
// MonsterDecorator Implementation
MonsterDecorator::MonsterDecorator(shared_ptr<Monster> m) : monster(move(m)) {}

MonsterDecorator::~MonsterDecorator() {
   
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
bool MonsterDecorator::IsPoison() const
{
    return false;
}

// BossMonster Implementation
BossMonster::BossMonster(shared_ptr<Monster> m) : MonsterDecorator(move(m)) {
    Name = "좀비 드래곤";
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
    if (Health <= 0)
    {
        Health = 0;
    }

    cout << Name << "  took " << damage << " damage. Remaining health: " << Health << endl;
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
    
    return nullptr;
}
bool BossMonster::IsPoison() const
{
    return false;
}

// PoisonMonster Implementation
PoisonMonster::PoisonMonster(shared_ptr<Monster> m) : MonsterDecorator(move(m)) {
    Name = "좀비 " + monster->GetName();
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
   
    return Attack;
}
bool PoisonMonster::IsPoison() const
{
    if (IsCreateEvent(50)) {
        return true;
    }
    return false;
}

void PoisonMonster::TakeDamage(int damage) {
    Health -= damage;
    if (Health <= 0)
    {
        Health = 0;
    }

   
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
   
    return nullptr;
}

// MonsterFactory Implementation
shared_ptr<Monster> MonsterFactory::CreateMonster(int level) const {
    shared_ptr<Monster> tmp = CreateMonsterFunc(level);
   
 if (GenerateRandom(1, 10) == 1) {
        tmp = make_shared<PoisonMonster>(tmp);
       
    }
    return tmp;
}

// BossMonsterFactory Implementation
shared_ptr<Monster> BossMonsterFactory::CreateBossMonster(int level) const {
    shared_ptr<Monster> tmp = CreateMonsterFunc(level);
    tmp = make_shared<BossMonster>(tmp);
    
    return tmp;
}

// Helper Function
shared_ptr<Monster> CreateMonsterFunc(int level) {
    shared_ptr<Monster> tmp;
    int MonsterType = GenerateRandom(0, 2);

    switch (MonsterType) {
    case 0:
        tmp = make_shared<Goblin>(level);
        break;
    case 1:
        tmp = make_shared<Orc>(level);
        break;
    case 2:
        tmp = make_shared<Troll>(level);
        break;
    default:
        cout << "Critical Error" << endl;
    }
    return tmp;
}