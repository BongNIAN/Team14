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
	bool fled;//���������� ���� �߰�
	/**��ȯ�� Shop Shared_ptr ���ο��� �־��ּ��� */
	
private:
	

};


#endif