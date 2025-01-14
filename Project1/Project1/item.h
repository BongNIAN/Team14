#include "item.h"
#include "character.h"


using namespace std;



AttackBoost::AttackBoost() : name("AttackBoost") {}

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

HealthPotion::HealthPotion() : name("HealthPotion") {}

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

ItemForQuest::ItemForQuest() : name("ItemForQuest") {}

void ItemForQuest::use(Character* character) {
    if (character) {
        // 특정 퀘스트를 위한 아이템 사용 로직
        cout << "ItemForQuest used! Quest objective " << endl;
    }
}

string ItemForQuest::getName() const {
    return this->name;
}

bool ItemCompare::operator()(const std::shared_ptr<Item>& left, const std::shared_ptr<Item>& right) const {
    // 아이템 이름을 기준으로 비교
    if (left->getName() == right->getName()) {
        return false;
    }

    // 이름이 다를 경우 내림차순 비교
    return left->getName() > right->getName();
}