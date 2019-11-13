#pragma once
#include "cocos2d.h"
enum MonNum
{
	None = 0,
	Ork
};
class Monster : public cocos2d::Scene
{
public:
	int Hp;
	float Spead;
	int Money;
	MonNum *MonsterNum;
	void MakeMon(int N, MonNum *MonsterNum);
};
