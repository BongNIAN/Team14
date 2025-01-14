#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <memory>

class Character;

class Item {
private:
    std::string name;   // ������ �̸�
    int price;

public:



    // ���� �Ҹ���
    virtual ~Item() = default;

    // ���� ���� �Լ�: ������ ���
    virtual void use(Character* character) = 0;

    // ������ �̸� ��ȯ
    virtual std::string getName() const = 0;
    virtual int getPrice() const = 0;


};

// ���ݷ� ���� ���� Ŭ���� ����
class AttackBoost : public Item {
public:
    // ������
    AttackBoost();

    // ������ ��� �޼���
    void use(Character* character) override;

    // ������ ��� ���ڿ� ��ȯ
    std::string getName() const;

    int getPrice() const;

private:
    std::string name;
    int price;
};

class HealthPotion : public Item {
public:
    HealthPotion();

    // ������ ��� �޼���           
    void use(Character* character) override;

    // ������ ��� ���ڿ� ��ȯ
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

    // ������ ��� �޼���           
    void use(Character* character) override;

    // ������ ��� ���ڿ� ��ȯ
    std::string getName() const;

    //�����ؾ���
    int getPrice() const;

private:
    std::string name;
    int price;

};

struct ItemCompare {
    bool operator()(const std::shared_ptr<Item>& left, const std::shared_ptr<Item>& right) const;
};


#endif // ITEM_H