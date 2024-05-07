#pragma once
using namespace std;
#include <iostream>
#include "Base_Unit.h"
#include "ArrayBAG.h"
#include "LinkedStack.h"
#include "LinkedQueue.h"
#include "priQueue.h"
#include "SpecialQueue.h"
#include "AS.h"
#include "AM.h"
#include "Drones.h"

class AlienArmy {
	SpecialQueue dequedrone;
	LinkedQueue<AS*> queueAsoldier;
	Array<AM*> arraymonster;
	int Acount;
	int AS_Created, AD_Created, AM_Created;
public:
	//constructor to assign Counter
	AlienArmy();
	//Add part
	void adddrone(AD* drone);
	void addAsoldier(AS* Asoldier);
	void addmonster(AM* monster);
	void addAlienUnit(Unit* inputUnit);
	//Remove Part
	bool removedrone(AD*& drone1, AD*& drone2);
	void removeAsoldier(AS*& Asoldier);
	//void removemonster(AM*& monster, int index);
	//Printing Part
	void Alienprint();
	//GettersPart

	SpecialQueue& GetADrone();
	LinkedQueue<AS*>& GetASoldier();
	Array<AM*>& GetAMonster();
	int getCounter();
	int get_ASCreated();
	int get_ADCreated();
	int get_AMCreated();
	void pickAM(AM*& monster);
	void removemonster(AM*& monster);
	void attack();
};