#include "battlemanager.h"
#include "print.h"
#include "random.h" 

//이부분 리턴값 필요할것 같다 플레이어가 죽었는지 
//몬스터가 죽었는지를 확인할 지표가 필요해 
//보스몬스터와 일반몬스터 배틀은 다를 수 있으니깐 각각 따로 구현해야하나?
void BattleManager :: Battle(Character *c) 
{

	MonsterFactory m;
	int InvenSelection = 1000;
	//몬스터 생성
	shared_ptr<Monster> tmp = m.CreateMonster(c->getLevel());
	int CheckThrough = 1;
	while (1)
	{


		

		int selection = 1000; // 초기화
		PrintSelection();
		cout << "만일..도망가기를 실패한다면..."
			<< "많이 맞을 수 있소.. 거기에 골드도 떨어지오.."
			<< endl;

		cin >> selection;

		if (IsCreateEvent(30) && CheckThrough != 0)
		{
			cout << "몬스터 선 공격!" << endl;
			c->takeDamage(tmp->GetAttack());
			if (c->getHP() <= 0)
			{
				cout << "im BM , you die" << endl;
				break;
			}
		}


		switch (selection)
		{
		case(1) : 
			CheckThrough = 1;
			
			cout << "플레이어 공격 : " << c->getATK() << endl;
			tmp->TakeDamage(c->getATK());
			if(tmp->GetHealth() <= 0)
			{ 
				cout << "획득경험치 : 40 ";  
				c->setEXP(50);

				int gold = GenerateRandom(10, 20);
				cout << "획득 골드" << gold << endl;
				c->increaseGold(gold);

				shared_ptr<Item> tmpItem = tmp->DropItem();

				if (tmpItem != nullptr)
				{
					cout << "item : " << tmpItem->getName();
					cout << "\n";
				}
				else 
				{
					cout << "몬스터 드랍 아무것도 안됨" << endl;
				}

				CheckThrough = 100;
				InvenSelection = 0;
				break;
			}
			c->takeDamage(tmp->GetAttack());
			if (c->getHP() <= 0)
			{
				cout << "im BM , you die" << endl;
				CheckThrough = 100;
				InvenSelection = 0;
				break;
			}

			InvenSelection = 0;
			break;

		case(2):
			

			
			
			c->displayInventory();
			cout << "사용할 아이템을 고르세요" << endl;
			cout << "인벤토리 닫기는 9을 써주세요 ! " << endl;
			cin >> InvenSelection;

			//만일 아이템이 비어있다면  invenselection 0 으로 
			//인벤토리 사이즈 리턴 
			//이거 검색값으로 리턴해야할듯?
			//지금 벡터로 들어가서 벡터로 순회를 하기때문에
			//인덱스 오류가 발생함 
			//map으로 바꿔야할듯 
			//그리고 shop에서 지금 인덱스가 맞는지 체크한번 해보기 
			//몬스터가 죽을 때 확률적으로 독에 걸리게 한다
			//독에 걸렸다면 ? 몬스터에게 공격받을 때 
			if (InvenSelection == 9)
			{
				CheckThrough = 0;
				break;
			}
			c->useItem(1);
			CheckThrough = 1;
			break;
			


		case(3) : // 도망가기
			
			// 실패 한대 얻어맞고 또 확률적으로 얻어맞고 
			if (IsCreateEvent(50))
			{
				CheckThrough = 100;
				cout << "탈출 성공 축하드려요 ㅎㅎ" << endl;
				//이건 전투를 탈출하는거니깐  전투 전으로 
				InvenSelection = 0;
				break;
			}
			

			cout << "도망 실패 일단 한대 맞아 그리고  10골드를 내놔 " << endl;
			// set gold c->
			c->takeDamage(tmp->GetAttack());
			if (c->getHP() <= 0)
			{
				CheckThrough = 100;
				cout << "im BM , you die" << endl;
				InvenSelection = 0;
				break;
			}

			if (c->getGold() < 10) {
				cout << "돈 없음 플레이어" << endl;
			}
			c->decreaseGold(10);
			
			c->displayStatus();
			
			CheckThrough = 1;
			InvenSelection = 0;
			break;
			
			
		case(4) : 
			
			
			c->displayStatus();
			CheckThrough = 0;
			InvenSelection = 0;
			break;

		default: 
			cout << "제대로 번호를 고르세요 " << endl;
			InvenSelection = 0;
			break;
		}
		


		//얘가 가장먼저 돌아야함
		if (CheckThrough==100 )break;
		
	
		
	}



}


void BattleManager::PrintSelection() 
{
	cout << "1 : 공격 " 
		 <<"   " << "2 : 아이템 사용" // Inventory
		<< "   " << "3 : 도망가기"
		<< "   " << "4 : 스테이터스 확인"
		<< endl;;
}

