#include <iostream>
#include "AM.h"
#include "GameManager.h"
using namespace std;

AM::AM() {
	settype("Alien Mosnter");
}
AM::AM(int h, int attackcap, int join, int p, int ID, GameManager* gm) {
	setGM(gm);
	sethealth(h);
	setIH(h);
	setattack(attackcap);
	setid(ID);
	settj(join);
	setpower(p);
	settype("Alien Monster");
	setTa(0);
}
void AM::attack() {
	ES* es=NULL;
	ET* et=NULL;
	SU* su = NULL;
	LinkedQueue<SU*> sutemp;
	LinkedQueue<ES*> estemp;
	LinkedQueue<ET*> ettemp;
	LinkedQueue<Unit*> fightlist;
	bool infection_prob;
	for (int i = 0; i < getattack(); i++) {
		es = NULL;
		if ((i % 2 == 0 && i%3!=0) || getGM()->GetEarth()->GetETank().getcount() == 0 || getGM()->Getally()->getsaver().getcount() == 0) {
			getGM()->GetEarth()->removeEsoldier(es);
			if (es) {
				fightlist.enqueue(es);
				setUAP(es->gethealth()); //used UAP
				es->sethealth(es->gethealth() - getUAP());
				infection_prob =(rand() % 100) < 10;
				if (infection_prob && !(es->getinfection()) && !(es->getimmunity()))
				{
					es->setinfection(true);
				}
				if (es->getTa() == 0) es->setTa(getGM()->getTimestep());
				es->setDf();
				if (es->gethealth() <= 0) {
					es->setTd(getGM()->getTimestep());
					es->setDd();
					es->setDb();
					getGM()->kill(es);
				}
				else if (es->gethealth() < 0.20 * es->getIH()) {
					getGM()->aidsoldier(es, 100 - es->gethealth());
					es->setaid(getGM()->getTimestep());
				}
				/*else if (es->getinfection())
				{
					getGM()->GetEarth()->addEsoldier(es);
				}*/
				else {
					estemp.enqueue(es);
				}
			}
		}
		else if (i % 2 == 1 || getGM()->GetEarth()->GetESoldier().getcount() == 0 || getGM()->Getally()->getsaver().getcount() == 0) {
			et = NULL;
			getGM()->GetEarth()->removetank(et);
			if (et) {
				fightlist.enqueue(et);
				setUAP(et->gethealth()); //used UAP
				et->sethealth(et->gethealth() - getUAP());
				if (et->getTa() == 0) et->setTa(getGM()->getTimestep());
				et->setDf();
				if (et->gethealth() <= 0) {
					et->setTd(getGM()->getTimestep());
					et->setDd();
					et->setDb();
					getGM()->kill(et);
				}
				else if (et->gethealth() < 0.20 * et->getIH()) {
					getGM()->aidtank(et);
					et->setaid(getGM()->getTimestep());
				}
				else {
					ettemp.enqueue(et);
				}
			}
		}
		else if (i % 3 == 0 || getGM()->GetEarth()->GetESoldier().getcount() == 0 || getGM()->GetEarth()->GetETank().getcount() == 0) {
			su = NULL;
			getGM()->Getally()->removesaver(su);
			if (su) {
				fightlist.enqueue(su);
				setUAP(su->gethealth()); //used UAP
				su->sethealth(su->gethealth() - getUAP());
				if (su->getTa() == 0) su->setTa(getGM()->getTimestep());
				su->setDf();
				if (su->gethealth() <= 0) {
					su->setTd(getGM()->getTimestep());
					su->setDd();
					su->setDb();
					//getGM()->Getally()->removesaver(su);
				}
				else {
					sutemp.enqueue(su);
				}
			}
		}
	}
	while (!estemp.isEmpty()) {
		estemp.dequeue(es);
		getGM()->GetEarth()->addEsoldier(es);
	}
	while (!ettemp.isEmpty()) {
		ettemp.dequeue(et);
		getGM()->GetEarth()->addtank(et);
	}

	while (!sutemp.isEmpty()) {
		sutemp.dequeue(su);
		getGM()->Getally()->addsaver(su);
	}

	if (getGM()->getOpMode() == "Interactive") {
		cout << "AM " << fightlist.getcount() << " shots "; fightlist.print();
		cout << " IDs of all Earth/Ally units shot by AM " << getid() << endl;
	}
}