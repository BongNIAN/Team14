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

    

    bool getnextStage() const {
        return stageUpWhenFlee;
    }

    void setnextStage(bool value) {
        stageUpWhenFlee = value;
    }

    bool getstageUpWhenFlee() const {
        return stageUpWhenFlee;
    }

    // stageUpWhenFlee ���� �����ϴ� setter
    void setstageUpWhenFlee(bool value) {
        stageUpWhenFlee = value;
    }
    void startStage(Character* c); // �������� ���� �Լ�
    bool isStageClear(Character* c); // �������� Ŭ���� ���� Ȯ��
    void checkStageUp(Character* c); // ���� Ƚ���� ���� �������� ���
    void battleStage(Character* c);
    
private:
    int currentStage; // ���� �������� ��ȣ
    void nextStage(); // ���� ���������� ����
    void bossStage(Character* c);
    bool stageUpWhenFlee; // ���� ���� �� �������� ��� ����
};

#endif
