#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <limits>
#include "character.h"

// ������ ��� ������
enum class ItemGrade { S, A, B, C };

// �߻� Ŭ���� Item ����
class Item {
protected:
    std::string name;   // ������ �̸�
    ItemGrade grade;    // ������ ���

public:
    // ������
    Item(const std::string& itemName, ItemGrade itemGrade);

    // ���� �Ҹ���
    virtual ~Item();

    // ���� ���� �Լ�: ������ ���
    virtual void use(Character* character, int level) = 0;

    // ������ �̸� ��ȯ
    std::string getName() const;

    // ������ ��� ��ȯ
    ItemGrade getGrade() const;
};

// ���ݷ� ���� ���� Ŭ���� ����
class AttackPotion : public Item {
public:
    // ������
    AttackPotion(ItemGrade itemGrade);

    // ������ ��� �޼���
    void use(Character* character, int level) override;

    // ������ ��� ���ڿ� ��ȯ
    std::string getGradeString() const;
};

#endif // ITEM_H
