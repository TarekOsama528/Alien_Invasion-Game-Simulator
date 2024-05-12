#pragma once
#include"Base_Unit.h"
#include"LinkedQueue.h"
class SU : public Unit
{
public:
	SU();
	SU(int h, int attackcap, int join, int p, int ID, GameManager* gm);
	void attack();
};

