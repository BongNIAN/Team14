#pragma once
#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include "Character.h"
#include "battleManager.h"
#include <memory>
#include <iostream>

class StageManager {
public:
    StageManager();
    ~StageManager();

    void startStage(Character* c); // 스테이지 시작 함수
    bool isStageClear(Character* c); // 스테이지 클리어 여부 확인
    void checkStageUp(Character* c); // 전투 횟수에 따른 스테이지 상승

private:
    int currentStage; // 현재 스테이지 번호
    void battleStage(Character* c); // 전투 스테이지
    void bossStage(Character* c);   // 보스 스테이지
    void nextStage(); // 다음 스테이지로 진행
    bool stageUpWhenFlee; // 도망 갔을 때 스테이지 상승 여부
};

#endif
