#include "battlemanager.h"
#include "print.h"
#include "random.h" 
#include "stageManager.h"
#include <memory>
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
		std::cout << "����..�������⸦ �����Ѵٸ�..."
			<< "���� ���� �� �ּ�.. �ű⿡ ��嵵 ��������.."
			<< std::endl;

		std::cin >> selection;

		if (IsCreateEvent(30) && CheckThrough != 0)
		{
			std::cout << "���� �� ����!" << std::endl;
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
			
			std::cout << "�÷��̾� ���� : " << c->getATK() << std::endl;
			tmp->TakeDamage(c->getATK());
			if(tmp->GetHealth() <= 0)
			{ 
				std::cout << "ȹ�����ġ : 40 ";
				c->setEXP(50);

				int gold = GenerateRandom(10, 20);
				cout << "ȹ�� ���" << gold << endl;
				c->increaseGold(gold);

				shared_ptr<Item> tmpItem = tmp->DropItem();

				if (tmpItem != nullptr)
				{
					std::cout << "item : " << tmpItem->getName();
					std::cout << "\n";
				}
				else 
				{
					std::cout << "���� ��� �ƹ��͵� �ȵ�" << std::endl;
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
			std::cout << "����� �������� ������" << std::endl;
			std::cout << "�κ��丮 �ݱ�� 9�� ���ּ��� ! " << std::endl;
			std::cin >> InvenSelection;

		
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
				std::cout << "Ż�� ���� ���ϵ���� ����" << std::endl;
				//�̰� ������ Ż���ϴ°Ŵϱ�  ���� ������ 
				InvenSelection = 0;
				fled = true;
				break;
			}
			

			std::cout << "���� ���� �ϴ� �Ѵ� �¾� �׸���  10��带 ���� " << std::endl;
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
				std::cout << "�� ���� �÷��̾�" << std::endl;
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
			std::cout << "����� ��ȣ�� ������ " << std::endl;
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
	std::cout << "�Ϲ� ����..�׸����� ����! �� �̸���?!!! : " << monster->GetName() << std::endl;
	int BattleResult = HandleBattle(c, monster);
	return BattleResult;
}
int BattleManager::BossBattle(Character* c)
{

	int InvenSelection = 1000;
	//���� ����
	shared_ptr<Monster> boss = bossMonsterFactory.CreateBossMonster(c->getLevel());
	std::cout << "���� ����..�׸����� ����! �� �̸���?!!! : " << boss->GetName() << std::endl;
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
		std::cout << " //////////////////////" << std::endl;

		//���� CHECK!=0
		if (IsCreateEvent(30) && CheckThrough == 1 ) {
			std::cout << monster->GetName() << " �� ����!" << std::endl;
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
				return 2;
			}
			std::cout << "�� ���� �� �������ͽ� " << std::endl;
			c->displayStatus();
		}
		PrintSelection();
		std::cout << "����..�������⸦ �����Ѵٸ�...���� ���� �� �ּ�.. �ű⿡ ��嵵 ��������..\n";
		std::cin >> selection;

		

		switch (selection) {
		case 1: { // ����
			CheckThrough = 1;
			std::cout << "�÷��̾� ���� : " << c->getATK() << std::endl;
			
			IsWin = HandlePlayerAttack(c, monster);
			if (!IsWin && c->getHP() <= 0)
			{
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
				return 2;
			}
			
			std::cout << " 1�� ���� �� �������� �°� �� ���� �������ͽ� " << std::endl;
			c->displayStatus();


			break;
		}
		case 2: { // ������ ���
			c->displayInventory();
			std::cout << "����� �������� ������ (�κ��丮 �ݱ�� 9): " << std::endl;
			std::cin >> InvenSelection;

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
				std::cout << "Ż�� ����!" << std::endl;
				return 3; // ���� ���� (Ż��)
			}

			std::cout << "���� ����! �� �� �°� 10��带 �ҽ��ϴ�." << std::endl;
			IsDefeat = HandleMonsterAttack(c, monster);
			if (IsDefeat)
			{
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
		default:
			std::cout << "�߸��� �����Դϴ�. �ٽ� �Է����ּ���." << std::endl;
			break;
		}
	}
}
void BattleManager::PrintSelection() 
{
	std::cout << "1 : ���� "
		 <<"   " << "2 : ������ ���" // Inventory
		<< "   " << "3 : ��������"
		<< "   " << "4 : �������ͽ� Ȯ��"
		<< std::endl;;
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
		std::cout << "���� óġ! ����ġ�� ��带 ȹ���߽��ϴ�." << std::endl;
		c->setEXP(50);

		int gold = GenerateRandom(10, 20);
		c->increaseGold(gold);
		std::cout << "ȹ�� ���: " << gold << std::endl;

		shared_ptr<Item> droppedItem = monster->DropItem();
		if (droppedItem) {
			std::cout << "������ ȹ��: " << droppedItem->getName() << "\n";
		}
		else {
			std::cout << "���Ͱ� �������� ������� �ʾҽ��ϴ�." << std::endl;
		}
		//check
		std::cout << "���� ��� �� �������ͽ�" << std::endl;
		c->displayStatus();
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

	std::cout << monster->GetName() << " �� ���� ! ������ : "<<monster->GetAttack() << "�� �Խ��ϴ�." << std::endl;
	c->takeDamage(monster->GetAttack());
	if (c->getHP() <= 0) {
		std::cout << "�÷��̾ ����߽��ϴ�." << std::endl;
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

//void addRecord(const std::string& result, const std::string& monsterName, int playerHP, int gold, int exp) {
//	records.push_back({ result, monsterName, playerHP, gold, exp });
//}

//void BattleManager::showRecords() const
//{
//
//}
