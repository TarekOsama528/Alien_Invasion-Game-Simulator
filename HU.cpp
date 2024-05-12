#include <iostream>
#include "HU.h"
#include "GameManager.h"
using namespace std;

HU::HU() {
	settype("Heal");
}
HU::HU(int h, int attackcap, int join, int p, int ID,GameManager* gm) {
	setGM(gm);
	sethealth(h);
	setIH(h);
	setattack(attackcap);
	setid(ID);
	settj(join);
	setpower(p);
	settype("Heal");
	setTa(0);
}
void HU::attack() {
	ET* et = NULL;
	ES* es = NULL;
	int k=0;
	int c = 0;
	bool healed = false;
	LinkedQueue<Unit*> fightlist;
	priQueue<ES*> soldierlist;
	LinkedQueue<ET*> tanklist;
	int imp = ((float)(getpower() * (gethealth() / 100))) / (float)sqrt(gethealth());
	for (int i = 0; i < getattack(); i++)
	{
		es= NULL;
		getGM()->removesoldier(es, k);
		if (es && (es->getaid() - getGM()->getTimestep())<=10) {
			c++;
			healed = true;
			fightlist.enqueue(es);
			if (!es->getinfection())
			{
				es->sethealth(gethealth() + imp);
			}
			else if (es->getinfection())
			{
				es->sethealth(gethealth() + imp / 2);
			}
			if (es->gethealth() >= 20) {
				if (es->getinfection())
				{
					es->setinfection(false);
					es->setimmunity(true);
				}
				getGM()->GetEarth()->addEsoldier(es);
			}
			else {
				soldierlist.enqueue(es,k);
			}
		}
		else if (es && es->getaid() - getGM()->getTimestep() > 10) {
			es->setTd(getGM()->getTimestep());
			es->setDd();
			es->setDb();
			getGM()->kill(es); //setting db
		}
	}

	while (!soldierlist.isEmpty()) {
		soldierlist.dequeue(es,k);
		getGM()->aidsoldier(es, k);
	}

	for  (int i= 0;i<getattack()-c;i++) {
		et = NULL;
		getGM()->removetank(et);
		if (et && et->getaid() - getGM()->getTimestep() <= 10) {
			fightlist.enqueue(et);
			healed = true;
			et->sethealth(et->gethealth() + imp);
			if (et->gethealth() >= 20) {
				getGM()->GetEarth()->addtank(et);
			}
			else {
				tanklist.enqueue(et);
			}
		}
		else if (et && et->getaid() - getGM()->getTimestep() > 10) {
			et->setTd(getGM()->getTimestep());
			et->setDd();
			et->setDb();
			getGM()->kill(et);
		}
	}

	while (!tanklist.isEmpty()) {
		tanklist.dequeue(et);
		getGM()->aidtank(et);
	}

	if (getGM()->getOpMode() == "Interactive") {
		cout << "HU " << fightlist.getcount() << " healings "; fightlist.print();
		cout << " IDs of all Earth units healed by HU" << getid() << endl;
	}

	if (healed) {
		sethealth(0); //heal unit should be killed after healing immediately
		HU* hu;
		getGM()->GetEarth()->GetHeal().pop(hu);

		setTa(getGM()->getTimestep());
		setTd(getGM()->getTimestep());
		setDf();
		setDd();
		setDb();
		getGM()->kill(this);
	}
}