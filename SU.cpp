#include "SU.h"
#include "GameManager.h"

SU::SU()
{
	settype("Saver Unit");
}

SU::SU(int h, int attackcap, int join, int p, int ID, GameManager* gm)
{
	setGM(gm);
	sethealth(h);
	setIH(h);
	setattack(attackcap);
	setid(ID);
	settj(join);
	setpower(p);
	settype("Saver Unit");
	setTa(0);
	setinfection(false);
}

void SU::attack()
{
	AS* as = NULL;
	LinkedQueue<AS*> astemp;
	LinkedQueue<Unit*> fightlist;
	for (size_t i = 0; i < getattack(); i++)
	{
		as = NULL;
		getGM()->GetAlien()->removeAsoldier(as);
		if (as)
		{
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
			else
			{
				astemp.enqueue(as);
			}
		}
	}

	while (!astemp.isEmpty()) {
		astemp.dequeue(as);
		getGM()->GetAlien()->addAsoldier(as);
	}

	if (getGM()->getOpMode() == "Interactive") {
		cout << "SU " << fightlist.getcount() << " shots "; fightlist.print();
		cout << " IDs of all alien units shot by SU" << getid() << endl;
	}
}
