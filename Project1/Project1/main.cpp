#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "ItemManager.h"
#include "item.h"
#include "battlemanager.h"
#include "EventManager.h"
#include "stageManager.h"

using namespace std;

// ���� ���� �Լ�
void quitGame() {
    cout << "������ �ٽ� ���ƿò��� �Ͼ�!" << endl;
    exit(0); // ���� ����
}

void visitshop() {

}

// ���� ���� �Լ�
void startGame() {
    // ĳ���� �̸� �Է� �ޱ�
    string characterName;
    cout << "ũ��...�Ӹ���...���� �̸��� ������? : ";
    cin.ignore(); // cin���� �����ִ� ���� ���� ó��
    getline(cin, characterName); // �̸��� �� �ٷ� �Է¹ޱ�
    
    // Singleton�� ����Ͽ� Character ��ü ����
    Character* character = Character::getInstance(characterName);
    cout << "===============================================================================" << endl;
    cout << " �׷� ���� �̸��� " << characterName << "..." << endl;
    cout << "������� ���� �����̾���, �� ���� �ֱ� ������. "<< endl;
    cout << "���� �������� �̹� �ƹ��͵� ������ �ʴ� ĥ��ӿ� ���׷��� �����ִ� ��� ���� ���̾���. "<< endl;
    cout << "�ƹ��� ������ �ѷ����Ƶ� ���ư� ���� ������ �ʴ� ���ν�� �� ���� ���� ���ư��� ���ۿ� ����. "<< endl;         
    cout << "�� ��ۿ� ����.���ư�����." << endl;
    cout << "������ ������ �𸣴� �η����, Ż�ⱸ�� ���� �� �ִٴ� ����� ���� ���� ���� ��������." << endl;
    cout << "===============================================================================" << endl;
    int choice = 0;
    
    character->displayStatus();

  
    
    while (true) {
       
        int choice;
        cout << " ==================================" << endl;
        cout << "��         ������ �ұ��?         ��" << endl;
        cout << " ==================================" << endl;
        cout << "��      1. ���� ������ ����       ��" << endl;
        cout << "��      2. ĳ���� ���� ����       ��" << endl;
        cout << "��         3. ���� ����           ��" << endl;
        cout << " ==================================" << endl;

        cout << "�޴����� ���� : ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "���� ������ ���ϴ�..." << endl;
            {
                BattleManager battleManager;
                battleManager.MonsterBattle(character);  // ���� ����
                // 0�������� Ŭ���� �� ���� ���丮 ���
                EventManager::triggerStageEvent(character->getBattleCount());

            }
            break;
        case 2:
            character->displayStatus();  // ĳ���� ���� ����
            break;
        case 3:
            quitGame();   // ���� ����
            break;
        default:
            cout << "�߸��� �����̾�. �ٽ� �õ��� ��." << endl;
            startGame();  // �ٽ� ������ �� �� �ֵ���
            break;
        }
        
        while (character->getBattleCount() > 0&& character->getBattleCount() <18 ) {

            int choice;
            cout << " ===================================" << endl;
            cout << "��         ������ �ұ��?          ��" << endl;
            cout << " ===================================" << endl;
            cout << "��      1. ���� ������ ����        ��" << endl;
            cout << "��          2. �����湮            ��" << endl;
            cout << "��      3. ĳ���� ���� ����        ��" << endl;
            cout << "��          4. �κ��丮            ��" << endl;
            cout << "��          5. ��������            ��" << endl;
            cout << " ===================================" << endl;

            cout << "�޴����� ���� : ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "���� ������ ���ϴ�..." << endl;
                {
                    BattleManager battleManager;
                    battleManager.MonsterBattle(character);  // ���� ����
                    // 10�������� Ŭ���� �� ���� ���丮 ���
                    EventManager::triggerStageEvent(character->getBattleCount());

                }
                break;

            case 2:
                character->visitShop();
                break;

            case 3:
                character->displayStatus();  // ĳ���� ���� ����
                break;

            case 4:
                character->displayInventory();
                break;

            case 5:
                quitGame();   // ���� ����
                break;

            default:
                cout << "�߸��� �����̾�. �ٽ� �õ��� ��." << endl;
                startGame();  // �ٽ� ������ �� �� �ֵ���
                break;
            }


        }
        while (character->getBattleCount() ==18) {

            int choice;
            cout << " ===================================" << endl;
            cout << "��         ������ �ұ��?          ��" << endl;
            cout << " ===================================" << endl;
            cout << "��      1. ���� ������ ����        ��" << endl;
            cout << "��          2. �����湮            ��" << endl;
            cout << "��      3. ĳ���� ���� ����        ��" << endl;
            cout << "��          4. �κ��丮            ��" << endl;
            cout << "��          5. ��������            ��" << endl;
            cout << " ===================================" << endl;

            cout << "�޴����� ���� : ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "���� ������ ���ϴ�..." << endl;
                {
                    BattleManager battleManager;
                    battleManager.BossBattle(character);  // ���� ����
                    
                    EventManager::triggerStageEvent(character->getBattleCount());
                }
                break;

            case 2:
                character->visitShop();
                break;

            case 3:
                character->displayStatus();  // ĳ���� ���� ����
                break;

            case 4:
                character->displayInventory();
                break;

            case 5:
                quitGame();   // ���� ����
                break;

            default:
                cout << "�߸��� �����̾�. �ٽ� �õ��� ��." << endl;
                startGame();  // �ٽ� ������ �� �� �ֵ���
                break;
            }


        }
    }

}

// ���� �޴� ȭ�� �Լ�
void mainMenu() {
    int choice;

    cout << " ===================================" << endl;
    cout << "��          �ؽ�Ʈ �ҿ�            ��" << endl;
    cout << " ===================================" << endl;
    cout << "��         1. ���� ����            ��" << endl;
    cout << "��         2. ���� ����            ��" << endl;
    cout << "��         3. ?????????            ��" << endl;
    cout << " ===================================" << endl;

    cout << "�޴����� �������� : ";
    cin >> choice;

    switch (choice) {
    case 1:
        startGame();  // ���� ����
        break;
    case 2:
        quitGame();   // ���� ����
        break;
    
    case 3:
        cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�" << endl;
        cout << "�� ���� ȣ����� ������? �� ȣ��ɿ� �����ϴ� ������ �ٲ�!" << endl;
        cout << "�� ���踦 â���ߴٴ� ������ ������ �������� �ŵ��� �̸��� �˷��ٲ�!" << endl;
        cout << endl;
        cout << " =======================================" << endl;
        cout << "��             ���� �����             ��" << endl;
        cout << " =======================================" << endl;
        cout << "��             ����.������             ��" << endl;
        cout << "��            ������.���ȯ            ��" << endl;
        cout << "��             ����.������             ��" << endl;
        cout << "��             ����.���ر�             ��" << endl;
        cout << "��             ����.�輺��             ��" << endl;
        cout << "��                                     ��" << endl;
        cout << "��                Team                 ��" << endl;
        cout << "��         ���񷹰���Ÿ 3�����        ��" << endl;
        cout << "��              (����3��)              ��" << endl;
        cout << "��                                     ��" << endl;
        cout << "��         Thank you for Playing!      ��" << endl;
        cout << " =======================================" << endl;
        cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�" << endl;
        mainMenu();
        
        break;
    default:
        cout << "�߸��� �����̾�. �ٽ� �õ��� ��." << endl;
        mainMenu();
        break;
    }
   

}

int main() {
    // ������ ���� �޴��� ǥ��
    mainMenu();

    return 0;
}
