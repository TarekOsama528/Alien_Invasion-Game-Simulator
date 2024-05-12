#include <iostream>
#include "ES.h"
#include "AS.h"
#include "GameManager.h"
using namespace std;


void ES::setaid(int aid) {
	aidtime = aid;
}
int ES::getaid() {
	return aidtime;
}

ES::ES() {
		settype("Earth Soldier");
}
ES::ES(int h, int attackcap, int join, int p, int ID, GameManager* gm) {
	setGM(gm);
	sethealth(h);
	setIH(h);
	setattack(attackcap);
	setid(ID);
	settj(join);
	setpower(p);
	settype("Earth Soldier");
	setTa(0);
	setinfection(false);
	setimmunity(false);
}
//void ES::setinfected(bool ifection)
//{
//	infected = ifection;
//}
//bool ES::getinfected()
//{
//	return infected;
//}
void ES::setimmunity(bool immunity)
{
	immune = immunity;
}
bool ES::getimmunity()
{
	return immune;
}
void ES::attack() {
	AS* as=NULL;
	ES* es = NULL;
	LinkedQueue<AS*> astemp;
	LinkedQueue<ES*> estemp;
	LinkedQueue<Unit*> fightlist;
	LinkedQueue<Unit*> infectedfightlist;
	for (size_t i = 0; i < getattack(); i++)
	{
		as = NULL;
		if (!getinfection())
		{
			getGM()->GetAlien()->removeAsoldier(as);
			if (as) {
				fightlist.enqueue(as);
				setUAP(as->gethealth());			//Used UAP
				as->sethealth(as->gethealth() - getUAP());
				if (as->getTa() == 0) as->setTa(getGM()->getTimestep());
				as->setDf();
				if (as->gethealth() <= 0) {
					as->setTd(getGM()->getTimestep());
					as->setDd();
					as->setDb();
					getGM()->kill(as);

				}
				else {
					astemp.enqueue(as);
				}
			}
		}
		es = NULL;
		if (getinfection())
		{
			getGM()->GetEarth()->removeEsoldier(es);
			if (es && !es->getinfection()) {
				infectedfightlist.enqueue(es);
				setUAP(es->gethealth());			//Used UAP
				es->sethealth(es->gethealth() - getUAP());
				if (es->getTa() == 0) es->setTa(getGM()->getTimestep());
				es->setDf();
				if (es->gethealth() <= 0) {
					es->setTd(getGM()->getTimestep());
					es->setDd();
					es->setDb();
					getGM()->kill(es);

				}
				else {
					estemp.enqueue(es);
				}
			}
		}
	}
	if (getGM()->getOpMode() == "Interactive" && !getinfection()) {
		cout << "ES " << fightlist.getcount() << " shots "; fightlist.print();
		cout << " IDs of all alien units shot by ES" << getid() << endl;
	}
	else if (getGM()->getOpMode() == "Interactive" && getinfection())
	{
		cout << "Infected ES " << infectedfightlist.getcount() << " shots "; infectedfightlist.print();
		cout << " IDs of all earth units shot by infected ES " << "\033[1;32m"<<"inf_" << getid() << "\033[0m" << endl;
	}
	while (!astemp.isEmpty()) {
		astemp.dequeue(as);
		getGM()->GetAlien()->addAsoldier(as);
	}
	while (!estemp.isEmpty()) {
		estemp.dequeue(es);
		getGM()->GetEarth()->addEsoldier(es);
	}
}
