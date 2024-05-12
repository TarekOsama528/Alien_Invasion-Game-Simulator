#pragma once
using namespace std;
#include <iostream>
#include "Base_Unit.h"
#include "ArrayBAG.h"
#include "LinkedStack.h"
#include "LinkedQueue.h"
#include "priQueue.h"
#include "SpecialQueue.h"
#include "ET.h"
#include "ES.h"
#include "EG.h"
#include "HU.h"

class EarthArmy {
	LinkedStack<ET*> stacktank;
	LinkedQueue<ES*> queueEsoldier;
	priQueue<EG*> priqueuegunnery;
	LinkedStack<HU*> stackheal;
	int Ecounter;
	bool critical;
	int ES_Created, ET_Created, EG_Created,EH_Created;
	double infection_Per;
public:
	//Constructor to set the Counter
	EarthArmy();
	//Adding Part 
	void addtank(ET* tank);
	void addEsoldier(ES *Esoldier);
	void addgunnery(EG *gunnery, int k);
	void AddEarthUnit(Unit* inputUnit);
	void addHeal(HU* Qheal);
	//Removing Part
	void removetank(ET*& tank);
	void removeEsoldier(ES*& Esoldier);
	void removegunnery(EG*& gunnery, int k);
	void removeheal(HU*& Qheal);
	//Printing Part
	void Earthprint();
	//Getters 
	LinkedStack<ET*>& GetETank();
	LinkedQueue<ES*>& GetESoldier();
	priQueue<EG*>& GetEGunnery();
	LinkedStack<HU*>& GetHeal();
	int getCounter();

	int get_ESCreated();
	int get_ETCreated();
	int get_EGCreated();
	int get_EHCreated();
	void attack();
	void spreadinfection();
	void Calc_inf_Perc();
	double getinfection_Per();
};




