#pragma once

using namespace std;
//#include <iostream>
#include "Base_Unit.h"
#include "SU.h"
#include "LinkedStack.h"
#include "LinkedQueue.h"
#include "ES.h"
#include "EartArmy.h"

class AllyArmy {
	LinkedQueue<SU*> queueSaver;
	int Infection_Percentage;
	int AllyCounter;

public:
	AllyArmy();
	void attack();
	void print();
	LinkedQueue<SU*> getsaver();
	void withdraw();
	void addsaver(Unit* su);
	void removesaver(SU*& su);
	void setInfectionPercentage(int per);
	int getCounter();

};



