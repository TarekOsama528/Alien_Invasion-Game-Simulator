#pragma once
#include"Base_Unit.h"
#include"LinkedQueue.h"
class AS :public Unit
{
public:
	AS();
	AS(int h, int attackcap, int join, int p, int ID, GameManager* gm);
	void attack();
};