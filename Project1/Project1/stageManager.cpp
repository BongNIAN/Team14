#include "StageManager.h"
#include "monster.h"
#include "battleManager.h"
#include "random.h"
#include "Character.h"

StageManager::StageManager() : currentStage(1), stageUpWhenFlee(true) {}

StageManager::~StageManager() {}

void StageManager::startStage(Character* c) {
    std::cout << "���� ��������: " << currentStage << std::endl;

    checkStageUp(c); // ���� Ƚ���� ���� �������� �� üũ

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
    // �������� Ŭ���� ���θ� �Ǵ��ϴ� ����
    if (c->getHP() > 0 && c->getEXP() >= currentStage * 50) {
        std::cout << "�������� Ŭ����!" << std::endl;
        return true;
    }
    return false;
}

void StageManager::battleStage(Character* c) {
    // �Ϲ� ���� ��������
    BattleManager battleManager;
    battleManager.Battle(c); // BattleManager�� ���� ���� ����

    // ������ ���� �� ���� ���� ���� ���������� ������� �ʵ��� ó��
    if (battleManager.fled) {
        stageUpWhenFlee = false;
    }

    c->increasebattleCount(); // ���� Ƚ�� ����
}

void StageManager::bossStage(Character* c) {
    // ���� ���� ��������
    std::cout << "������ ��Ÿ�����ϴ�!" << std::endl;
    BattleManager battleManager;
    battleManager.Battle(c); // ���� ����

    // ������ ���� �� ���� ���� ���� ���������� ������� �ʵ��� ó��
    if (battleManager.fled) {
        stageUpWhenFlee = false;
    }

    c->increasebattleCount(); // ���� Ƚ�� ����
}

void StageManager::nextStage() {
    // �������� ��� �������� ����� ����
    if (stageUpWhenFlee) {
        currentStage++; // ���� ���������� ����
    }
    else {
        std::cout << "���������Ƿ� ���������� ������� �ʽ��ϴ�." << std::endl;
    }

    std::cout << "���� ���������� �̵��մϴ�!" << std::endl;
    stageUpWhenFlee = true; // ���� �ʱ�ȭ
}

void StageManager::checkStageUp(Character* c) {
    // ���� Ƚ���� ���� �������� �� ���� Ȯ��
    int battlesRequiredForNextStage = currentStage * 5; // ����: �� ���������� 5���� ������ �ʿ�
    if (c->getBattleCount() >= battlesRequiredForNextStage) {
        std::cout << "���� Ƚ���� ���� ���������� ����մϴ�!" << std::endl;
        nextStage(); // ���� Ƚ���� ���� �������� ��
    }
}
