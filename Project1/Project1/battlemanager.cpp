#include "battlemanager.h"
#include "print.h"
#include "random.h" 
#include "stageManager.h"



int BattleManager::MonsterBattle(Character* c) 
{
	MonsterFactory m;
	
	int InvenSelection = 1000;
	shared_ptr<Monster> monster = m.CreateMonster(c->getLevel());
	cout << "��Ҽӿ��� �Ȱ��� ���¸� ���ߴ��� ���Ͱ� �Ǿ���!!����" << monster->GetName() << "!!" << endl;
	int BattleResult = HandleBattle(c, monster);
	if (!fled) {
		c->increasebattleCount(); //���� Ƚ�� ����
		StageManager stageManager;
		stageManager.checkStageUp(c); // ���������� �ø��� Ȯ��
	}
	return BattleResult;
	
}
int BattleManager::BossBattle(Character* c)
{   
	BossMonsterFactory m;
	int InvenSelection = 1000;
	//���� ����
	shared_ptr<Monster> boss = m.CreateBossMonster(c->getLevel());
	cout << "������� ��ü���� ���� �ھ�Ű���� ���� ������ �Ǿ���...����..." << boss->GetName() << "!!!" << endl;
	int BattleResult = HandleBattle(c, boss);
	if (!fled) {
		c->increasebattleCount(); //���� Ƚ�� ����
		StageManager stageManager;
		stageManager.checkStageUp(c); // ���������� �ø��� Ȯ��
	
	}

	return BattleResult;
}



