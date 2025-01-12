#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

using namespace std;

class Item {
public:
    virtual string GetName() const = 0;
    virtual void use() = 0;
    virtual ~Item() = default;
};

class HealthPotion :public Item {
public:
    HealthPotion() : name("HealthPotion"), HealthRestore(50) {}
    void use()
    {
        cout << "HealPotion" << endl;
    }

    string GetName() const
    {
        return this->name;
    }
private:
    string name;
    int HealthRestore;

};
class AttackBoost :public Item
{
public:
    AttackBoost() : name("AttackBoost"), AttackIncrease(50) {}
    void use()
    {
        cout << "AttackBoost" << endl;
    }

    string GetName() const
    {
        return this->name;
    }
private:
    string name;
    int AttackIncrease;

};


class ItemForQuest :public Item {
public:
    ItemForQuest() : name("ItemForQuest") {}
    string GetName() const
    {
        return this->name;
    }

    void use() {
        cout << "ItemForQuest" << endl;
    };

private:
    string name;
};

class Antidote :public Item {
public:

    void use() {
        cout << "해독제 리턴값 1 or true" << endl;
    };
private:
    string name;
};


//이벤트확률구현 함수 
/**정확성을 위해 초기화*/
void InitializeRandom()
{

    srand(static_cast<unsigned int>(time(0)));
}

/**min<= RandomX <= max*/
int GenerateRandom(int min, int max)
{

    return min + (rand() % (max - min + 1));
}

//Percent
bool IsCreateEvent(int percent)
{
    int sample = GenerateRandom(0, 99);

    if (sample < percent) {

        return true;

    }


    return false;
}

string CreateGradeByCDF() {

    const vector<pair<int, string>> grade =
    {
        {1, "S"},    // 1%
        {10, "A"},   // 9%
        {30, "B"},   // 20%
        {55, "C"},   // 25%
        {100, "D"}   // 45%
    };

    int RandomValue = GenerateRandom(1, 100);

    for (const auto& range : grade) {
        if (RandomValue <= range.first) {
            return range.second;
        }
    }
    return "D"; // Default case 



}

//Create MonsterClass
class Monster
{
public:
    virtual string GetName() const = 0;
    virtual int GetHealth() const = 0;
    virtual int GetAttack() const = 0;
    virtual void TakeDamage(int damage) = 0;
    virtual shared_ptr<Item> DropItem() = 0;
    virtual ~Monster() = default;
};

//Create MonsterClass
class Goblin : public Monster
{
public:
    Goblin(int level)
    {
        Name = "Goblin";
        Health = level * GenerateRandom(20, 30);
        Attack = level * GenerateRandom(5, 10);
    }

    string GetName() const override
    {
        return Name;
    }

    int GetHealth() const override
    {
        return Health;
    }

    int GetAttack() const override
    {
        return Attack;
    }

    void TakeDamage(int damage) override
    {
        Health -= damage;
        cout << "Goblin took " << damage << " damage. Remaining health: " << Health << endl;
    }

    shared_ptr<Item> DropItem() override
    {
        if (IsCreateEvent(30)) {
            if (IsCreateEvent(50))
            {
                return make_shared<HealthPotion>();

            }
            else
            {
                return make_shared<AttackBoost>();
            }
        }


        cout << "I am Goblin, No Drop." << endl;
        return nullptr;
    }

private:
    string Name;
    int Health;
    int Attack;
};

//Create MonsterClass
class Troll : public Monster {
public:
    Troll(int level)
    {
        Name = "Troll";
        Health = level * GenerateRandom(20, 30);
        Attack = level * GenerateRandom(5, 10);
    }
    string GetName() const override {
        return Name;
    }

    int GetHealth() const override {
        return Health;
    }

    int GetAttack() const override {
        return Attack;
    }

    void TakeDamage(int damage) override {
        Health -= damage;
        cout << "Troll took " << damage << " damage. Remaining health: " << Health << endl;
    }

    shared_ptr<Item> DropItem() override {
        if (IsCreateEvent(30)) {
            if (IsCreateEvent(50))
            {
                return make_shared<HealthPotion>();

            }
            else
            {
                return make_shared<AttackBoost>();
            }
        }


        cout << "I am Troll, No Drop." << endl;
        return nullptr;
    }

private:
    string Name;
    int Health;
    int Attack;
};

//Create MonsterClass
class Orc : public Monster {
public:
    Orc(int level)
    {
        Name = "Orc";
        Health = level * GenerateRandom(20, 30);
        Attack = level * GenerateRandom(5, 10);
    }

    string GetName() const override {
        return Name;
    }

    int GetHealth() const override {
        return Health;
    }

    int GetAttack() const override {
        return Attack;
    }

    void TakeDamage(int damage) override {
        Health -= damage;
        cout << "Orc took " << damage << " damage. Remaining health: " << Health << endl;
    }

    shared_ptr<Item> DropItem() override {
        if (IsCreateEvent(30)) {
            if (IsCreateEvent(50))
            {
                return make_shared<HealthPotion>();

            }
            else
            {
                return make_shared<AttackBoost>();
            }
        }


        cout << "I am Orc, No Drop." << endl;
        return nullptr;
    }

private:
    string Name;
    int Health;
    int Attack;
};

//Create Abs Class
class MonsterDecorator : public Monster {
public:
    MonsterDecorator(shared_ptr<Monster> m) : monster(m) {}

    virtual ~MonsterDecorator()
    {
        cout << " byebyeDecorator" << endl;
    }

protected:
    shared_ptr<Monster> monster;
};

