
#include "AllyArmy.h"

void AllyArmy::attack() {
	SU* su = NULL;
	queueSaver.dequeue(su);
	if (su) {
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

void AllyArmy::addsaver(SU* su) {
	queueSaver.enqueue(su);
}
void AllyArmy::removesaver(SU*& su) {
	queueSaver.dequeue(su);
}