/**return 1 : victory, return 2 : defeat , return 3 : run */
/**checkThrough : 1. ������  , 0 : ������ ���� ����  */
int BattleManager::HandleBattle(Character* c, shared_ptr<Monster> monster) {
	int selection = 1000;
	int CheckThrough = 1;
	int InvenSelection = 0;
	bool IsWin = false;
	bool IsDefeat = false;

	while (true) {
		if (IsCreateEvent(30) && CheckThrough == 1) {
			cout << monster->GetName() << " ���!" << endl;
			IsDefeat = HandleMonsterAttack(c, monster);
			if (IsPoisonAttack(monster) && !c->isPoison())
			{
				std::cout << "�÷��̾ �ߵ��Ǿ����ϴ�!" << std::endl;
				c->setPoison(true); // �÷��̾� ���¸� �ߵ����� ����
			}
			IsDefeat = HandleMonsterAttack(c, monster);
			if (IsDefeat)
			{
				addRecord("Defeat", monster->GetName(), 0, 0, 0);
				return 2;
			}
			cout << "���� �� �������ͽ� " << endl;
			c->displayStatus();
		}
		PrintSelection();
		cout << "����..�������⸦ �����Ѵٸ�..." << endl;
		cout << "���� ���ظ� ����������... �����ϰ� ��������..." << endl;
		
		cin >> selection;

		

		switch (selection) {
		case 1: { // ����
			CheckThrough = 1;
			cout << "�÷��̾� ����! " << c->getATK() << "�� ������!" << endl;
			
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
			//���ϰ� �޾ƿ��� 

			IsDefeat = HandleMonsterAttack(c, monster);
			if (IsDefeat) 
			{
				addRecord("Defeat", monster->GetName(), 0, 0, 0);
				return 2;
			}
			
			cout << " ���� �� �������ͽ� " << endl;
			c->displayStatus();


			break;
		}
		case 2: { // ������ ���
			c->displayInventory();
			cout << "����� �������� ������ (�κ��丮 �ݱ�� 9): " << endl;
			cin >> InvenSelection;

			if (InvenSelection == 9) {
				CheckThrough = 0;
				break;
			}
			c->useItem(InvenSelection);
			CheckThrough = 1;
			break;
		}

		case 3: { // ���� Ȯ��
			c->displayStatus();
			CheckThrough = 0;
			break;
		}

		case 4: { // ��������
			CheckThrough = 1;

			if (IsCreateEvent(50)) {
				cout << "����� ���� �ִ� ������ �����ƴ�...������ ���ش� ���°� ����.." << endl;

				StageManager stageManager;
				stageManager.setstageUpWhenFlee(false);
				
				fled = true;
				addRecord("Run", monster->GetName(), 0, 0, 0);
				return 3; // ���� ����
			}

			cout << "ũ��! ���͸� �Ѹ�ĥ ���� ����! ��ƴ�� ���� ���ݴ��߾�!" << endl;
			IsDefeat = HandleMonsterAttack(c, monster);
			if (IsDefeat)
			{
				addRecord("Defeat", monster->GetName(), 0, 0, 0);
				return 2;
			}

			//�����ݾ��� 10���� ������ ������ �ݾ� ���� ���� 
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
			cout << "�߸��� �����̾�. �ٽ� �Է�����." << endl;
			break;
		}
	}

}
void BattleManager::PrintSelection() 
{
	cout << " ===================================" << endl;
	cout << "��         ������ �ұ��?          ��" << endl;
	cout << " ===================================" << endl;
	cout << "��       1. ���͸� �����Ѵ�!     ��" << endl;
	cout << "��          2. �κ��丮            ��" << endl;
	cout << "��       3. ĳ���� ���� Ȯ��       ��" << endl;
	cout << "��          4. ��������            ��" << endl;
	cout << "��       5. ���� Ȯ��(�̱���)      ��" << endl;
	cout << " ===================================" << endl;
}

bool BattleManager::HandlePlayerAttack(Character* c, shared_ptr<Monster> monster)
{
	if (c->isPoison()) {
		// �÷��̾� �ߵ�����
		c->displayStatus();
		std::cout << "�ߵ����� ���� �߰� ������ 1�� ���ɴϴ�." << std::endl;
		c->takeDamage(1); // �ߵ����� ���� 1 ������
		c->displayStatus();
		if (c->getHP() <= 0)
		{
			return false;
		}

	}
	monster->TakeDamage(c->getATK());
	if (monster->GetHealth() <= 0) {
		cout << "���� óġ! ����ġ�� ��带 �����." << endl;
		c->setEXP(50);

		int gold = GenerateRandom(10, 20);
		c->increaseGold(gold);
		cout << "ȹ�� ���: " << gold << endl;

		shared_ptr<Item> droppedItem = monster->DropItem();
		if (droppedItem) {
			cout << "������ ȹ��: " << droppedItem->getName() << "\n";
		}
		else {
			cout << "���Ͱ� �������� ������� �ʾҽ��ϴ�." << endl;
		}
		addRecord("Victory", monster->GetName(), c->getHP(), gold, 50);
		return true; // ���� ���
	}
	else return false;
}
bool BattleManager::HandleMonsterAttack(Character* c, shared_ptr<Monster> monster)
{
	if (IsPoisonAttack(monster) && !c->isPoison()) {
		// ���Ͱ� ������ && �÷��̾� �Ϲݻ���
		std::cout << "�÷��̾ �ߵ��Ǿ����ϴ�!" << std::endl;
		c->setPoison(true); // �÷��̾� ���¸� �ߵ����� ����
	}

	cout << monster->GetName() << " �� ����! "<<monster->GetAttack() << " �� ������!" << endl;
	c->takeDamage(monster->GetAttack());
	if (c->getHP() <= 0) {
		cout << "�÷��̾ ����߽��ϴ�." << endl;
		return true; // �÷��̾� ���
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
		std::cout << "���� ������ �����ϴ�." << std::endl;
		return;
	}
	for (int i = 0; i < recordsCnt; i++)
	{
		std::cout << "���: " << record[i].result << ", ����: " << record[i].monsterName
			<< ", �÷��̾� HP: " << record[i].playerHP
			<< ", ȹ�� ���: " << record[i].goldEarned
			<< ", ȹ�� ����ġ: " << record[i].experienceGained << std::endl;
	}
}

