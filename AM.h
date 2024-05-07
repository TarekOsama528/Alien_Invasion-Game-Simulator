#pragma once
using namespace std;
#include "Base_Unit.h"
#include "ArrayBAG.h"

class AM :public Unit {
public:
	AM();
	AM(int h, int attackcap, int join, int p, int ID, GameManager* gm);
	void attack();
};
