#include "random.h"
#include <cstdlib> 
#include <ctime> 
#include <vector> 
#include <string>

void InitializeRandom() {
    srand(static_cast<unsigned int>(time(0)));
}

int GenerateRandom(int min, int max) {
    return min + (rand() % (max - min + 1));
}

bool IsCreateEvent(int percent) {
    int tmp = GenerateRandom(0, 99);
    return tmp < percent;
}

string CreateGradeByCDF() {
    const vector<pair<int, string>> grade = {
        {1, "S"}, {10, "A"}, {30, "B"}, {55, "C"}, {100, "D"}
    };

    int RandomValue = GenerateRandom(1, 100);
    for (const auto& range : grade) {
        if (RandomValue <= range.first) {
            return range.second;
        }
    }
    return "D"; // Default case
}