//Decorate Monster 
class BossMonster : public MonsterDecorator {
public:
    BossMonster(shared_ptr<Monster> m) : MonsterDecorator(m)
    {
        cout << "monsterAttack :     " << m->GetAttack() << endl;
        this->Name = "Boss" + m->GetName();
        this->Attack = static_cast <int> (m->GetAttack() * 1.5);
        this->Health = static_cast <int> (m->GetHealth() * 1.5);
        cout << "BossAttack :     " << this->Attack << endl;
    }

    string GetName() const override {
        return Name;
    }

    int GetHealth() const override {
        return Health;
    }

    int GetAttack() const override {
        return Attack;
    }

    void TakeDamage(int damage) override {
        Health -= damage;
        cout << "Boss took " << damage << " damage. Remaining health: " << Health << endl;
    }

    shared_ptr<Item> DropItem() override {
        if (IsCreateEvent(10))
        {
            cout << "QuestItem" << endl;
            return make_shared<ItemForQuest>();
        }
        else {
            if (IsCreateEvent(50)) {
                cout << "HealthPotion" << endl;
                return make_shared<HealthPotion>();
            }
            if (IsCreateEvent(40)) {
                cout << "AttackBoost" << endl;
                return make_shared<AttackBoost>();
            }

        }


        cout << "I am Boss, No Drop." << endl;
        return nullptr;
    }

private:
    string Name;
    int Health;
    int Attack;
};

//Decorate Monster
class PoisonMonster : public MonsterDecorator {
public:
    PoisonMonster(shared_ptr<Monster> m) : MonsterDecorator(m)
    {
        cout << "monsterAttack :     " << m->GetAttack() << endl;
        Name = "Poison" + m->GetName();
        Attack = m->GetAttack();
        Health = m->GetAttack();
        cout << "BossAttack :     " << this->Attack << endl;
    }

    string GetName() const override {
        return  Name;
    }

    int GetHealth() const override {
        return Health;
    }

    int GetAttack() const override {

        if (IsCreateEvent(10))
        {
            return Attack + 1; // 어택 +1 이면 독걸린것 
        }

        return Attack;
    }

    /**다시 진행할지 말지 */
    /*int PoisonAttack(bool IsPoison) const
    {
        if (IsPoison)
        {
            return Attack;
        }

        else {

        }

        return Attack;
    }
  */

    void TakeDamage(int damage) override {
        Health -= damage;
        cout << "Boss took " << damage << " damage. Remaining health: " << Health << endl;
    }

    shared_ptr<Item> DropItem() override {
        if (IsCreateEvent(10))
        {
            cout << "QuestItem" << endl;
            return make_shared<ItemForQuest>();
        }
        else {
            if (IsCreateEvent(50)) {
                cout << "HealthPotion" << endl;
                return make_shared<HealthPotion>();
            }
            if (IsCreateEvent(40)) {
                cout << "AttackBoost" << endl;
                return make_shared<AttackBoost>();
            }

        }


        cout << "I am" << this->GetName() << "No Drop." << endl;
        return nullptr;
    }

    //drop Item 모듈화시켜야할듯 ? //보스따로 Decorator따로

private:
    string Name;
    int Health;
    int Attack;
};

//Create Factory Interface
class IMonsterFactory {
public:

    virtual shared_ptr<Monster> CreateMonster(int level) const = 0;
    virtual ~IMonsterFactory() = default;
};

//Create BossFactory Interface
class IBossMonsterFactory {
public:

    virtual shared_ptr<Monster> CreateBossMonster(int level) const = 0;
    virtual ~IBossMonsterFactory() = default;
};

shared_ptr<Monster> CreateMonster(int level)
{
    shared_ptr<Monster> tmp;

    int MonsterType = GenerateRandom(0, 2);

    switch (MonsterType)
    {
    case 0:
        tmp = make_shared<Goblin>(level);
        cout << "MonsterFactory Create New Goblin" << endl;
        break;

    case 1:
        tmp = make_shared<Orc>(level);
        cout << "MonsterFactory Create New Orc" << endl;
        break;

    case 2:
        tmp = make_shared <Troll>(level);
        cout << "MonsterFactory Create New Troll" << endl;
        break;
    default:
        cout << "Critical Error" << endl;
    }
    return tmp;

}

//Create MonsterFactory
class MonsterFactory :public IMonsterFactory
{
public:

    shared_ptr<Monster> CreateMonster(int level) const override
    {
        shared_ptr<Monster> tmp;



        int IsPoison = GenerateRandom(1, 10);

        tmp = CreateMonster(level);

        //1~10중 1이 걸리면 10%
        if (IsPoison == 1)
        {
            tmp = make_shared<PoisonMonster>(tmp);
            cout << "MonsterFactory Create New IsPoison" << endl;
        }

        return tmp;
    }

};

//Create BossMonsterFactory
class BossMonsterFactory : public IBossMonsterFactory
{
public:

    shared_ptr<Monster> CreateBossMonster(int level) const override
    {
        shared_ptr<Monster> tmp;
        //0~2 난수 생성
        int MonsterType = GenerateRandom(0, 2);


        tmp = CreateMonster(level);

        //1~10중 1이 걸리면 10%

        tmp = make_shared<BossMonster>(tmp);

        cout << "Boss Name  : " << tmp->GetName() << endl;


        return tmp;

    }

};

int main() {

    cout << "Hello" << endl;

    BossMonsterFactory boss;
    for (int i = 0; i < 100; i++)
    {
        boss.CreateBossMonster(i);
    }

    return 0;
}