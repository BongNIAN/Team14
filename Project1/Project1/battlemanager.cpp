#include "battlemanager.h"
#include "print.h"
#include "random.h" 
#include "stageManager.h"



int BattleManager::MonsterBattle(Character* c) 
{
	MonsterFactory m;
	
	int InvenSelection = 1000;
	shared_ptr<Monster> monster = m.CreateMonster(c->getLevel());
	cout << "어둠속에서 안개가 형태를 갖추더니 몬스터가 되었다!!저건" << monster->GetName() << "!!" << endl;
	int BattleResult = HandleBattle(c, monster);
	if (!fled) {
		c->increasebattleCount(); //전투 횟수 증가
		StageManager stageManager;
		stageManager.checkStageUp(c); // 스테이지를 올릴지 확인
	}
	return BattleResult;
	
}
int BattleManager::BossBattle(Character* c)
{   
	BossMonsterFactory m;
	int InvenSelection = 1000;
	//몬스터 생성
	shared_ptr<Monster> boss = m.CreateBossMonster(c->getLevel());
	cout << "좀비들의 시체들이 서로 뒤엉키더니 용의 형상이 되었다...저건..." << boss->GetName() << "!!!" << endl;
	int BattleResult = HandleBattle(c, boss);
	if (!fled) {
		c->increasebattleCount(); //전투 횟수 증가
		StageManager stageManager;
		stageManager.checkStageUp(c); // 스테이지를 올릴지 확인
	
	}

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
		if (IsCreateEvent(30) && CheckThrough == 1) {
			cout << monster->GetName() << " 기습!" << endl;
			IsDefeat = HandleMonsterAttack(c, monster);
			if (IsPoisonAttack(monster) && !c->isPoison())
			{
				std::cout << "플레이어가 중독되었습니다!" << std::endl;
				c->setPoison(true); // 플레이어 상태를 중독으로 변경
			}
			IsDefeat = HandleMonsterAttack(c, monster);
			if (IsDefeat)
			{
				addRecord("Defeat", monster->GetName(), 0, 0, 0);
				return 2;
			}
			cout << "공격 후 스테이터스 " << endl;
			c->displayStatus();
		}
		PrintSelection();
		cout << "만일..도망가기를 실패한다면..." << endl;
		cout << "많은 피해를 입을꺼같다... 신중하게 선택하자..." << endl;
		
		cin >> selection;

		

		switch (selection) {
		case 1: { // 공격
			CheckThrough = 1;
			cout << "플레이어 공격! " << c->getATK() << "의 데미지!" << endl;
			
			IsWin = HandlePlayerAttack(c, monster);
			if (!IsWin && c->getHP() <= 0)
			{
				addRecord("Defeat", monster->GetName(), 0, 0, 0);
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
				addRecord("Defeat", monster->GetName(), 0, 0, 0);
				return 2;
			}
			
			cout << " 전투 후 스테이터스 " << endl;
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
			c->useItem(InvenSelection);
			CheckThrough = 1;
			break;
		}

		case 3: { // 상태 확인
			c->displayStatus();
			CheckThrough = 0;
			break;
		}

		case 4: { // 도망가기
			CheckThrough = 1;

			if (IsCreateEvent(50)) {
				cout << "가까스로 전에 있던 방으로 도망쳤다...다행히 피해는 없는것 같다.." << endl;

				StageManager stageManager;
				stageManager.setstageUpWhenFlee(false);
				
				fled = true;
				addRecord("Run", monster->GetName(), 0, 0, 0);
				return 3; // 전투 종료
			}

			cout << "크윽! 몬스터를 뿌리칠 수가 없어! 빈틈을 보여 공격당했어!" << endl;
			IsDefeat = HandleMonsterAttack(c, monster);
			if (IsDefeat)
			{
				addRecord("Defeat", monster->GetName(), 0, 0, 0);
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
		case 5: {
			showRecords();
			CheckThrough = 0;
			break;
		}
		default:
			cout << "잘못된 선택이야. 다시 입력해줘." << endl;
			break;
		}
	}

}
void BattleManager::PrintSelection() 
{
	cout << " ===================================" << endl;
	cout << "ㅣ         무엇을 할까요?          ㅣ" << endl;
	cout << " ===================================" << endl;
	cout << "ㅣ       1. 몬스터를 공격한다!     ㅣ" << endl;
	cout << "ㅣ          2. 인벤토리            ㅣ" << endl;
	cout << "ㅣ       3. 캐릭터 상태 확인       ㅣ" << endl;
	cout << "ㅣ          4. 도망간다            ㅣ" << endl;
	cout << "ㅣ       5. 전적 확인(미구현)      ㅣ" << endl;
	cout << " ===================================" << endl;
}

bool BattleManager::HandlePlayerAttack(Character* c, shared_ptr<Monster> monster)
{
	if (c->isPoison()) {
		// 플레이어 중독상태
		c->displayStatus();
		std::cout << "중독으로 인해 추가 데미지 1이 들어옵니다." << std::endl;
		c->takeDamage(1); // 중독으로 인해 1 데미지
		c->displayStatus();
		if (c->getHP() <= 0)
		{
			return false;
		}

	}
	monster->TakeDamage(c->getATK());
	if (monster->GetHealth() <= 0) {
		cout << "몬스터 처치! 경험치와 골드를 얻었다." << endl;
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
		addRecord("Victory", monster->GetName(), c->getHP(), gold, 50);
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

	cout << monster->GetName() << " 의 공격! "<<monster->GetAttack() << " 의 데미지!" << endl;
	c->takeDamage(monster->GetAttack());
	if (c->getHP() <= 0) {
		cout << "플레이어가 사망했습니다." << endl;
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
void BattleManager::addRecord(const std::string& result, const std::string& monsterName, int playerHP, int goldEarned, int experienceGained) {
	record[recordsCnt].result = result;
	record[recordsCnt].monsterName = monsterName;
	record[recordsCnt].playerHP = playerHP;
	record[recordsCnt].goldEarned = goldEarned;
	record[recordsCnt].experienceGained = experienceGained;
	recordsCnt++;
}
void BattleManager::showRecords() const
{
	if (recordsCnt == 0)
	{
		std::cout << "전투 전적이 없습니다." << std::endl;
		return;
	}
	for (int i = 0; i < recordsCnt; i++)
	{
		std::cout << "결과: " << record[i].result << ", 몬스터: " << record[i].monsterName
			<< ", 플레이어 HP: " << record[i].playerHP
			<< ", 획득 골드: " << record[i].goldEarned
			<< ", 획득 경험치: " << record[i].experienceGained << std::endl;
	}
}

