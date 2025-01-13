#include <iostream>
#include "monster.h"
#include "random.h"

int main() {
    InitializeRandom();

    BossMonsterFactory boss;
    MonsterFactory monst;

    for (int i = 0; i < 100; i++) {
        boss.CreateBossMonster(i);
    }
    for (int i = 0; i < 100; i++) {
        monst.CreateMonster(i);
    }

    return 0;
}
