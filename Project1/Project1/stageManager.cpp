#include "StageManager.h"
#include "monster.h"
#include "battleManager.h"
#include "random.h"
#include "Character.h"

StageManager::StageManager() : currentStage(1), stageUpWhenFlee(true) {}

StageManager::~StageManager() {}

void StageManager::startStage(Character* c) {
    std::cout << "현재 스테이지: " << currentStage << std::endl;

    checkStageUp(c); // 전투 횟수에 따라 스테이지 업 체크

    if (isStageClear(c)) {
        nextStage();
    }
    else {
        if (currentStage == 1) {
            battleStage(c);
        }
        else if (currentStage == 2) {
            battleStage(c);
        }
        else if (currentStage == 3) {
            bossStage(c);
        }
    }
}

bool StageManager::isStageClear(Character* c) {
    // 스테이지 클리어 여부를 판단하는 로직
    if (c->getHP() > 0 && c->getEXP() >= currentStage * 50) {
        std::cout << "스테이지 클리어!" << std::endl;
        return true;
    }
    return false;
}

void StageManager::battleStage(Character* c) {
    // 일반 전투 스테이지
    BattleManager battleManager;
    battleManager.Battle(c); // BattleManager를 통해 전투 진행

    // 전투가 끝난 후 도망 갔을 때는 스테이지가 상승하지 않도록 처리
    if (battleManager.fled) {
        stageUpWhenFlee = false;
    }

    c->increasebattleCount(); // 전투 횟수 증가
}

void StageManager::bossStage(Character* c) {
    // 보스 전투 스테이지
    std::cout << "보스가 나타났습니다!" << std::endl;
    BattleManager battleManager;
    battleManager.Battle(c); // 보스 전투

    // 전투가 끝난 후 도망 갔을 때는 스테이지가 상승하지 않도록 처리
    if (battleManager.fled) {
        stageUpWhenFlee = false;
    }

    c->increasebattleCount(); // 전투 횟수 증가
}

void StageManager::nextStage() {
    // 도망쳤을 경우 스테이지 상승을 막음
    if (stageUpWhenFlee) {
        currentStage++; // 현재 스테이지를 증가
    }
    else {
        std::cout << "도망쳤으므로 스테이지는 상승하지 않습니다." << std::endl;
    }

    std::cout << "다음 스테이지로 이동합니다!" << std::endl;
    stageUpWhenFlee = true; // 상태 초기화
}

void StageManager::checkStageUp(Character* c) {
    // 전투 횟수에 따라 스테이지 업 여부 확인
    int battlesRequiredForNextStage = currentStage * 5; // 예시: 각 스테이지당 5번의 전투가 필요
    if (c->getBattleCount() >= battlesRequiredForNextStage) {
        std::cout << "전투 횟수로 인해 스테이지가 상승합니다!" << std::endl;
        nextStage(); // 전투 횟수에 따라 스테이지 업
    }
}
