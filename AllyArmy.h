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

public:
	void attack();
	void print();
	LinkedQueue<SU*> getsaver();
	void withdraw();
	void addsaver(SU* su);
	void removesaver(SU*& su);
};



