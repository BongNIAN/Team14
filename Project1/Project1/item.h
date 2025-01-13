#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <limits>
#include "character.h"

// 아이템 등급 열거형
enum class ItemGrade { S, A, B, C };

// 추상 클래스 Item 정의
class Item {
protected:
    std::string name;   // 아이템 이름
    ItemGrade grade;    // 아이템 등급

public:
    // 생성자
    Item(const std::string& itemName, ItemGrade itemGrade);

    // 가상 소멸자
    virtual ~Item();

    // 순수 가상 함수: 아이템 사용
    virtual void use(Character* character, int level) = 0;

    // 아이템 이름 반환
    std::string getName() const;

    // 아이템 등급 반환
    ItemGrade getGrade() const;
};

// 공격력 증가 포션 클래스 정의
class AttackPotion : public Item {
public:
    // 생성자
    AttackPotion(ItemGrade itemGrade);

    // 아이템 사용 메서드
    void use(Character* character, int level) override;

    // 아이템 등급 문자열 반환
    std::string getGradeString() const;
};

#endif // ITEM_H
