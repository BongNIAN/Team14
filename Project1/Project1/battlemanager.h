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
	
	BattleManager() : fled(false) {}
	bool fled;

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

	//void addRecord(const std::string& result, const std::string& monsterName, int playerHP, int gold, int exp);
	//
	void showRecords() const;
	/**��Ʋ ȭ�� ���*/
	void PrintSelection();
private:
	MonsterFactory monsterFactory;
	BossMonsterFactory bossMonsterFactory;
	/*std::vector<Record> records;*/

};

//struct Record {
//	std::string result;  // �¸�/�й�
//	std::string monsterName;  // ���� �̸�
//	int playerHP;  // ���� ���� �� �÷��̾� HP
//	int goldEarned;  // ȹ���� ���
//	int experienceGained;  // ȹ���� ����ġ
//};



#endif