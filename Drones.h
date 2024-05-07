#pragma once
#include<iostream>
#include "Base_unit.h"
#include "SpecialQueue.h"
#include "ET.h"
#include "EG.h"

using namespace std;

class AD :public Unit
{
public:
	AD();
	AD(int h, int attackcap, int join, int p, int ID, GameManager* gm);
	void attack();	
};