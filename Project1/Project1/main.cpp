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
    * 현재 오름차순으로 정렬되어 있기 때문에 [0] = AttackBoost
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

    /**이부분 에러 ->올바르지 않은 nullptr이 들어간다면, 중단됨 */
    // c->addItem(HealthPotion, 3); 
    // HealthPotion이 null이라면 중단처리 
    // 메서드 ItemManager add함수에 null값 처리 완료 

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