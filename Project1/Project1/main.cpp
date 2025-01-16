#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "ItemManager.h"
#include "item.h"
#include "battlemanager.h"
#include "EventManager.h"


void printDragon()
{
    cout << R"(
(  )   /\   _                 (     
    \ |  (  \ ( \.(               )                      _____
  \  \ \  `  `   ) \             (  ___                 / _   \
 (_`    \+   . x  ( .\            \/   \____-----------/ (o)   \_
- .-               \+  ;          (  O                           \____
                          )        \_____________  `              \  /
(__                +- .( -'.- <. - _  VVVVVVV VV V\                 \/
(_____            ._._: <_ - <- _  (--  _AAAAAAA__A_/                  |
  .    /./.+-  . .- /  +--  - .     \______________//_              \_______
  (__ ' /x  / x _/ (                                  \___'          \     /
 , x / ( '  . / .  /                                      |           \   /
    /  /  _/ /    +                                      /              \/
   '  (__/                                             /                  \
        )" << endl;

}
// 게임 종료 함수
void quitGame() {
    cout << "언젠간 다시 돌아올꺼라 믿어!" << endl;
    exit(0); // 게임 종료
}

void visitshop() {

}


bool IsNextStage(int result)
{
    if (result == 1) return true;
    else return false;

}


// 게임 시작 함수
void startGame() {
    // 캐릭터 이름 입력 받기
    string characterName;
    BattleManager battleManager;
    int tmp = 110;
    cout << "크윽...머리가...나의 이름이 뭐였지? : ";
    cin.ignore(); // cin에서 남아있는 개행 문자 처리
    getline(cin, characterName); // 이름을 한 줄로 입력받기

    // Singleton을 사용하여 Character 객체 생성
    Character* character = Character::getInstance(characterName);
    cout << "===============================================================================" << endl;
    cout << " 그래 나의 이름은 " << characterName << "..." << endl;
    cout << "어느때와 같은 저녁이었다, 그 일이 있기 전까지. " << endl;
    cout << "눈을 떴을때는 이미 아무것도 보이지 않는 칠흑속에 덩그러니 놓여있는 계단 위의 문이었다. " << endl;
    cout << "아무리 주위를 둘러보아도 나아갈 길이 보이지 않는 나로써는 저 문을 향해 나아가는 수밖에 없다. " << endl;
    cout << "이 길밖에 없다.나아가보자." << endl;
    cout << "무엇이 있을지 모르는 두려움과, 탈출구가 있을 수 있다는 희망이 섞여 나의 발을 움직였다." << endl;
    cout << "===============================================================================" << endl;
    int choice = 0;

    character->displayStatus();



    while (true) {

        int choice;
        cout << " ==================================" << endl;
        cout << "ㅣ         무엇을 할까요?         ㅣ" << endl;
        cout << " ==================================" << endl;
        cout << "ㅣ      1. 다음 방으로 간다       ㅣ" << endl;
        cout << "ㅣ      2. 캐릭터 상태 보기       ㅣ" << endl;
        cout << "ㅣ         3. 게임 종료           ㅣ" << endl;
        cout << " ==================================" << endl;

        cout << "메뉴에서 선택 : ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "다음 방으로 들어갑니다..." << endl;
            {
                int tmp = battleManager.MonsterBattle(character);  // 전투 시작
                if (tmp == 1)
                {
                    character->increasebattleCount();
                }
                else if (tmp == 2)
                {
                    cout << "gameOver" << endl;
                    exit(0);
                }
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

        while (character->getBattleCount() > 0 && character->getBattleCount() < 18) {

            int choice;
            cout << " ===================================" << endl;
            cout << "ㅣ         무엇을 할까요?          ㅣ" << endl;
            cout << " ===================================" << endl;
            cout << "ㅣ      1. 다음 방으로 간다        ㅣ" << endl;
            cout << "ㅣ          2. 상점방문            ㅣ" << endl;
            cout << "ㅣ      3. 캐릭터 상태 보기        ㅣ" << endl;
            cout << "ㅣ          4. 인벤토리            ㅣ" << endl;
            cout << "ㅣ          5. 게임종료            ㅣ" << endl;
            cout << " ===================================" << endl;

            cout << "메뉴에서 선택 : ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "다음 방으로 들어갑니다..." << endl;
                {
                    int tmp = battleManager.MonsterBattle(character);  // 전투 시작
                    if (tmp == 1)
                    {
                        character->increasebattleCount();
                    }
                    else if (tmp == 2)
                    {
                        cout << "gameOver" << endl;
                        exit(0);
                    }
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
        while (character->getBattleCount() == 18) {

            int choice;
            cout << " ===================================" << endl;
            cout << "ㅣ         무엇을 할까요?          ㅣ" << endl;
            cout << " ===================================" << endl;
            cout << "ㅣ      1. 다음 방으로 간다        ㅣ" << endl;
            cout << "ㅣ          2. 상점방문            ㅣ" << endl;
            cout << "ㅣ      3. 캐릭터 상태 보기        ㅣ" << endl;
            cout << "ㅣ          4. 인벤토리            ㅣ" << endl;
            cout << "ㅣ          5. 게임종료            ㅣ" << endl;
            cout << " ===================================" << endl;

            cout << "메뉴에서 선택 : ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "다음 방으로 들어갑니다..." << endl;
                printDragon();

                {
                   
                    int tmp = battleManager.BossBattle(character);  // 전투 시작
                    if (tmp == 1)
                    {
                        character->increasebattleCount();
                    }
                    else if (tmp == 2)
                    {
                        cout << "gameOver" << endl;
                        exit(0);
                    }
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
            cout << "Game End 플레이해주셔서 감사합니다 " << endl;

        }
    }

}

// 메인 메뉴 화면 함수
void mainMenu() {
    int choice;

    cout << " ===================================" << endl;
    cout << "ㅣ          텍스트 소울            ㅣ" << endl;
    cout << " ===================================" << endl;
    cout << "ㅣ         1. 게임 시작            ㅣ" << endl;
    cout << "ㅣ         2. 게임 종료            ㅣ" << endl;
    cout << "ㅣ         3. ?????????            ㅣ" << endl;
    cout << " ===================================" << endl;

    cout << "메뉴에서 선택해줘 : ";
    cin >> choice;

    switch (choice) {
    case 1:
        startGame();  // 게임 시작
        break;
    case 2:
        quitGame();   // 게임 종료
        break;

    case 3:
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
        cout << "너 정말 호기심이 많구나? 그 호기심에 보답하는 선물을 줄께!" << endl;
        cout << "이 세계를 창조했다는 전설로 전해져 내려오는 신들의 이름을 알려줄께!" << endl;
        cout << endl;
        cout << " =======================================" << endl;
        cout << "ㅣ             만든 사람들             ㅣ" << endl;
        cout << " =======================================" << endl;
        cout << "ㅣ             팀장.봉원명             ㅣ" << endl;
        cout << "ㅣ            부팀장.김승환            ㅣ" << endl;
        cout << "ㅣ             팀원.곽연진             ㅣ" << endl;
        cout << "ㅣ             팀원.김준기             ㅣ" << endl;
        cout << "ㅣ             팀원.김성훈             ㅣ" << endl;
        cout << "ㅣ                                     ㅣ" << endl;
        cout << "ㅣ                Team                 ㅣ" << endl;
        cout << "ㅣ         봉골레곽스타 3각김밥        ㅣ" << endl;
        cout << "ㅣ              (봉곽3김)              ㅣ" << endl;
        cout << "ㅣ                                     ㅣ" << endl;
        cout << "ㅣ         Thank you for Playing!      ㅣ" << endl;
        cout << " =======================================" << endl;
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
        mainMenu();

        break;
    default:
        cout << "잘못된 선택이야. 다시 시도해 봐." << endl;
        mainMenu();
        break;
    }
}

int main() {
    // 게임의 메인 메뉴를 표시
   /* mainMenu();*/

    mainMenu();
   /* Character* c = Character::getInstance("name");
    c->displayStatus();
   */


    return 0;
}
