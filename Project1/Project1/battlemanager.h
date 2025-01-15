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
	bool fled;//도망갔는지 여부 추가
	/**반환형 Shop Shared_ptr 메인에서 넣어주세요 */
	
private:
	

};


#endif