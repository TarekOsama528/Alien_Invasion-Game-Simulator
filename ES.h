#pragma once
#include"Base_Unit.h"
#include"LinkedQueue.h"
class ES :public Unit
{
	int aidtime;
public:
	ES();
	ES(int h, int attackcap, int join, int p, int ID, GameManager* gm);
	void attack();
	void setaid(int aid);
	int getaid();
};