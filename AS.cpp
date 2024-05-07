//#include <iostream>
#include "AS.h"
#include "GameManager.h"
using namespace std;

AS::AS() {
	settype("Alien Soldier");
}
AS::AS(int h, int attackcap, int join, int p, int ID,GameManager* gm) {
	setGM(gm);
	sethealth(h);
	setIH(h);
	setattack(attackcap);
	setid(ID);
	settj(join);
	setpower(p);
	settype("Alien Soldier");
	setTa(0);
}
void AS::attack() {
	ES* es=NULL;
	LinkedQueue<Unit*> fightlist;
	LinkedQueue<ES*> estemp;
	for (int i = 0; i < getattack(); i++) {
		es = NULL;
		getGM()->GetEarth()->removeEsoldier(es);
		if (es) {
			fightlist.enqueue(es);
			setUAP(es->gethealth());//used UAP
			es->sethealth(es->gethealth() - getUAP());
			if (es->getTa() == 0) es->setTa(getGM()->getTimestep());
			es->setDf();
			if (es->gethealth() <= 0) {
				es->setTd(getGM()->getTimestep());
				es->setDd();
				es->setDb();
				getGM()->kill(es);
			}
			else if (es->gethealth() < 40) { //this should be changed to 0.2*initial health
				getGM()->aidsoldier(es,100-es->gethealth());
				es->setaid(getGM()->getTimestep());
			}
			else {
				estemp.enqueue(es);
			}
		}
	}
	while (!estemp.isEmpty()) {
		estemp.dequeue(es);
		getGM()->GetEarth()->addEsoldier(es);
	}

	if (getGM()->getOpMode() == "Interactive") {
		cout << "AS " << fightlist.getcount() << " shots "; fightlist.print();
		cout << " IDs of all Earth units shot by AS " << getid() << endl;
	}
}