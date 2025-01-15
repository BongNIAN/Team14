#include "battlemanager.h"
#include "print.h"
#include "random.h" 
#include "stageManager.h"

/** 혹시 오류생기면 교체할 모델입니다 삭제 노노!*/
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
				fled = true;
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
				fled = false;
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
		if (CheckThrough == 100) {
			if (!fled) {
				c->increasebattleCount(); //전투 횟수 증가

				StageManager stageManager;
				stageManager.checkStageUp(c); // 스테이지를 올릴지 확인
			}
			break;
		}
		
	
		
	}



}


int BattleManager::MonsterBattle(Character* c) 
{
	MonsterFactory m;
	int InvenSelection = 1000;
	shared_ptr<Monster> monster = m.CreateMonster(c->getLevel());
	cout << "일반 몬스터..그르르릉 드장! 내 이름은?!!! : " << monster->GetName() << endl;
	int BattleResult = HandleBattle(c, monster);
	return BattleResult;
}
int BattleManager::BossBattle(Character* c)
{

	BossMonsterFactory m;
	int InvenSelection = 1000;
	//몬스터 생성
	shared_ptr<Monster> boss = m.CreateBossMonster(c->getLevel());
	cout << "보스 몬스터..그르르릉 드장! 내 이름은?!!! : " << boss->GetName() << endl;
	int BattleResult = HandleBattle(c, boss);
	return BattleResult;

}


/**return 1 : victory, return 2 : defeat , return 3 : run */
/**checkThrough : 1. 선어택  , 0 : 선어택 맞지 않음  */
int BattleManager::HandleBattle(Character* c, shared_ptr<Monster> monster) {
	int selection = 1000;
	int CheckThrough = 1;
	int InvenSelection = 0;
	bool IsWin = false;
	bool IsDefeat = false;

	while (true) {
		cout << " //////////////////////" << endl;
		if (IsCreateEvent(30) && CheckThrough != 0) {
			cout << monster->GetName() << " 선 공격!" << endl;
			IsDefeat = HandleMonsterAttack(c, monster);
			if (IsDefeat)
			{
				return 2;
			}
			cout << "선 공격 후 스테이터스 " << endl;
			c->displayStatus();
		}
		PrintSelection();
		cout << "만일..도망가기를 실패한다면...많이 맞을 수 있소.. 거기에 골드도 떨어지오..\n";
		cin >> selection;

		

		switch (selection) {
		case 1: { // 공격
			CheckThrough = 1;
			cout << "플레이어 공격 : " << c->getATK() << endl;
			
			IsWin = HandlePlayerAttack(c, monster);
			if (IsWin) 
			{
				return 1;
			}
			//리턴값 받아오기 

			IsDefeat = HandleMonsterAttack(c, monster);
			if (IsDefeat) 
			{
				return 2;
			}
			
			cout << " 1번 선택 후 몬스터한테 맞고 난 뒤의 스테이터스 " << endl;
			c->displayStatus();


			break;
		}
		case 2: { // 아이템 사용
			c->displayInventory();
			cout << "사용할 아이템을 고르세요 (인벤토리 닫기는 9): " << endl;
			cin >> InvenSelection;

			if (InvenSelection == 9) {
				CheckThrough = 0;
				break;
			}
			c->useItem(1);
			CheckThrough = 1;
			break;
		}
		case 3: { // 도망가기
			CheckThrough = 1;

			if (IsCreateEvent(50)) {
				cout << "탈출 성공!" << endl;
				return 3; // 전투 종료 (탈출)
			}

			cout << "도망 실패! 한 대 맞고 10골드를 잃습니다." << endl;
			IsDefeat = HandleMonsterAttack(c, monster);
			if (IsDefeat)
			{
				return 2;
			}

			//소지금액이 10보다 작으면 소지한 금액 전부 삭제 
			if (c->getGold() < 10)
			{
				c->decreaseGold(c->getGold());
			}

			c->decreaseGold(10);
			//check
			c->displayStatus();
			
			
			break;
		}
		case 4: { // 상태 확인
			c->displayStatus();
			CheckThrough = 0;
			break;
		}
		default:
			cout << "잘못된 선택입니다. 다시 입력해주세요." << endl;
			break;
		}
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
bool BattleManager::HandlePlayerAttack(Character* c, shared_ptr<Monster> monster)
{
	monster->TakeDamage(c->getATK());
	if (monster->GetHealth() <= 0) {
		cout << "몬스터 처치! 경험치와 골드를 획득했습니다." << endl;
		c->setEXP(50);

		int gold = GenerateRandom(10, 20);
		c->increaseGold(gold);
		cout << "획득 골드: " << gold << endl;

		shared_ptr<Item> droppedItem = monster->DropItem();
		if (droppedItem) {
			cout << "아이템 획득: " << droppedItem->getName() << "\n";
		}
		else {
			cout << "몬스터가 아이템을 드롭하지 않았습니다." << endl;
		}
		//check
		cout << "몬스터 사망 후 스테이터스" << endl;
		c->displayStatus();
		return true; // 몬스터 사망
	}
	else return false;
}
bool BattleManager::HandleMonsterAttack(Character* c, shared_ptr<Monster> monster)
{
	cout << monster->GetName() << " 의 공격 ! 데미지 : "<<monster->GetAttack() << "를 입습니다." << endl;
	c->takeDamage(monster->GetAttack());
	if (c->getHP() <= 0) {
		cout << "플레이어가 사망했습니다." << endl;
		return true; // 플레이어 사망
	}
	else return false;
}

//TODO : 2)TODO : userState by Observer

// 3) todo : item사용 MAP Item기반 searching

// 4) todo :  스테이지로 돌아가는 기능 추가

