#include <iostream>
#include "monster.h"
#include "random.h"
#include "Character.h"
#include "item.h"

int main() {
    InitializeRandom();

    Character* c = Character::getInstance("hero");
    BossMonsterFactory boss;
    MonsterFactory monst;
    int ItemCnt = 0;

    for (int i = 0; i < 100; i++) {
        boss.CreateBossMonster(i);
    }
    for (int i = 0; i < 100; i++) {

        shared_ptr<Monster> tmp = monst.CreateMonster(i);
        shared_ptr<Item> itemTmp;
        itemTmp = tmp->DropItem();
        if (itemTmp == nullptr)continue;
        c->addItem(itemTmp);
        ItemCnt++;

    }
    c->displayInventory();
    cout << ItemCnt << endl;
    cout << "\n";



    /*
    * ���� ������������ ���ĵǾ� �ֱ� ������ [0] = AttackBoost
    * [1] = HealthPotion
    * [2] = QuestForItem
    **/
    c->displayStatus();
    c->useItem(0);
    c->displayStatus();
    c->useItem(2);
    c->displayStatus();
    c->useItem(1);
    c->displayStatus();
    cout << "\n";
    c->displayInventory();
    cout << "\n";

    cout << "display Status start" << endl;
    c->displayStatus();
    cout << "display Status end" << endl;
    cout << "\n";
    c->displayInventory();
    cout << "start" << endl;

    /**�̺κ� ���� ->�ùٸ��� ���� nullptr�� ���ٸ�, �ߴܵ� */
    // c->addItem(HealthPotion, 3); 
    // HealthPotion�� null�̶�� �ߴ�ó�� 
    // �޼��� ItemManager add�Լ��� null�� ó�� �Ϸ� 

    shared_ptr<Item> healthPotion = make_shared<HealthPotion>();

    c->addItem(healthPotion, 3);

    c->displayInventory();

    c->addItem(nullptr, 3);


    c->displayStatus();
    c->increaseGold(3);
    c->displayStatus();


    c->decreaseGold(3);
    c->displayStatus();


    c->decreaseGold(3);
    c->displayStatus();

    c->decreaseGold(3);
    c->displayStatus();

    c->takeDamage(30);
    c->displayStatus();

    c->takeDamage(30);
    c->displayStatus();
    c->takeDamage(30);
    c->displayStatus();
    c->takeDamage(300);
    c->displayStatus();

    c->~Character();
   


    return 0;
}