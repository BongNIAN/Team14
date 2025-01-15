#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "Character.h"
#include "ItemManager.h"
#include "item.h"
#include "battlemanager.h"

// ���� ���� �Լ�
void quitGame() {
    cout << "������ �ٽ� ���ƿò��� �Ͼ�!" << endl;
    exit(0); // ���� ����
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
    
    cout << " �׷� ���� �̸��� " << characterName << "..." << endl;
    cout << "������� ���� �����̾���, �� ���� �ֱ� ������. "<< endl;
    cout << "���� �������� �̹� �ƹ��͵� ������ �ʴ� ĥ��ӿ� ���׷��� �����ִ� ��� ���� ���̾���. "<< endl;
    cout << "�ƹ��� ������ �ѷ����Ƶ� ���ư� ���� ������ �ʴ� ���ν�� �� ���� ���� ���ư��� ���ۿ� ����. "<< endl;         
    cout << "�� ��ۿ� ����.���ư�����." << endl;
    cout << "������ ������ �𸣴� �η����, Ż�ⱸ�� ���� �� �ִٴ� ����� ���� ���� ���� ��������." << endl;

    int choice = 0;
 
        // ���¸� ���� �� ��, ������ �� �� �ִ� �޴� �߰�
    while (true) {
        character->displayStatus();
        int choice;
        cout << "====================================" << endl;
        cout << "=        ������ �ұ��?            =" << endl;
        cout << "====================================" << endl;
        cout << "=     1. ���� ������ ����          =" << endl;
        cout << "=     2. ĳ���� ���� ����          =" << endl;
        cout << "=        3. ���� ����              =" << endl;
        cout << "====================================" << endl;

        cout << "�޴����� ���� : ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "���� ������ ���ϴ�..." << endl;
            {
                BattleManager battleManager;
                battleManager.Battle(character);  // ���� ����
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
    }
}

// ���� �޴� ȭ�� �Լ�
void mainMenu() {
    int choice;

    cout << "====================================" << endl;
    cout << "=          �ؽ�Ʈ �ҿ�             =" << endl;
    cout << "====================================" << endl;
    cout << "=         1. ���� ����             =" << endl;
    cout << "=         2. ���� ����             =" << endl;
    cout << "====================================" << endl;

    cout << "�޴����� �������� : ";
    cin >> choice;

    switch (choice) {
    case 1:
        startGame();  // ���� ����
        break;
    case 2:
        quitGame();   // ���� ����
        break;
    default:
        cout << "�߸��� �����̾�. �ٽ� �õ��� ��." << endl;
        mainMenu();
        break;
    }
}





//int main() {
//    // ������ ���� �޴��� ǥ��
//    mainMenu();
//
//    return 0;
//}
