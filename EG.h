#pragma once
#include<iostream>
#include "Base_unit.h"
#include "priQueue.h"
using namespace std;

class EG : public Unit {

public:
	EG();
	EG(int h, int attackcap, int join, int p, int ID,GameManager* gm);
	void attack();
};