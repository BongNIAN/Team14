#include "item.h"
#include <iostream>
using namespace std;

// HealthPotion Implementation
HealthPotion::HealthPotion() : name("HealthPotion"), HealthRestore(50) {}

void HealthPotion::use() {
    cout << "HealPotion" << endl;
}

string HealthPotion::GetName() const {
    return this->name;
}

// AttackBoost Implementation
AttackBoost::AttackBoost() : name("AttackBoost"), AttackIncrease(50) {}

void AttackBoost::use() {
    cout << "AttackBoost" << endl;
}

string AttackBoost::GetName() const {
    return this->name;
}

// ItemForQuest Implementation
ItemForQuest::ItemForQuest() : name("ItemForQuest") {}

string ItemForQuest::GetName() const {
    return this->name;
}

void ItemForQuest::use() {
    cout << "ItemForQuest" << endl;
}

// Antidote Implementation
void Antidote::use() {
    cout << "해독제 리턴값 1 or true" << endl;
}
