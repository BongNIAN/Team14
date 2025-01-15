#include "print.h"
#include "Monster.h"
#include <iostream> 
#include <thread> 
#include <chrono> 

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

    int filledLengthRed = static_cast<int>(barLength * 0.3);

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

void cursorLocation(int x,int y) 
{
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
