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
	bool fled;//���������� ���� �߰�
	
	// 1 �Ǵ� 10 �������������� �̺�Ʈ �߻�
	
	
	/**��ȯ�� Shop Shared_ptr ���ο��� �־��ּ��� */
>>>>>>> Stashed changes
	
private:
	

};


#endif