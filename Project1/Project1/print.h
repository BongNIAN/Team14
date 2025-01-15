#ifndef PRINT_H
#define PRINT_H

#include <string>
#include <memory>


class Monster; // Forward declaration for Monster class

// Print functions
void PrintLine(const std::string& line, int delay = 50);
void printBossMonster();
void printMonster();
void printBattleWithMonster();
void PrintDeathMonster();
void printMonsterTestModule(std::shared_ptr<Monster> m);
void drawHpBar(int currentHp, int maxHp, int barLength = 20);
void cursorLocation(int x, int y);
void clearScreen();

// Prints a single frame of the door animation.
// Parameters:
//   - frame: The current frame number to render.
void printPlayerPerspectiveDoor(int frame);

// Runs the door opening animation.
void playerPerspectiveDoorAnimation();
#endif // PRINT_H

