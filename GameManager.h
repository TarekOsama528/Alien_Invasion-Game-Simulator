
#pragma once
#include "AlienArmy.h"
#include "Base_Unit.h"
#include "EartArmy.h"
#include "LinkedQueue.h"
//#include "SpecialQueue.h"
#include "RandomGenerator.h"
#include <fstream>
#include<string>
#include <windows.h> // For Sleep function


//#include <sstream>
class GameManager
{
private:
	AlienArmy Aliens;
	EarthArmy Earth;
	RandomGenerator RandGen;
	LinkedQueue <Unit*> KilledList;
	priQueue<ES*> UMLsoldier;
	LinkedQueue<ET*> UMLtank;
	int Timestep;
	string BattleResult;
	string OpMode;

public:
	bool setOpMode(string mode);
	bool setResult(string result);
	string SelectMode();
	string getOpMode();
	string getBattleResult();
	void aidsoldier(ES* unit,int pri);
	void aidtank(ET* tank);
	void removesoldier(ES*& es,int& k);
	priQueue<ES*> getUMLsoldier();
	LinkedQueue<ET*> getUMLtank();
	GameManager(); //Constructor to initilaize Time step and 
	bool GetInput();
	void SimulatePhase1();
	RandomGenerator* getRandomGen();
	AlienArmy* GetAlien();
	EarthArmy* GetEarth();
	void Print();
	void setTimestep(int t);
	int getTimestep();
	void kill(Unit* unit);
	bool ProduceOutputFile();
	void SilentMode();
	void simulate_phase2();

	void print1();
	void print2();
	//Function To sort Destructed Unit
	//priQueue<Unit*> SortKilledList();

};