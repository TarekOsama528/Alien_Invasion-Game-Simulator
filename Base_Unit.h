#pragma once
#include<iostream>
//#include"ES.h"
using namespace std;
class GameManager;

class Unit
{
protected:
	GameManager* GM;
	int Id;
	int Health;
	int IH;
	string Type;
	int Tj;
	int Power;
	int Attack_Cap;
	int Ta;
	int Td;
	int Df;
	int Dd;
	int Db;
	int UAP;
	bool infection;
public:
	Unit();
	void setIH(int ih);
	int getIH();
	void setid(int id);
	int getid();
	void sethealth(int h);
	int gethealth();
	void settj(int tj);
	int gettj();
	void setpower(int p);
	int getpower();
	void setattack(int a);
	int getattack();
	void settype(string t);
	string gettype();
	void setTa(int ta);
	void setTd(int td);
	void setDf();
	void setDd();
	void setDb();

	void setUAP(int Health);
	void setGM(GameManager* gm);

	void setaid(int aid);
	int getaid();

	int getTa();
	int getTd();
	int getDf();
	int getDd();
	int getDb();
	int getUAP();
	GameManager* getGM();
	virtual void attack(){}

	void setinfection(bool infection);

	bool getinfection();


};

 static ostream& operator<<(ostream& display, Unit uni) {
	 

	 display << uni.getid();
	return display;
}
 static ostream& operator<<(ostream& display, Unit* uni) {

	if (uni->getinfection())
	{
		display << "\033[1;32m"<< "inf_" << uni->getid() << "\033[0m";
	}
	else {
		display << uni->getid();
		
	}
	return display;
	}

 //test
 //test2