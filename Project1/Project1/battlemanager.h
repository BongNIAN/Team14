#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include<memory>
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
	
	
	void PrintSelection();

	int BossBattle(Character* c);
	int MonsterBattle(Character* c);
	int HandleBattle(Character* c, shared_ptr<Monster> monster);
	bool HandlePlayerAttack(Character* c, shared_ptr<Monster> monster);
	bool HandleMonsterAttack(Character* c, shared_ptr<Monster> monster);

	bool IsPoisonAttack(shared_ptr<Monster> monster);
	void addRecord(const std::string& result, const std::string& monsterName, int playerHP, int gold, int exp);
	void showRecords() const;


private:
	MonsterFactory monsterFactory;
	BossMonsterFactory bossMonsterFactory;
	Record* record;
	int recordsCnt;
	int maxRecordsCnt;

};


#endif