#include "item.h"
#include "character.h"


using namespace std;



AttackBoost::AttackBoost() : name("AttackBoost"), price(15) {}

// AttackPotion 클래스 아이템 사용 메서드
void AttackBoost::use(Character* character) {
    int level = character->getLevel();

    int bonus = level * 8;



    // 캐릭터에 효과 적용
    character->increaseATK(bonus);

    // 사용 메시지 출력
    std::cout << name << " (등급: " << this->getName() << ")을(를) 사용했습니다!\n";
}

std::string AttackBoost::getName() const
{
    return this->name;
}

int AttackBoost::getPrice() const 
{
    return this->price;
}

HealthPotion::HealthPotion() : name("HealthPotion"),price(10) {}

void HealthPotion::use(Character* character) {
    if (character) {
        // 캐릭터의 체력을 회복시키는 로직
        int getLv = character->getLevel();

        character->increaseHP(getLv * 20);  // 체력 +50 (예시)
        cout << "im HealthPotion cpp , :hp는 + " << getLv * 20 << endl;
    }
}

string HealthPotion::getName() const {
    return this->name;
}

int HealthPotion::getPrice() const
{
    return this->price;
}


ItemForQuest::ItemForQuest() : name("ItemForQuest") ,price(1){}

void ItemForQuest::use(Character* character) {
    if (character) {
        // 특정 퀘스트를 위한 아이템 사용 로직
        cout << "ItemForQuest used! Quest objective " << endl;
    }
}

string ItemForQuest::getName() const {
    return this->name;
}

int ItemForQuest::getPrice() const
{
    return this->price;
}

bool ItemCompare::operator()(const std::shared_ptr<Item>& left, const std::shared_ptr<Item>& right) const {
    // 아이템 이름을 기준으로 비교
    if (left->getName() == right->getName()) {
        return false;
    }

    // 이름이 다를 경우 오름차순 비교
    return left->getName() > right->getName();
}

