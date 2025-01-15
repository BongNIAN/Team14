#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <windows.h>

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

#endif // PRINT_H

