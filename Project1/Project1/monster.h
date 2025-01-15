#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <memory>

// 전방 선언
class Item;

using namespace std;

/** Base Monster Class */
class Monster {
public:
    virtual string GetName() const = 0;
    virtual int GetHealth() const = 0;
    virtual int GetAttack() const = 0;
    virtual void TakeDamage(int damage) = 0;
    virtual shared_ptr<Item> DropItem() = 0;
    virtual ~Monster() = default;
};

/** Goblin Monster Class */
class Goblin : public Monster {
public:
    Goblin(int level);
    string GetName() const override;
    int GetHealth() const override;
    int GetAttack() const override;
    void TakeDamage(int damage) override;
    shared_ptr<Item> DropItem() override;

private:
    string Name;
    int Health;
    int Attack;
};

/** Troll Monster Class */
class Troll : public Monster {
public:
    Troll(int level);
    string GetName() const override;
    int GetHealth() const override;
    int GetAttack() const override;
    void TakeDamage(int damage) override;
    shared_ptr<Item> DropItem() override;

private:
    string Name;
    int Health;
    int Attack;
};

/** Orc Monster Class */
class Orc : public Monster {
public:
    Orc(int level);
    string GetName() const override;
    int GetHealth() const override;
    int GetAttack() const override;
    void TakeDamage(int damage) override;
    shared_ptr<Item> DropItem() override;

private:
    string Name;
    int Health;
    int Attack;
};

/** Abstract Monster Decorator */
class MonsterDecorator : public Monster {
public:
    MonsterDecorator(shared_ptr<Monster> m);
    virtual ~MonsterDecorator();
    string GetName() const override;
    int GetHealth() const override;
    int GetAttack() const override;
    void TakeDamage(int damage) override;
    shared_ptr<Item> DropItem() override;

protected:
    shared_ptr<Monster> monster;
};

/** Boss Monster Decorator */
class BossMonster : public MonsterDecorator {
public:
    BossMonster(shared_ptr<Monster> m);
    string GetName() const override;
    int GetHealth() const override;
    int GetAttack() const override;
    void TakeDamage(int damage) override;
    shared_ptr<Item> DropItem() override;

private:
    string Name;
    int Health;
    int Attack;
};

/** Poison Monster Decorator */
class PoisonMonster : public MonsterDecorator {
public:
    PoisonMonster(shared_ptr<Monster> m);
    string GetName() const override;
    int GetHealth() const override;
    int GetAttack() const override;
    void TakeDamage(int damage) override;
    shared_ptr<Item> DropItem() override;

private:
    string Name;
    int Health;
    int Attack;
};

/** Monster Factory Interface */
class IMonsterFactory {
public:
    virtual shared_ptr<Monster> CreateMonster(int level) const = 0;
    virtual ~IMonsterFactory() = default;
};

/** Boss Monster Factory Interface */
class IBossMonsterFactory {
public:
    virtual shared_ptr<Monster> CreateBossMonster(int level) const = 0;
    virtual ~IBossMonsterFactory() = default;
};

/** Monster Factory Implementation */
class MonsterFactory : public IMonsterFactory {
public:
    shared_ptr<Monster> CreateMonster(int level) const override;
};

/** Boss Monster Factory Implementation */
class BossMonsterFactory : public IBossMonsterFactory {
public:
    shared_ptr<Monster> CreateBossMonster(int level) const override;
};

shared_ptr<Monster> CreateMonsterFunc(int level);

#endif // MONSTER_H