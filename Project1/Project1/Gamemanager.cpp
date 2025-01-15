#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "Character.h"
#include "ItemManager.h"
#include "item.h"
#include "battlemanager.h"
#include "EventManager.h"
#include "stageManager.h"

// 게임 종료 함수
void quitGame() {
    cout << "언젠간 다시 돌아올꺼라 믿어!" << endl;
    exit(0); // 게임 종료
}

void visitshop() {

}

// 게임 시작 함수
void startGame() {
    // 캐릭터 이름 입력 받기
    string characterName;
    cout << "크윽...머리가...나의 이름이 뭐였지? : ";
    cin.ignore(); // cin에서 남아있는 개행 문자 처리
    getline(cin, characterName); // 이름을 한 줄로 입력받기
    
    // Singleton을 사용하여 Character 객체 생성
    Character* character = Character::getInstance(characterName);
    cout << "===============================================================================" << endl;
    cout << " 그래 나의 이름은 " << characterName << "..." << endl;
    cout << "어느때와 같은 저녁이었다, 그 일이 있기 전까지. "<< endl;
    cout << "눈을 떴을때는 이미 아무것도 보이지 않는 칠흑속에 덩그러니 놓여있는 계단 위의 문이었다. "<< endl;
    cout << "아무리 주위를 둘러보아도 나아갈 길이 보이지 않는 나로써는 저 문을 향해 나아가는 수밖에 없다. "<< endl;         
    cout << "이 길밖에 없다.나아가보자." << endl;
    cout << "무엇이 있을지 모르는 두려움과, 탈출구가 있을 수 있다는 희망이 섞여 나의 발을 움직였다." << endl;
    cout << "===============================================================================" << endl;
    int choice = 0;
    
    character->displayStatus();

  
    
    while (true) {
       
        int choice;
        cout << "====================================" << endl;
        cout << "=        무엇을 할까요?            =" << endl;
        cout << "====================================" << endl;
        cout << "=     1. 다음 방으로 간다          =" << endl;
        cout << "=     2. 캐릭터 상태 보기          =" << endl;
        cout << "=        3. 게임 종료              =" << endl;
        cout << "====================================" << endl;

        cout << "메뉴에서 선택 : ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "다음 방으로 들어갑니다..." << endl;
            {
                BattleManager battleManager;
                battleManager.Battle(character);  // 전투 시작
                // 0스테이지 클리어 후 상점 스토리 출력
                EventManager::triggerStageEvent(character->getBattleCount());

            }
            break;
        case 2:
            character->displayStatus();  // 캐릭터 상태 보기
            break;
        case 3:
            quitGame();   // 게임 종료
            break;
        default:
            cout << "잘못된 선택이야. 다시 시도해 봐." << endl;
            startGame();  // 다시 선택을 할 수 있도록
            break;
        }
        
        while (character->getBattleCount() > 0) {

            int choice;
            cout << "====================================" << endl;
            cout << "=        무엇을 할까요?            =" << endl;
            cout << "====================================" << endl;
            cout << "=     1. 다음 방으로 간다          =" << endl;
            cout << "=        2. 상점방문               =" << endl;
            cout << "=     3. 캐릭터 상태 보기          =" << endl;
            cout << "=        4. 인벤토리               =" << endl;
            cout << "=        5. 게임종료               =" << endl;
            cout << "====================================" << endl;

            cout << "메뉴에서 선택 : ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "다음 방으로 들어갑니다..." << endl;
                {
                    BattleManager battleManager;
                    battleManager.Battle(character);  // 전투 시작
                    // 10스테이지 클리어 후 상점 스토리 출력
                    EventManager::triggerStageEvent(character->getBattleCount());

                }
                break;

            case 2:
                character->visitShop();
                break;

            case 3:
                character->displayStatus();  // 캐릭터 상태 보기
                break;

            case 4:
                character->displayInventory();
                break;

            case 5:
                quitGame();   // 게임 종료
                break;

            default:
                cout << "잘못된 선택이야. 다시 시도해 봐." << endl;
                startGame();  // 다시 선택을 할 수 있도록
                break;
            }


        }
        
    }

}

// 메인 메뉴 화면 함수
void mainMenu() {
    int choice;

    cout << "====================================" << endl;
    cout << "=          텍스트 소울             =" << endl;
    cout << "====================================" << endl;
    cout << "=         1. 게임 시작             =" << endl;
    cout << "=         2. 게임 종료             =" << endl;
    cout << "====================================" << endl;

    cout << "메뉴에서 선택해줘 : ";
    cin >> choice;

    switch (choice) {
    case 1:
        startGame();  // 게임 시작
        break;
    case 2:
        quitGame();   // 게임 종료
        break;
    default:
        cout << "잘못된 선택이야. 다시 시도해 봐." << endl;
        mainMenu();
        break;
    }
   

}

int main() {
    // 게임의 메인 메뉴를 표시
    mainMenu();

    return 0;
}
