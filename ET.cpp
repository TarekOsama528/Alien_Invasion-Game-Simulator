#include <iostream>
#include "ET.h"
#include "GameManager.h"
using namespace std;


void ET::setaid(int aid) {
	aidtime = aid;
}
int ET::getaid() {
	return aidtime;
}

ET::ET() {
	settype("Tank");
	//setaid(0);
}
ET::ET(int h, int attackcap, int join, int p, int ID, GameManager* gm) {
	setGM(gm);
	sethealth(h);
	setIH(h);
	setattack(attackcap);
	setid(ID);
	settj(join);
	setpower(p);
	settype("Tank");
	setTa(0);
	critical = false;
}
void ET::attack() {
	AM* am=NULL;
	LinkedQueue<Unit*> fightlist;
	//AS* as=NULL;
	//LinkedQueue<AS*> astemp;
	LinkedQueue<AM*> amtemp;
	for (int i = 0; i < getattack(); i++)
	{
		am = NULL;
		getGM()->GetAlien()->pickAM(am); //peek function to pick randomly
		getGM()->GetAlien()->removemonster(am);
		if (am) {
			fightlist.enqueue(am);
			setUAP(am->gethealth()); //Used UAP function
			am->sethealth(am->gethealth() - getUAP());
			if (am->getTa() == 0) am->setTa(getGM()->getTimestep());
			am->setDf();
			if (am->gethealth() <= 0) {
				am->setTd(getGM()->getTimestep());
				am->setDd();
				am->setDb();
				getGM()->kill(am);
			}
			else {
				amtemp.enqueue(am);
			}
		}
	}

	while (!amtemp.isEmpty()) {
		amtemp.dequeue(am);
		getGM()->GetAlien()->addmonster(am);
	}

	//if (getGM()->GetEarth()->GetESoldier().getcount() < (0.3 * getGM()->GetAlien()->GetASoldier().getcount())) {
	//	while (getGM()->GetEarth()->GetESoldier().getcount() < (0.8 * getGM()->GetAlien()->GetASoldier().getcount())) {
	//		as = NULL;
	//		getGM()->GetAlien()->removeAsoldier(as);
	//		if (as) {
	//			fightlist.enqueue(as);
	//			setUAP(as->gethealth()); //used UAP
	//			as->sethealth(gethealth() - getUAP());
	//			if (as->getTa() == 0) as->setTa(getGM()->getTimestep());
	//			as->setDf();
	//			if (as->gethealth() <= 0) {
	//				as->setTd(getGM()->getTimestep());
	//				as->setDd();
	//				as->setDb();
	//				getGM()->kill(as);
	//			}
	//			else {
	//				getGM()->GetAlien()->addAsoldier(as);
	//			}
	//		}
	//	}
	//}

	if (getGM()->getOpMode() == "Interactive") {
		cout << "ET " << fightlist.getcount() << " shots "; fightlist.print();
		cout << " IDs of all alien units shot by ET" << getid() << endl;
	}
}
void ET::attackAS() {
	//AM* am = NULL;
	LinkedQueue<Unit*> fightlist;
	AS* as = NULL;
	LinkedQueue<AS*> astemp;
	//LinkedQueue<AM*> amtemp;
	for (int i = 0; i < getattack(); i++)
	{
		as = NULL;
		getGM()->GetAlien()->removeAsoldier(as);
		if (as) {
			fightlist.enqueue(as);
			setUAP(as->gethealth()); //Used UAP function
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

	while (!astemp.isEmpty()) {
		astemp.dequeue(as);
		getGM()->GetAlien()->addAsoldier(as);
	}

	if (getGM()->getOpMode() == "Interactive") {
		cout << "ET " << fightlist.getcount() << " shots "; fightlist.print();
		cout << " IDs of all alien units shot by ET" << getid() << endl;
	}
}