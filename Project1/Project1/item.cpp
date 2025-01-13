#include "Item.h"

// Item Ŭ���� ������
Item::Item(const std::string& itemName, ItemGrade itemGrade)
    : name(itemName), grade(itemGrade) {
}

// Item Ŭ���� �Ҹ���
Item::~Item() {
}

// ������ �̸� ��ȯ
std::string Item::getName() const {
    return name;
}

// ������ ��� ��ȯ
ItemGrade Item::getGrade() const {
    return grade;
}

// AttackPotion Ŭ���� ������
AttackPotion::AttackPotion(ItemGrade itemGrade)
    : Item("Attack Potion", itemGrade) {
}

// AttackPotion Ŭ���� ������ ��� �޼���
void AttackPotion::use(Character* character, int level) {
    int bonus = 0;

    // ��޿� ���� ȿ�� ����
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

    // ĳ���Ϳ� ȿ�� ����
    character->increaseATK(bonus);

    // ��� �޽��� ���
    std::cout << name << " (���: " << getGradeString() << ")��(��) ����߽��ϴ�!\n";
}

// AttackPotion Ŭ���� ������ ��� ���ڿ� ��ȯ
std::string AttackPotion::getGradeString() const {
    switch (grade) {
    case ItemGrade::S: return "S";
    case ItemGrade::A: return "A";
    case ItemGrade::B: return "B";
    case ItemGrade::C: return "C";
    default: return "Unknown";
    }
}
