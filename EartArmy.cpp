#include <iostream>
#include "EartArmy.h"
#include "GameManager.h"
using namespace std;
EarthArmy::EarthArmy()
{
	Ecounter = 1;
	ES_Created = 0;
	ET_Created = 0;
	EG_Created = 0;
	EH_Created = 0;
	critical = false;
}
void EarthArmy::addtank(ET *tank) {
	stacktank.push(tank);
}
void EarthArmy::addEsoldier(ES *Esoldier) {
	queueEsoldier.enqueue(Esoldier);
}
void EarthArmy::addgunnery(EG* gunnery, int k) {
	priqueuegunnery.enqueue(gunnery, k);
}
void EarthArmy::addHeal(HU* Qheal) {
	stackheal.push(Qheal);
}
void EarthArmy::AddEarthUnit(Unit* inputUnit)
{
	//Tried to do using Dynamic Casting but it has to be at least one virtual function This was on phase 1 
	//TODO Implement Dynamic Casting Becuase it's Better as it provides Checking for the return Pointer
	Ecounter++;
	if (inputUnit->gettype() == "Earth Soldier")
	{
			queueEsoldier.enqueue(static_cast<ES*>(inputUnit));
			ES_Created++;
	}
	else if (inputUnit->gettype() == "Gunnery")
	{
		priqueuegunnery.enqueue(static_cast<EG*> (inputUnit), inputUnit->getpower() * (inputUnit->gethealth() / 100)); //using UAP From Given Document without unit 2
		EG_Created++;
	}
	else if (inputUnit->gettype() == "Tank")
	{
		stacktank.push(static_cast<ET*>(inputUnit));
		ET_Created++;
	}
	else if (inputUnit->gettype() == "Heal")
	{
		stackheal.push(static_cast<HU*>(inputUnit));
		EH_Created++;
	}
}
void EarthArmy::removetank(ET *&tank) {
	stacktank.pop(tank);
}
void EarthArmy::removeEsoldier(ES *&Esoldier) {
	queueEsoldier.dequeue(Esoldier);
}
void EarthArmy::removegunnery(EG*& gunnery, int k) {
	priqueuegunnery.dequeue(gunnery, k);
}
void EarthArmy::removeheal(HU*& Qheal) {
	stackheal.pop(Qheal);
}

void EarthArmy::Earthprint() {
	cout << queueEsoldier.getcount() << " " << "ES ";
	queueEsoldier.print(); cout << endl;
	cout << priqueuegunnery.getcount() << " " << "EG ";
	priqueuegunnery.print(); cout << endl;
	cout << stacktank.getcount() << " " << "ET ";
	stacktank.print(); cout << endl;
	cout << stackheal.getcount() << " " << "HU ";
	stackheal.print(); cout << endl;
}
LinkedStack<ET*>& EarthArmy::GetETank()
{
	return stacktank;
}
LinkedQueue<ES*>& EarthArmy::GetESoldier()
{
	return queueEsoldier;
}
priQueue<EG*>& EarthArmy::GetEGunnery()
{
	return priqueuegunnery;
}
LinkedStack<HU*>& EarthArmy::GetHeal() {
	return stackheal;
}
int EarthArmy::getCounter()
{
	return Ecounter;
}
int EarthArmy::get_ESCreated()
{
	return ES_Created;
}
int EarthArmy::get_ETCreated()
{
	return ET_Created;
}
int EarthArmy::get_EGCreated()
{
	return EG_Created;
}
int EarthArmy::get_EHCreated()
{
	return EH_Created;
}
void EarthArmy::attack() {
	ES* es = NULL;
	ET* et = NULL;
	HU* hu = NULL;
	EG* eg = NULL;
	int k = 0;
	queueEsoldier.dequeue(es);
	stacktank.peek(et);
	stackheal.peek(hu);
	priqueuegunnery.dequeue(eg,k);
	if (es) {
		es->attack();
		queueEsoldier.enqueue(es);
	}
	if (et) {
		if (et->getGM()->GetEarth()->GetESoldier().getcount() < (0.3 * et->getGM()->GetAlien()->GetASoldier().getcount())) {
			et->attackAS();
			critical = true;
		}
		else if (critical == true && et->getGM()->GetEarth()->GetESoldier().getcount() >= (0.8 * et->getGM()->GetAlien()->GetASoldier().getcount())) {
			et->attack();
			critical = false;
		}
		else if (critical == true && et->getGM()->GetEarth()->GetESoldier().getcount() < (0.8 * et->getGM()->GetAlien()->GetASoldier().getcount())) {
			et->attackAS();
		}
		else {
            et->attack();
		}
	}
	if (eg) {
		eg->attack();
		priqueuegunnery.enqueue(eg, k);
	}
	if (hu) {
		hu->attack();
	}
}