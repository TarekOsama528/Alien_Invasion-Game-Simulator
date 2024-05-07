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
}
void ES::attack() {
	AS* as=NULL;
	LinkedQueue<AS*> astemp;
	LinkedQueue<Unit*> fightlist;
	for (size_t i = 0; i < getattack(); i++)
	{
		as = NULL;
		getGM()->GetAlien()->removeAsoldier(as);
		if (as) {
			fightlist.enqueue(as);
			setUAP(as->gethealth());			//Used UAP
			as->sethealth(as->gethealth() - getUAP());
			if (as->getTa()==0) as->setTa(getGM()->getTimestep());
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
	if (getGM()->getOpMode() == "Interactive") {
		cout << "ES " << fightlist.getcount() << " shots "; fightlist.print();
		cout << " IDs of all alien units shot by ES" << getid()<<endl;
	}
	while (!astemp.isEmpty()) {
		astemp.dequeue(as);
		getGM()->GetAlien()->addAsoldier(as);
	}
}
