
#pragma once
#include"Base_Unit.h"
#include"LinkedQueue.h"
class HU :public Unit {
public:
	HU();
	HU(int h, int attackcap, int join, int p, int ID,GameManager* gm);
	void attack();
};
