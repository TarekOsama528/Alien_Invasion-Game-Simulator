#pragma once
using namespace std;

#include"Base_Unit.h"
#include "LinkedStack.h"
class ET : public Unit {
private:
	int aidtime;
	bool critical;
public:
	ET();
	ET(int h, int attackcap, int join, int p, int ID,GameManager* gm);
	void attack();
	void attackAS();
	void setaid(int aid);
	int getaid();
};

