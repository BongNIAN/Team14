#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include <memory>
#include "monster.h"
#include "Character.h"
#include "shop.h"

//class Character;
class Monster;




class BattleManager {
public:
	struct Record {
		std::string result = "";  // �¸�/�й�
		std::string monsterName = "";  // ���� �̸�
		int playerHP = 0;  // ���� ���� �� �÷��̾� HP
		int goldEarned = 0;  // ȹ���� ���
		int experienceGained = 0;  // ȹ���� ����ġ
	};
	bool fled;

	BattleManager() : recordsCnt(0), maxRecordsCnt(1000)
	{
		fled = false;
		recordsCnt = 0;
		record = new Record[maxRecordsCnt];
	}
	~BattleManager()
	{
		delete[] record;
	}

	/**�ӽ� �����*/
	void Battle(Character* c);
	/**�������� ����*/
	int BossBattle(Character* c);
	/**�Ϲ� ���Ϳ��� ����*/
	int MonsterBattle(Character* c);
	/**��ü���� ��Ʋ ���� */
	int HandleBattle(Character* c, shared_ptr<Monster> monster);
	/**�÷��̾� ���ݽ� ����*/
	bool HandlePlayerAttack(Character* c, shared_ptr<Monster> monster);
	/**���� ���ݽ� ����*/
	bool HandleMonsterAttack(Character* c, shared_ptr<Monster> monster);
	/**���Ͱ� �ߵ��� �Ŵ� ������ �ߴ��� üũ*/
	
	bool IsPoisonAttack(shared_ptr<Monster> monster);

	//������ ��ǰ�̶� ������ ������Ű�ڽ��ϴ�
	//��ȯ ������ ���� ���� ����� ������� �迭�� �����߽��ϴ�.
	void addRecord(const std::string& result, const std::string& monsterName, int playerHP, int gold, int exp);
	
	//������ ��ǰ�̶� ������ ������Ű�ڽ��ϴ�.
	void showRecords() const;

	/**��Ʋ ȭ�� ���*/
	void PrintSelection();

private:
	MonsterFactory monsterFactory;
	BossMonsterFactory bossMonsterFactory;
	Record* record;
	int recordsCnt;
	int maxRecordsCnt;
};





#endif