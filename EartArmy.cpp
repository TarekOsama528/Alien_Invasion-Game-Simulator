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
	//num_inf = 0;
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
//int EarthArmy::getnumberofinfected()
//{
//	ES* es = NULL;
//	LinkedQueue<ES*> estempq;
//	while (queueEsoldier.dequeue(es))
//	{
//		if (es->getinfection())
//		{
//			num_inf++;
//		}
//		estempq.enqueue(es);
//	}
//	while (estempq.dequeue(es))
//	{
//		queueEsoldier.enqueue(es);
//	}
//	return num_inf;
//}
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

void EarthArmy::spreadinfection()
{
	ES* es = NULL;
	LinkedQueue<ES*> inf_es_temp;
	LinkedQueue<ES*> es_temp;
	LinkedQueue<ES*> new_infected;
	int healthy_index_array[1000];
	int infectedcount = 0;
	int healthy_array_count=0;
	int not_inf_index=0;
	while (queueEsoldier.dequeue(es))
	{
		if (es->getinfection())
		{
			inf_es_temp.enqueue(es);
			infectedcount++;
		}
		else if(!es->getinfection() && !es->getimmunity())
		{
			healthy_index_array[healthy_array_count] = not_inf_index;
			healthy_array_count++;
		}
		not_inf_index++;
		es_temp.enqueue(es);
	}
	while (es_temp.dequeue(es))
	{
		queueEsoldier.enqueue(es);
	}
	int random_soldeir_index;
	int counter;
	for (int i = 0; i < infectedcount; i++)
	{

		if ((rand() % 100) < 2 && healthy_array_count !=0)
		{
			random_soldeir_index = rand() % healthy_array_count;
			counter = 0;
			while (queueEsoldier.dequeue(es))
			{
				if (counter == healthy_index_array[random_soldeir_index])
				{
					es->setinfection(true);
					//es->setid(es->getid() + 1000);
					new_infected.enqueue(es);
				}
				counter++;
				es_temp.enqueue(es);
			}
			healthy_index_array[random_soldeir_index] = healthy_index_array[healthy_array_count-1];
			healthy_array_count--;
			while (es_temp.dequeue(es))
			{
				queueEsoldier.enqueue(es);
			}
		}
	}
	
}

void EarthArmy::Calc_inf_Perc()
{
	int Total_es_count = 0;
	int Total_inf_es=0;
	ES* es = NULL;
	LinkedQueue<ES*> tempesq;
	while (queueEsoldier.dequeue(es))
	{
		if (es->getinfection())
		{
			Total_inf_es++;
		}
		Total_es_count++;

		tempesq.enqueue(es);
	}
	while (tempesq.dequeue(es))
	{
		queueEsoldier.enqueue(es);
	}
	infection_Per = (static_cast<double>(Total_inf_es) / Total_es_count) * 100;
}

double EarthArmy::getinfection_Per()
{
	return infection_Per;
}
