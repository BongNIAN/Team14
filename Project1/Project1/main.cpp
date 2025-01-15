#include <iostream>
#include "monster.h"
#include "random.h"
#include "Character.h"
#include "item.h"
#include "shop.h"
#include "print.h"
#include "observer.h"
#include "battlemanager.h"



int main() {
    InitializeRandom();
    

    Character* c = Character::getInstance("hero");
    shared_ptr<Item> item = make_shared<HealthPotion>();
    shared_ptr<Item> item2 = make_shared<AttackBoost>();
    BattleManager TestBossMonster;
    BattleManager TestMonster;
  
  
    int cnt = 0;
    while (cnt < 10)
    {
        TestMonster.MonsterBattle(c);
        cnt++;


        int BattleResult = 100;


        for (int i = 0; i < 10; i++)
        {
            BattleResult = TestMonster.MonsterBattle(c);

            if (BattleResult == 1)
            {
                cout << "Player Win" << endl;
            }
            else if (BattleResult == 2)
            {
                cout << "Monster Win" << endl;
            }
            else if (BattleResult == 3)
            {
                cout << "Run" << endl;
            }

        } } 
        

        return 0;
   

}





//Test Observer : 
//
//Character* c = Character::getInstance("hero");
//auto playerObserver = std::make_shared<PlayerObserver>();
//auto gameOverHandler = std::make_shared<GameOverHandler>();
//c->Attach(playerObserver);
//c->Attach(gameOverHandler);
//MonsterFactory mf;
//shared_ptr<Monster> m = mf.CreateMonster(1);
//
//printMonsterTestModule(m);
//c->takeDamage(170);
//drawHpBar(c->getHP(), c->getMaxHp());
//PrintLine("123213123");
//printBattleWithMonster();
//printBossMonster();
//cout << GenerateRandom(1, 10) << endl;
//c->takeDamage(30);
//c->takeDamage(100);




//Test Shop
//Character* c = Character::getInstance("hero");
///* BossMonsterFactory boss;
// MonsterFactory monst;
// int ItemCnt = 0;*/
//
//Shop s;
//
//bool check = true;
//check = s.buyItem(*c, 1);
//
//cout << "dfasdfasdfasdfasdfasf" << check << endl;
//
//c->increaseGold(1000);
//check = s.buyItem(*c, 1);
//check = s.buyItem(*c, 1);
//check = s.buyItem(*c, 1);
//check = s.buyItem(*c, 1);
//check = s.buyItem(*c, 1);
//
//check = s.buyItem(*c, 1);
//check = s.buyItem(*c, 1);
//check = s.buyItem(*c, 1);
//check = s.buyItem(*c, 2);
//check = s.buyItem(*c, 100);
//s.buyItem(*c, 200);
//c->displayInventory();
//cout << "12312312312312321312" << endl;
//vector<shared_ptr<Item>> inven = c->getInventory();
//
//cout << "inven size is  : " << inven.size() << endl;
//
//cout << "Inventory test" << endl;
//
//for (int i = 0; i < inven.size(); i++)
//{
//    inven[i]->use(c);
//}




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
    * 현재 오름차순으로 정렬되어 있기 때문에 [0] = AttackBoost
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

     /**이부분 에러 ->올바르지 않은 nullptr이 들어간다면, 중단됨 */
     // c->addItem(HealthPotion, 3); 
     // HealthPotion이 null이라면 중단처리 
     // 메서드 ItemManager add함수에 null값 처리 완료 



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
