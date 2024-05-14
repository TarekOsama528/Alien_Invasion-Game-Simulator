
#include<iostream>
//#include "Drones.h"
//#include "EartArmy.h"
#include "GameManager.h"
//#include "SpecialQueue.h"


AD::AD() {
	settype("Drone");
}
AD::AD(int h, int attackcap, int join, int p, int ID, GameManager* gm) {
	setGM(gm);
	sethealth(h);
	setIH(h);
	setattack(attackcap);
	setid(ID);
	settj(join);
	setpower(p);
	settype("Drone");
	setTa(0);
}

void AD::attack(){
	ET* et = NULL;
	EG* eg = NULL;
	LinkedQueue<ET*> ettemp;
	priQueue<EG*> egtemp;
	LinkedQueue<Unit*> fightlist;
	int k = 0;
	for (size_t i = 0; i < getattack(); i++)
	{
		et = NULL;
		if (i % 2 == 0 || getGM()->GetEarth()->GetETank().getcount() == 0) {
			getGM()->GetEarth()->removetank(et);
			if (et) {
				fightlist.enqueue(et);
				setUAP(et->gethealth()); //Used UAP
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
		eg = NULL;
		if (i % 2 == 1 || getGM()->GetEarth()->GetETank().getcount() == 0) {
			getGM()->GetEarth()->removegunnery(eg, k);
			if (eg) {
				fightlist.enqueue(eg);
				setUAP(eg->gethealth()); //Used UAP
				eg->sethealth(eg->gethealth() - getUAP());
				if (eg->getTa() == 0) eg->setTa(getGM()->getTimestep());
				eg->setDf();

				if (eg->gethealth() <= 0) {
					eg->setTd(getGM()->getTimestep());
					eg->setDd();
					eg->setDb();
					getGM()->kill(eg);
				}
				else {
					egtemp.enqueue(eg, k);
				}
			}
		}
	}

	while (!ettemp.isEmpty()) {
		ettemp.dequeue(et);
		getGM()->GetEarth()->addtank(et);
	}
	while (!egtemp.isEmpty()) {
		egtemp.dequeue(eg,k);
		getGM()->GetEarth()->addgunnery(eg,k);
	}

	if (getGM()->getOpMode() == "Interactive") {
		cout << "AD " << fightlist.getcount() << " shots "; fightlist.print();
		cout << " IDs of all Earth units shot by AD" << getid() << endl;
	}

}