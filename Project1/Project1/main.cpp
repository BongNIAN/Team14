#include <iostream>
#include "monster.h"
#include "random.h"
#include "Character.h"
#include "item.h"
#include "shop.h"

int main() {
    InitializeRandom();

    Character* c = Character::getInstance("hero");
   /* BossMonsterFactory boss;
    MonsterFactory monst;
    int ItemCnt = 0;*/

    Shop s;
   
   bool check = true;
   check =  s.buyItem(*c,1);

   cout << "dfasdfasdfasdfasdfasf" << check << endl;

   c->increaseGold(1000);
   check = s.buyItem(*c, 1);
   check = s.buyItem(*c, 1);
   check = s.buyItem(*c, 1);
   check = s.buyItem(*c, 1);
   check = s.buyItem(*c, 1);

   check = s.buyItem(*c, 1);
   check = s.buyItem(*c, 1);
   check = s.buyItem(*c, 1);
   check = s.buyItem(*c, 2);
   check = s.buyItem(*c, 100);
   s.buyItem(*c, 200);
   c->displayInventory();
   cout << "12312312312312321312" << endl;
   vector<shared_ptr<Item>> inven = c->getInventory();

   cout << "inven size is  : " <<inven.size()<< endl;
   
   cout << "Inventory test" << endl;

   for (int i = 0; i < inven.size(); i++)
   {
       inven[i]->use(c);
   }


    return 0;
}



//Test ItemPrice


//shared_ptr<Item> healthPotion = make_shared<HealthPotion>();
//shared_ptr<Item> itemForQuest = make_shared<ItemForQuest>();
//shared_ptr<Item> attackBoost = make_shared<AttackBoost>();
//
//int a = healthPotion->getPrice();
//cout << a << endl;
//a = itemForQuest->getPrice();
//cout << a << endl;
//a = attackBoost->getPrice();
//cout << a << endl;








//Test C-I-M:
    /* for (int i = 0; i < 100; i++) {
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
    cout << "\n";*/
    /*
    * ���� ������������ ���ĵǾ� �ֱ� ������ [0] = AttackBoost
    * [1] = HealthPotion
    * [2] = QuestForItem
    **/
    /* c->displayStatus();
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
     cout << "start" << endl;*/

     /**�̺κ� ���� ->�ùٸ��� ���� nullptr�� ���ٸ�, �ߴܵ� */
     // c->addItem(HealthPotion, 3); 
     // HealthPotion�� null�̶�� �ߴ�ó�� 
     // �޼��� ItemManager add�Լ��� null�� ó�� �Ϸ� 



     /*c->addItem(healthPotion, 3);

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

     c->~Character();*/
