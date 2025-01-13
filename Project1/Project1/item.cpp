#include "Item.h"

// Item 클래스 생성자
Item::Item(const std::string& itemName, ItemGrade itemGrade)
    : name(itemName), grade(itemGrade) {
}

// Item 클래스 소멸자
Item::~Item() {
}

// 아이템 이름 반환
std::string Item::getName() const {
    return name;
}

// 아이템 등급 반환
ItemGrade Item::getGrade() const {
    return grade;
}

// AttackPotion 클래스 생성자
AttackPotion::AttackPotion(ItemGrade itemGrade)
    : Item("Attack Potion", itemGrade) {
}

// AttackPotion 클래스 아이템 사용 메서드
void AttackPotion::use(Character* character, int level) {
    int bonus = 0;

    // 등급에 따른 효과 설정
    switch (grade) {
    case ItemGrade::S:
        bonus = 10000;
        break;
    case ItemGrade::A:
        bonus = 100;
        break;
    case ItemGrade::B:
        bonus = 50;
        break;
    case ItemGrade::C:
        bonus = 20;
        break;
    }

    // 캐릭터에 효과 적용
    character->increaseATK(bonus);

    // 사용 메시지 출력
    std::cout << name << " (등급: " << getGradeString() << ")을(를) 사용했습니다!\n";
}

// AttackPotion 클래스 아이템 등급 문자열 반환
std::string AttackPotion::getGradeString() const {
    switch (grade) {
    case ItemGrade::S: return "S";
    case ItemGrade::A: return "A";
    case ItemGrade::B: return "B";
    case ItemGrade::C: return "C";
    default: return "Unknown";
    }
}
