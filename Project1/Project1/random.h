
#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

/** ��Ȯ���� ���� ���� �ʱ�ȭ */
void InitializeRandom();

/** min <= RandomX <= max */
int GenerateRandom(int min, int max);

/** Ư�� Ȯ��(percent)�� �̺�Ʈ �߻� ���� Ȯ�� */
bool IsCreateEvent(int percent);

/** ���� ���� �Լ�(CDF)�� ����Ͽ� ��� ���� */
string CreateGradeByCDF();

#endif // random.h
