#include <iostream>
#include "AlienArmy.h"
using namespace std;


AlienArmy::AlienArmy()
{
	Acount = 2000;
	AS_Created = 0;
	AM_Created = 0;
	AD_Created = 0;
}

void AlienArmy::adddrone(AD* drone) {
	dequedrone.enqueue(drone);
}
void AlienArmy::addAsoldier(AS *Asoldier) {
	queueAsoldier.enqueue(Asoldier);
}
void AlienArmy::addmonster(AM* monster) {
	arraymonster.Add(monster);
}
void AlienArmy::addAlienUnit(Unit* inputUnit)
{
	//Tried to do using Dynamic Casting but it has to be at least one virtual function
	Acount++;
	if (inputUnit->gettype() == "Drone")
	{
		dequedrone.enqueue(static_cast<AD*> (inputUnit));
		AD_Created++;
	}
	else if (inputUnit->gettype() == "Alien Monster")
	{
		//cout << "trying to create monster"; This Line OF Code Used  For Debugging We Just Show it for steps
		arraymonster.Add(static_cast<AM*>(inputUnit));
		AM_Created++;
	}
	else if (inputUnit->gettype() == "Alien Soldier")
	{
		queueAsoldier.enqueue(static_cast<AS*>(inputUnit));
		AS_Created++;
	}
}



bool AlienArmy::removedrone(AD*& drone1, AD*& drone2)
{
	if (dequedrone.getcount() < 2) 
		return false;
	dequedrone.dequeue(drone1);
	dequedrone.dequeueRear(drone2);
	return true;
}
void AlienArmy::removeAsoldier(AS*& Asoldier) {
	queueAsoldier.dequeue(Asoldier);
}
//void AlienArmy::removemonster(AM*& monster, int index) {
//	arraymonster.Remove(index, monster);
//}

void AlienArmy::Alienprint() {
	cout << queueAsoldier.getcount() << " " << "AS ";
	queueAsoldier.print(); cout << endl;
	cout << arraymonster.getcount() << " " << "AM ";
	arraymonster.print(); cout << endl;
	cout << dequedrone.getcount() << " " << "AD ";
	dequedrone.print(); cout << endl;
}

SpecialQueue& AlienArmy::GetADrone()
{
	return dequedrone;
}
LinkedQueue<AS*> &AlienArmy::GetASoldier()
{
	return queueAsoldier;
}
Array<AM*> &AlienArmy::GetAMonster()
{
	return arraymonster;
}
int AlienArmy::getCounter()
{
	return Acount;
}
int AlienArmy::get_ASCreated()
{
	return AS_Created;
}
int AlienArmy::get_AMCreated()
{
	return AM_Created;
}
int AlienArmy::get_ADCreated()
{
	return AD_Created;
}


void AlienArmy::removemonster(AM*& monster) {
	arraymonster.remove(monster);
}

void AlienArmy::pickAM(AM*& monster) {
	arraymonster.peek(monster);
}
void AlienArmy::attack() {
	AS* as = NULL;
	AM* am = NULL;
	AD* d1 = NULL;
	AD* d2 = NULL;
	queueAsoldier.dequeue(as);
	arraymonster.peek(am);
    removedrone(d1,d2);
	if (as) {
		as->attack();
		queueAsoldier.enqueue(as);
	}
	if (am) {
		am->attack();
	}
	if (d1) {
		d1->attack();
		d2->attack();
		adddrone(d1);
		adddrone(d2);
	}
}