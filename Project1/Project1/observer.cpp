#include "Observer.h" 
#include "print.h" 
#include <iostream> 


void PlayerObserver::UpdatePlayer(const PlayerHp playerHp) {
    drawHpBar(playerHp.CurrentHp, playerHp.MaxHp);
}

void GameOverHandler::UpdatePlayer(PlayerHp playerHp) {
    if (playerHp.CurrentHp <= 0) {
        printBossMonster();
        PrintLine("uhahahahah");
    }
}


