#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <memory>

class Character;

class Item {
private:
    std::string name;   // 아이템 이름
    int price;

public:



    // 가상 소멸자
    virtual ~Item() = default;

    // 순수 가상 함수: 아이템 사용
    virtual void use(Character* character) = 0;

    // 아이템 이름 반환
    virtual std::string getName() const = 0;
    virtual int getPrice() const = 0;


};

// 공격력 증가 포션 클래스 정의
class AttackBoost : public Item {
public:
    // 생성자
    AttackBoost();

    // 아이템 사용 메서드
    void use(Character* character) override;

    // 아이템 등급 문자열 반환
    std::string getName() const;

    int getPrice() const;

private:
    std::string name;
    int price;
};

class HealthPotion : public Item {
public:
    HealthPotion();

    // 아이템 사용 메서드           
    void use(Character* character) override;

    // 아이템 등급 문자열 반환
    std::string getName() const;

    int getPrice() const;

private:
    std::string name;
    int price;
};

class ItemForQuest :public Item
{

public:
    ItemForQuest();

    // 아이템 사용 메서드           
    void use(Character* character) override;

    // 아이템 등급 문자열 반환
    std::string getName() const;

    //수정해야함
    int getPrice() const;

private:
    std::string name;
    int price;

};

struct ItemCompare {
    bool operator()(const std::shared_ptr<Item>& left, const std::shared_ptr<Item>& right) const;
};


#endif // ITEM_H