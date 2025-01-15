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
	void Battle(Character* c);
	void PrintSelection();
<<<<<<< Updated upstream

	int BossBattle(Character* c);
	int MonsterBattle(Character* c);
	int HandleBattle(Character* c, shared_ptr<Monster> monster);
	bool HandlePlayerAttack(Character* c, shared_ptr<Monster> monster);
	bool HandleMonsterAttack(Character* c, shared_ptr<Monster> monster);
	bool fled;
	

=======
	bool fled;//도망갔는지 여부 추가
	
	// 1 또는 10 스테이지에서만 이벤트 발생
	
	
	/**반환형 Shop Shared_ptr 메인에서 넣어주세요 */
>>>>>>> Stashed changes
	
private:
	

};


#endif