#include "item.h"
#include "character.h"


using namespace std;



AttackBoost::AttackBoost() : name("AttackBoost"), price(15) {}

// AttackPotion Ŭ���� ������ ��� �޼���
void AttackBoost::use(Character* character) {
    int level = character->getLevel();

    int bonus = level * 8;



    // ĳ���Ϳ� ȿ�� ����
    character->increaseATK(bonus);

    // ��� �޽��� ���
    std::cout << name << " (���: " << this->getName() << ")��(��) ����߽��ϴ�!\n";
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
        // ĳ������ ü���� ȸ����Ű�� ����
        int getLv = character->getLevel();

        character->increaseHP(getLv * 20);  // ü�� +50 (����)
        cout << "im HealthPotion cpp , :hp�� + " << getLv * 20 << endl;
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
        // Ư�� ����Ʈ�� ���� ������ ��� ����
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
    // ������ �̸��� �������� ��
    if (left->getName() == right->getName()) {
        return false;
    }

    // �̸��� �ٸ� ��� �������� ��
    return left->getName() > right->getName();
}

