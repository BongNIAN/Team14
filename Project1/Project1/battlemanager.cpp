#include "battlemanager.h"
#include "print.h"
#include "random.h" 

//�̺κ� ���ϰ� �ʿ��Ұ� ���� �÷��̾ �׾����� 
//���Ͱ� �׾������� Ȯ���� ��ǥ�� �ʿ��� 
//�������Ϳ� �Ϲݸ��� ��Ʋ�� �ٸ� �� �����ϱ� ���� ���� �����ؾ��ϳ�?
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

			//���� �������� ����ִٸ�  invenselection 0 ���� 
			//�κ��丮 ������ ���� 
			//�̰� �˻������� �����ؾ��ҵ�?
			//���� ���ͷ� ���� ���ͷ� ��ȸ�� �ϱ⶧����
			//�ε��� ������ �߻��� 
			//map���� �ٲ���ҵ� 
			//�׸��� shop���� ���� �ε����� �´��� üũ�ѹ� �غ��� 
			//���Ͱ� ���� �� Ȯ�������� ���� �ɸ��� �Ѵ�
			//���� �ɷȴٸ� ? ���Ϳ��� ���ݹ��� �� 
			if (InvenSelection == 9)
			{
				CheckThrough = 0;
				break;
			}
			c->useItem(1);
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
		if (CheckThrough==100 )break;
		
	
		
	}



}


void BattleManager::PrintSelection() 
{
	cout << "1 : ���� " 
		 <<"   " << "2 : ������ ���" // Inventory
		<< "   " << "3 : ��������"
		<< "   " << "4 : �������ͽ� Ȯ��"
		<< endl;;
}

