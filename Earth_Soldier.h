#pragma once
#include"Base_Unit.h"
#include"LinkedQueue.h"
class ES :public Unit, LinkedQueue<ES>
{
public:
	ES()
	{
		Type = "Earth Soldier";
	}

};