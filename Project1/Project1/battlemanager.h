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
	
	BattleManager() : fled(false) {}
	bool fled;

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

	/**배틀 화면 출력*/
	void PrintSelection();
private:
	

};


#endif