#include "battlemanager.h"
#include "print.h"
#include "random.h" 
#include "stageManager.h"

/** Ȥ�� ��������� ��ü�� ���Դϴ� ���� ���!*/
void BattleManager :: Battle(Character *c) 
{

	MonsterFactory m;
	int InvenSelection = 1000;
	//���� ����
	shared_ptr<Monster> tmp = m.CreateMonster(c->getLevel());
	int CheckThrough = 1;
	while (1)
	{

		int selection = 1000; // �ʱ�ȭ
		PrintSelection();
		cout << "����..�������⸦ �����Ѵٸ�..."
			<< "���� ���� �� �ּ�.. �ű⿡ ��嵵 ��������.."
			<< endl;

		cin >> selection;

		if (IsCreateEvent(30) && CheckThrough != 0)
		{
			cout << "���� �� ����!" << endl;
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
			
			cout << "�÷��̾� ���� : " << c->getATK() << endl;
			tmp->TakeDamage(c->getATK());
			if(tmp->GetHealth() <= 0)
			{ 
				cout << "ȹ�����ġ : 40 ";  
				c->setEXP(50);

				int gold = GenerateRandom(10, 20);
				cout << "ȹ�� ���" << gold << endl;
				c->increaseGold(gold);

				shared_ptr<Item> tmpItem = tmp->DropItem();

				if (tmpItem != nullptr)
				{
					cout << "item : " << tmpItem->getName();
					cout << "\n";
				}
				else 
				{
					cout << "���� ��� �ƹ��͵� �ȵ�" << endl;
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
			cout << "����� �������� ������" << endl;
			cout << "�κ��丮 �ݱ�� 9�� ���ּ��� ! " << endl;
			cin >> InvenSelection;

		
			if (InvenSelection == 9)
			{
				CheckThrough = 0;
				break;
			}
			c->useItem(InvenSelection);
			CheckThrough = 1;
			break;
			


		case(3) : // ��������
			
			// ���� �Ѵ� ���°� �� Ȯ�������� ���°� 
			if (IsCreateEvent(50))
			{
				CheckThrough = 100;
				cout << "Ż�� ���� ���ϵ���� ����" << endl;
				//�̰� ������ Ż���ϴ°Ŵϱ�  ���� ������ 
				InvenSelection = 0;
				fled = true;
				break;
			}
			

			cout << "���� ���� �ϴ� �Ѵ� �¾� �׸���  10��带 ���� " << endl;
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
				cout << "�� ���� �÷��̾�" << endl;
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
			cout << "����� ��ȣ�� ������ " << endl;
			InvenSelection = 0;
			break;
		}
		


		//�갡 ������� ���ƾ���
		if (CheckThrough == 100) {
			if (!fled) {
				c->increasebattleCount(); //���� Ƚ�� ����

				StageManager stageManager;
				stageManager.checkStageUp(c); // ���������� �ø��� Ȯ��
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
	cout << "�Ϲ� ����..�׸����� ����! �� �̸���?!!! : " << monster->GetName() << endl;
	int BattleResult = HandleBattle(c, monster);
	return BattleResult;
}
int BattleManager::BossBattle(Character* c)
{

	int InvenSelection = 1000;
	//���� ����
	shared_ptr<Monster> boss = bossMonsterFactory.CreateBossMonster(c->getLevel());
	cout << "���� ����..�׸����� ����! �� �̸���?!!! : " << boss->GetName() << endl;
	int BattleResult = HandleBattle(c, boss);
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
		cout << " //////////////////////" << endl;

		//���� CHECK!=0
		if (IsCreateEvent(30) && CheckThrough == 1 ) {
			cout << monster->GetName() << " �� ����!" << endl;
			//���Ͱ� �ߵ����� &&�÷��̾� �Ϲ� ����
			//HandlePoison�� �ߺ�����ϴ� ������
			//�÷��̾� �Ͽ��� �ߵ� �������� �ֱ� ���ؼ�
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
			cout << "�� ���� �� �������ͽ� " << endl;
			c->displayStatus();
		}
		PrintSelection();
		cout << "����..�������⸦ �����Ѵٸ�...���� ���� �� �ּ�.. �ű⿡ ��嵵 ��������..\n";
		cin >> selection;

		

		switch (selection) {
		case 1: { // ����
			CheckThrough = 1;
			cout << "�÷��̾� ���� : " << c->getATK() << endl;
			
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
			
			cout << " 1�� ���� �� �������� �°� �� ���� �������ͽ� " << endl;
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
		case 3: { // ��������
			CheckThrough = 1;

			if (IsCreateEvent(50)) {
				cout << "Ż�� ����!" << endl;
				addRecord("Run", monster->GetName(), 0, 0, 0);
				return 3; // ���� ���� (Ż��)
			}

			cout << "���� ����! �� �� �°� 10��带 �ҽ��ϴ�." << endl;
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
		case 4: { // ���� Ȯ��
			c->displayStatus();
			CheckThrough = 0;
			break;
		}
		case 5: 
		{
			showRecords();
			CheckThrough = 0;
			break;
		}
		default:
			cout << "�߸��� �����Դϴ�. �ٽ� �Է����ּ���." << endl;
			break;
		}
	}
}
void BattleManager::PrintSelection() 
{
	cout << "1 : ���� " 
		 <<"   " << "2 : ������ ���" // Inventory
		<< "   " << "3 : ��������"
		<< "   " << "4 : �������ͽ� Ȯ��"
		<< "   " << "5 : ���� �α� ���"
		<< endl;;
}
bool BattleManager::HandlePlayerAttack(Character* c, shared_ptr<Monster> monster)
{
	
	if (c->isPoison()) {
		// �÷��̾� �ߵ�����
		c->displayStatus();
		std::cout << "�ߵ����� ���� �߰� ������ 1�� ���ɴϴ�." << std::endl;
		c->takeDamage(120); // �ߵ����� ���� 1 ������
		c->displayStatus();
		if (c->getHP() <= 0)
		{
			return false;
		}

	}
	monster->TakeDamage(c->getATK());
	if (monster->GetHealth() <= 0) {
		cout << "���� óġ! ����ġ�� ��带 ȹ���߽��ϴ�." << endl;
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
		//check
		cout << "���� ��� �� �������ͽ�" << endl;
		c->displayStatus();
		addRecord("Victory", monster->GetName(),c->getHP(),gold,50);
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

	cout << monster->GetName() << " �� ���� ! ������ : "<<monster->GetAttack() << "�� �Խ��ϴ�." << endl;
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
