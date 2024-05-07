#include <iostream>
#include "Base_Unit.h"
using namespace std;



void Unit::setid(int id) {
	Id = id;
}
int Unit::getid() {
	return Id;
}
void Unit::sethealth(int h) {
	Health = h;
}
int Unit::gethealth() {
	return Health;
}
void Unit::settj(int tj) {
	Tj = tj;
}
int Unit::gettj() {
	return Tj;
}
void Unit::setpower(int p) {
	Power = p;
}
int Unit::getpower() {
	return Power;
}
void Unit::setattack(int a) {
	Attack_Cap = a;
}
int Unit::getattack() {
	return Attack_Cap;
}
void Unit::settype(string t) {
	Type = t;
}
string Unit::gettype() {
	return Type;
}
void Unit::setTa(int ta) {
	Ta = ta;
}
void Unit::setTd(int td) {
	Td = td;
}
void Unit::setDf() {
	Df = Ta - Tj;
}
void Unit::setDd() {
	Dd = Td - Ta;
}
void Unit::setDb() {
	Db = Td - Tj;
}
void Unit::setUAP(int Health2) {
	UAP = ((float)(Power * (Health / 100))) / sqrt(Health2); //unit2 needs gamemanager
}

void Unit::setGM(GameManager* gm) {
	GM = gm;
}

int Unit::getTa() {
	return Ta;
}
int Unit::getTd() {
	return Td;
}
int Unit::getDf() {
	return Df;
}
int Unit::getDd() {
	return Dd;
}
int Unit::getDb() {
	return Db;
}
int Unit::getUAP() {
	return UAP;
}
GameManager* Unit::getGM() {
	return GM;
}
void Unit::setIH(int ih) {
	IH = ih;
}
int Unit::getIH() {
	return IH;
}
