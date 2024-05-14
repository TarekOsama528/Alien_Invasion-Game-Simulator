
#include "AllyArmy.h"
AllyArmy::AllyArmy()
{
	AllyCounter = 3000;
	Infection_Percentage = -1;
}

void AllyArmy::attack() {
	SU* su = NULL;
	queueSaver.dequeue(su);
	if (su && Infection_Percentage!=0 ) {
		su->attack();
		queueSaver.enqueue(su);
	}
}

void AllyArmy::print() {
	cout << queueSaver.getcount() << " " << "SU ";
	queueSaver.print(); cout << endl;
}

void AllyArmy::withdraw() {
	SU* su;
	while (!queueSaver.isEmpty()) {
		queueSaver.dequeue(su);
		
	}
}

LinkedQueue<SU*> AllyArmy::getsaver() {
	return queueSaver;
}

void AllyArmy::addsaver(Unit* su) {
	AllyCounter++;
	queueSaver.enqueue(static_cast<SU*>(su));
}
void AllyArmy::removesaver(SU*& su) {
	queueSaver.dequeue(su);
}

void AllyArmy::setInfectionPercentage(int per)
{
	Infection_Percentage = per;
}

int AllyArmy::getCounter()
{
	
		return AllyCounter;
	
}
