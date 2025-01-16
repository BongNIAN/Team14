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
		std::string result = "";  // 승리/패배
		std::string monsterName = "";  // 몬스터 이름
		int playerHP = 0;  // 전투 종료 시 플레이어 HP
		int goldEarned = 0;  // 획득한 골드
		int experienceGained = 0;  // 획득한 경험치
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

	/**임시 저장용*/
	void Battle(Character* c);
	/**보스와의 전투*/
	int BossBattle(Character* c);
	/**일반 몬스터와의 전투*/
	int MonsterBattle(Character* c);
	/**구체적인 배틀 로직 */
	int HandleBattle(Character* c, shared_ptr<Monster> monster);
	/**플레이어 공격시 로직*/
	bool HandlePlayerAttack(Character* c, shared_ptr<Monster> monster);
	/**몬스터 공격시 로직*/
	bool HandleMonsterAttack(Character* c, shared_ptr<Monster> monster);
	/**몬스터가 중독을 거는 공격을 했는지 체크*/
	
	bool IsPoisonAttack(shared_ptr<Monster> monster);

	//연진님 작품이라 기필코 성공시키겠습니다
	//순환 참조로 인해 벡터 사용이 어려워서 배열로 구현했습니다.
	void addRecord(const std::string& result, const std::string& monsterName, int playerHP, int gold, int exp);
	
	//연진님 작품이라 기필코 성공시키겠습니다.
	void showRecords() const;

	/**배틀 화면 출력*/
	void PrintSelection();

private:
	MonsterFactory monsterFactory;
	BossMonsterFactory bossMonsterFactory;
	Record* record;
	int recordsCnt;
	int maxRecordsCnt;
};





#endif