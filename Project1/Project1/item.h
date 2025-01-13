
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <memory>
using namespace std;

/** Base Item Class */
class Item {
public:
    virtual string GetName() const = 0;
    virtual void use() = 0;
    virtual ~Item() = default;
};

/** HealthPotion Class */
class HealthPotion : public Item {
public:
    HealthPotion();
    void use() override;
    string GetName() const override;

private:
    string name;
    int HealthRestore;
};

/** AttackBoost Class */
class AttackBoost : public Item {
public:
    AttackBoost();
    void use() override;
    string GetName() const override;

private:
    string name;
    int AttackIncrease;
};

/** ItemForQuest Class */
class ItemForQuest : public Item {
public:
    ItemForQuest();
    void use() override;
    string GetName() const override;

private:
    string name;
};

/** Antidote Class */
class Antidote : public Item {
public:
    void use() override;

private:
    string name;
};

#endif // ITEM_H
