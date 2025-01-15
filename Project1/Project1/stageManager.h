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

    void startStage(Character* c); // �������� ���� �Լ�
    bool isStageClear(Character* c); // �������� Ŭ���� ���� Ȯ��
    void checkStageUp(Character* c); // ���� Ƚ���� ���� �������� ���

private:
    int currentStage; // ���� �������� ��ȣ
    void battleStage(Character* c); // ���� ��������
    void bossStage(Character* c);   // ���� ��������
    void nextStage(); // ���� ���������� ����
    bool stageUpWhenFlee; // ���� ���� �� �������� ��� ����
};

#endif
