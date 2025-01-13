
#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

/** 정확성을 위해 랜덤 초기화 */
void InitializeRandom();

/** min <= RandomX <= max */
int GenerateRandom(int min, int max);

/** 특정 확률(percent)로 이벤트 발생 여부 확인 */
bool IsCreateEvent(int percent);

/** 누적 분포 함수(CDF)를 사용하여 등급 생성 */
string CreateGradeByCDF();

#endif // random.h
