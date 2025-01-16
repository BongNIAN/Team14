#include "battlemanager.h"
#include "print.h"
#include "random.h" 
#include "stageManager.h"
#include <memory>
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
		std::cout << "만일..도망가기를 실패한다면..."
			<< "많이 맞을 수 있소.. 거기에 골드도 떨어지오.."
			<< std::endl;

		std::cin >> selection;

		if (IsCreateEvent(30) && CheckThrough != 0)
		{
			std::cout << "몬스터 선 공격!" << std::endl;
			c->takeDamage(tmp->GetAttack());
			if (c->getHP() <= 0)
			{
				std::cout << "im BM , you die" << std::endl;
				break;
			}
		}


		switch (selection)
		{
		case(1) : 
			CheckThrough = 1;
			
			std::cout << "플레이어 공격 : " << c->getATK() << std::endl;
			tmp->TakeDamage(c->getATK());
			if(tmp->GetHealth() <= 0)
			{ 
				std::cout << "획득경험치 : 40 ";
				c->setEXP(50);

				int gold = GenerateRandom(10, 20);
				cout << "획득 골드" << gold << endl;
				c->increaseGold(gold);

				shared_ptr<Item> tmpItem = tmp->DropItem();

				if (tmpItem != nullptr)
				{
					std::cout << "item : " << tmpItem->getName();
					std::cout << "\n";
				}
				else 
				{
					std::cout << "몬스터 드랍 아무것도 안됨" << std::endl;
				}

				CheckThrough = 100;
				InvenSelection = 0;
				break;
			}
			c->takeDamage(tmp->GetAttack());
			if (c->getHP() <= 0)
			{
				std::cout << "im BM , you die" << std::endl;
				CheckThrough = 100;
				InvenSelection = 0;
				break;
			}

			InvenSelection = 0;
			break;

		case(2):
			

			
			
			c->displayInventory();
			std::cout << "사용할 아이템을 고르세요" << std::endl;
			std::cout << "인벤토리 닫기는 9을 써주세요 ! " << std::endl;
			std::cin >> InvenSelection;

		
			if (InvenSelection == 9)
			{
				CheckThrough = 0;
				break;
			}
			c->useItem(InvenSelection);
			CheckThrough = 1;
			break;
			


		case(3) : // 도망가기
			
			// 실패 한대 얻어맞고 또 확률적으로 얻어맞고 
			if (IsCreateEvent(50))
			{
				CheckThrough = 100;
				std::cout << "탈출 성공 축하드려요 ㅎㅎ" << std::endl;
				//이건 전투를 탈출하는거니깐  전투 전으로 
				InvenSelection = 0;
				fled = true;
				break;
			}
			

			std::cout << "도망 실패 일단 한대 맞아 그리고  10골드를 내놔 " << std::endl;
			// set gold c->
			c->takeDamage(tmp->GetAttack());
			if (c->getHP() <= 0)
			{
				CheckThrough = 100;
				std::cout << "im BM , you die" << std::endl;
				InvenSelection = 0;
				fled = false;
				break;
			}

			if (c->getGold() < 10) {
				std::cout << "돈 없음 플레이어" << std::endl;
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
			std::cout << "제대로 번호를 고르세요 " << std::endl;
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

/**Refactoring Battle*/
int BattleManager::MonsterBattle(Character* c) 
{
	int InvenSelection = 1000;
	shared_ptr<Monster> monster = monsterFactory.CreateMonster(c->getLevel());
	std::cout << "일반 몬스터..그르르릉 드장! 내 이름은?!!! : " << monster->GetName() << std::endl;
	int BattleResult = HandleBattle(c, monster);
	return BattleResult;
}
int BattleManager::BossBattle(Character* c)
{

	int InvenSelection = 1000;
	//몬스터 생성
	shared_ptr<Monster> boss = bossMonsterFactory.CreateBossMonster(c->getLevel());
	std::cout << "보스 몬스터..그르르릉 드장! 내 이름은?!!! : " << boss->GetName() << std::endl;
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
		std::cout << " //////////////////////" << std::endl;

		//기존 CHECK!=0
		if (IsCreateEvent(30) && CheckThrough == 1 ) {
			std::cout << monster->GetName() << " 선 공격!" << std::endl;
			//몬스터가 중독공격 &&플레이어 일반 상태
			//HandlePoison과 중복사용하는 이유는
			//플레이어 턴에만 중독 데미지를 주기 위해서
			if (IsPoisonAttack(monster) && !c->isPoison())
			{
				std::cout << "플레이어가 중독되었습니다!" << std::endl;
				c->setPoison(true); // 플레이어 상태를 중독으로 변경
			}
			IsDefeat = HandleMonsterAttack(c, monster);
			if (IsDefeat)
			{
				return 2;
			}
			std::cout << "선 공격 후 스테이터스 " << std::endl;
			c->displayStatus();
		}
		PrintSelection();
		std::cout << "만일..도망가기를 실패한다면...많이 맞을 수 있소.. 거기에 골드도 떨어지오..\n";
		std::cin >> selection;

		

		switch (selection) {
		case 1: { // 공격
			CheckThrough = 1;
			std::cout << "플레이어 공격 : " << c->getATK() << std::endl;
			
			IsWin = HandlePlayerAttack(c, monster);
			if (!IsWin && c->getHP() <= 0)
			{
				return 2;
			}
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
			
			std::cout << " 1번 선택 후 몬스터한테 맞고 난 뒤의 스테이터스 " << std::endl;
			c->displayStatus();


			break;
		}
		case 2: { // 아이템 사용
			c->displayInventory();
			std::cout << "사용할 아이템을 고르세요 (인벤토리 닫기는 9): " << std::endl;
			std::cin >> InvenSelection;

			if (InvenSelection == 9) {
				CheckThrough = 0;
				break;
			}
			c->useItem(InvenSelection);
			CheckThrough = 1;
			break;
		}
		case 3: { // 도망가기
			CheckThrough = 1;

			if (IsCreateEvent(50)) {
				std::cout << "탈출 성공!" << std::endl;
				return 3; // 전투 종료 (탈출)
			}

			std::cout << "도망 실패! 한 대 맞고 10골드를 잃습니다." << std::endl;
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
			std::cout << "잘못된 선택입니다. 다시 입력해주세요." << std::endl;
			break;
		}
	}
}
void BattleManager::PrintSelection() 
{
	std::cout << "1 : 공격 "
		 <<"   " << "2 : 아이템 사용" // Inventory
		<< "   " << "3 : 도망가기"
		<< "   " << "4 : 스테이터스 확인"
		<< std::endl;;
}
bool BattleManager::HandlePlayerAttack(Character* c, shared_ptr<Monster> monster)
{
	if (c->isPoison()) {
		// 플레이어 중독상태
		c->displayStatus();
		std::cout << "중독으로 인해 추가 데미지 1이 들어옵니다." << std::endl;
		c->takeDamage(120); // 중독으로 인해 1 데미지
		c->displayStatus();
		if (c->getHP() <= 0)
		{
			return false;
		}

	}
	monster->TakeDamage(c->getATK());
	if (monster->GetHealth() <= 0) {
		std::cout << "몬스터 처치! 경험치와 골드를 획득했습니다." << std::endl;
		c->setEXP(50);

		int gold = GenerateRandom(10, 20);
		c->increaseGold(gold);
		std::cout << "획득 골드: " << gold << std::endl;

		shared_ptr<Item> droppedItem = monster->DropItem();
		if (droppedItem) {
			std::cout << "아이템 획득: " << droppedItem->getName() << "\n";
		}
		else {
			std::cout << "몬스터가 아이템을 드롭하지 않았습니다." << std::endl;
		}
		//check
		std::cout << "몬스터 사망 후 스테이터스" << std::endl;
		c->displayStatus();
		return true; // 몬스터 사망
	}
	else return false;
}
bool BattleManager::HandleMonsterAttack(Character* c, shared_ptr<Monster> monster)
{
	if (IsPoisonAttack(monster) && !c->isPoison()) {
		// 몬스터가 독공격 && 플레이어 일반상태
		std::cout << "플레이어가 중독되었습니다!" << std::endl;
		c->setPoison(true); // 플레이어 상태를 중독으로 변경
	}

	std::cout << monster->GetName() << " 의 공격 ! 데미지 : "<<monster->GetAttack() << "를 입습니다." << std::endl;
	c->takeDamage(monster->GetAttack());
	if (c->getHP() <= 0) {
		std::cout << "플레이어가 사망했습니다." << std::endl;
		return true; // 플레이어 사망
	}
	else return false;
}
bool BattleManager::IsPoisonAttack(shared_ptr<Monster> monster) 
{
	
	if (monster->IsPoison())
	{
		return true;
	}
	return false;
}

//void addRecord(const std::string& result, const std::string& monsterName, int playerHP, int gold, int exp) {
//	records.push_back({ result, monsterName, playerHP, gold, exp });
//}

//void BattleManager::showRecords() const
//{
//
//}
