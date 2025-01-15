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
	
	BattleManager() {}
	void Battle(Character* c);
	void PrintSelection();
	
	/**반환형 Shop Shared_ptr 메인에서 넣어주세요 */
	
private:
	

};


#endif