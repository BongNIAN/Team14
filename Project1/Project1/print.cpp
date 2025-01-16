#include "print.h"
#include "Monster.h"
#include <iostream> 
#include <thread> 
#include <chrono> 
#define NOMINMAX

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


// Include the Monster class definition

void PrintLine(const std::string& line, int delay) {
    for (char c : line) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    std::cout << std::endl;
}

void printBossMonster() {
    std::cout << R"(
      ______
   .-'      `-.
  /            \
 |,  .-.  .-.  ,|
 | )(_o/  \o_)( |
 |/     /\     \|
 (_     ^^     _)
  \__|IIIIII|__/
   | \IIIIII/ |
   \          /
    `--------`
    // \\  // \\
   //   \\//   \\
  ||     \/     ||

     GAME OVER
)" << std::endl;
}

void printMonster() {
    std::cout << R"(    ,      ,        *       *
      /(.-""-.)\     *    *        *
  |\  \/      \/  /|     *
  | \ / =.  .= \ / |  
  \( \   o\/o   / )/
   \_, '-/  \-' ,_/      *       *
     /   \__/   \          *
     \ \__/\__/ /            *
   ___\ \|--|/ /___
 /`    \      /    `\     
/       '----'       \     
)" << std::endl;
}

void printBattleWithMonster() {
    std::cout << R"(
                     _____                     ,      ,
                  .-'     '-.                /(.-""-.)\
                 /           \           |\  \/      \/  /|
                |   .-------. |          | \ / =.  .= \ / |
                |  /         \\          \( \   o\/o   / )/
                |  |    O    ||           \_, '-/  \-' ,_/
                \  \         /              /   \__/   \
                 '. '-------'               \ \__/\__/ /
                   '.___._.'               ___\ \|--|/ /___
                 //       \\             /`    \      /    `\
                //         \\           /       '----'       \
               ||    HERO   ||          ||      GOBLIN      ||
               ||           ||          ||                  ||
               ||           ||          ||                  ||
)" << std::endl;
}

void PrintDeathMonster() {
    std::cout << R"(
        _______
       /       \
      /         \
     |   x   x   |
     |     ^     |
      \___|_|___/       
        /     \
       /       \
)" << std::endl;
}

void printMonsterTestModule(std::shared_ptr<Monster> m) {
    std::cout << "hp : " << m->GetHealth() << std::endl;
    std::cout << "attack : " << m->GetAttack() << std::endl;
    std::cout << "name : " << m->GetName() << std::endl;
}
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

void drawHpBar(int currentHp, int maxHp, int barLength) {
    int filledLength = (currentHp * barLength) / maxHp;
    int emptyLength = barLength - filledLength;

    std::string green = "\033[42m \033[0m";
    std::string white = "\033[47m \033[0m";
    std::string red = "\033[41m \033[0m";

    std::string hpBar;

    int filledLengthRed = static_cast<int>(barLength * 0.4);

    if (filledLength < filledLengthRed) {
        for (int i = 0; i < filledLength; ++i) {
            hpBar += red;
        }
    }
    else {
        for (int i = 0; i < filledLength; ++i) {
            hpBar += green;
        }
    }

    for (int i = 0; i < emptyLength; ++i) {
        hpBar += white;
    }

    std::cout << "HP: [" << hpBar << "] " << currentHp << "/" << maxHp << std::endl;
}
void drawExpBar(int currentHp, int maxHp, int barLength) {
    int filledLength = (currentHp * barLength) / maxHp;
    int emptyLength = barLength - filledLength;
    
    std::string yellow = "\033[43m \033[0m";
    std::string white = "\033[47m \033[0m";
    std::string ExpBar;
    for (int i = 0; i < filledLength; ++i) {
        ExpBar += yellow;
    }

    // 빈 부분 (흰색)
    for (int i = 0; i < emptyLength; ++i) {
        ExpBar += white;
    }

    std::cout << "EXP:[" << ExpBar << "] " << currentHp << "/" << maxHp << std::endl;
}


void cursorLocation(int x,int y) 
{
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

COORD getCurrentCursorPosition() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.dwCursorPosition;
    }
    else {
        // 기본 값 반환 (0, 0)
        return { 0, 0 };
    }
}

void getConsoleInfo() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        std::cout << "현재 커서 위치: (" << csbi.dwCursorPosition.X << ", " << csbi.dwCursorPosition.Y << ")\n";
        std::cout << "콘솔 창 크기: (" << csbi.srWindow.Right - csbi.srWindow.Left + 1 << ", "
            << csbi.srWindow.Bottom - csbi.srWindow.Top + 1 << ")\n";
    }
    else {
        std::cerr << "콘솔 정보를 가져올 수 없습니다.\n";
    }
}