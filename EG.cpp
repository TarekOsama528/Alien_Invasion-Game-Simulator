#include <iostream>
#include "EG.h"
#include "GameManager.h"
using namespace std;


EG::EG() {
	settype("Gunnery");
}
EG::EG(int h, int attackcap, int join, int p, int ID, GameManager* gm) {
	setGM(gm);
	sethealth(h);
	setIH(h);
	setattack(attackcap);
	setid(ID);
	settj(join);
	setpower(p);
	settype("Gunnery");
	setTa(0);
}
void EG::attack() {
	AD* d1 = NULL;
	AD* d2 = NULL;
	AM* am = NULL;
	LinkedQueue<AM*> amtemp;
	LinkedQueue<AD*> adtemp;
	LinkedQueue<Unit*> fightlist;
	for (int i = 0; i < getattack(); i++)
	{
		am = NULL;
		if (i % 2 == 0 || getGM()->GetAlien()->GetADrone().getcount() == 0) {
			getGM()->GetAlien()->pickAM(am); //peek function to pick randomly
			getGM()->GetAlien()->removemonster(am);
			if (am) {
				fightlist.enqueue(am);
				setUAP(am->gethealth()); //Used UAP
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
		d1 = NULL;
		d2 = NULL;
		if (i % 2 == 1 || getGM()->GetAlien()->GetAMonster().getcount() == 0) {
			getGM()->GetAlien()->removedrone(d1, d2);
			if (d1) {
				fightlist.enqueue(d1);
				fightlist.enqueue(d2);
				setUAP(d1->gethealth());//Used UAP
				d1->sethealth(d1->gethealth() - getUAP());
				if (d1->getTa() == 0) d1->setTa(getGM()->getTimestep());
				d1->setDf();

				setUAP(d2->gethealth());//Used UAP
				d2->sethealth(d2->gethealth() - getUAP());
				if (d1->getTa() == 0) d1->setTa(getGM()->getTimestep());
				d1->setDf();

				if (d1->gethealth() <= 0) {
					d1->setTd(getGM()->getTimestep());
					d1->setDd();
					d1->setDb();
					getGM()->kill(d1);
				}
				else {
					adtemp.enqueue(d1);
				}
				if (d2->gethealth() <= 0) {
					d2->setTd(getGM()->getTimestep());
					d2->setDd();
					d2->setDb();
					getGM()->kill(d2);
				}
				else {
					adtemp.enqueue(d2);
				}
			}

			else if (getGM()->GetAlien()->GetADrone().getcount() == 1 && i % 2 == 1) {
				getGM()->GetAlien()->GetADrone().dequeue(d1);
				if (d1) {
					fightlist.enqueue(d1);
					setUAP(d1->gethealth());//used UAP
					d1->sethealth(d1->gethealth() - getUAP());
					if (d1->getTa() == 0) d1->setTa(getGM()->getTimestep());
					d1->setDf();

					if (d1->gethealth() <= 0) {
						d1->setTd(getGM()->getTimestep());
						d1->setDd();
						d1->setDb();
						getGM()->kill(d1);
					}
					else {
						adtemp.enqueue(d1);
					}
				}
			}
		}
	}

	while (!amtemp.isEmpty())
	{
		amtemp.dequeue(am);
		getGM()->GetAlien()->addmonster(am);
	}
	while (!adtemp.isEmpty()) {
		adtemp.dequeue(d1); 
		getGM()->GetAlien()->adddrone(d1);
	}
	if (getGM()->getOpMode() == "Interactive") {
		cout << "EG " << fightlist.getcount() << " shots "; fightlist.print();
		cout << " IDs of all alien units shot by EG" << getid() << endl;
	}
}
