#pragma once
#include "Base_Unit.h"
#include "string"
class GameManager;
class RandomGenerator
{
private:
	int SeedValue;
	int unit_Number;
	int ES_Percentage, ET_Percentage, EG_Percentage,EH_Percentage, AS_Percentage, AM_Percentage, AD_Percentage, Prob;
	int Min_Earth_Health, Min_Earth_Power, Min_Earth_Capacity;
	int Max_Earth_Health, Max_Earth_Power, Max_Earth_Capacity;
	int Min_Alien_Health, Min_Alien_Power, Min_Alien_Capacity;
	int Max_Alien_Health, Max_Alien_Power, Max_Alien_Capacity;
	GameManager* gManger;
public:
	RandomGenerator();
	Unit* CreateUnit(int B,string type); 
	void RandomUnitGenratorAlgortihm();
    void GenerateStats(int& Power, int& Health, int& Capacity,string type);
	void SetSeed(int number);
    // Setters
    void SetNumber(int number);
    void setES_Percentage(int percentage);
    void setET_Percentage(int percentage);
    void setEG_Percentage(int percentage);
    void setEH_Percentage(int percentage);
    void setAS_Percentage(int percentage);
    void setAM_Percentage(int percentage);
    void setAD_Percentage(int percentage);
    void setProb(int probability);

    void setEHealth(int minHealth, int maxHealth);
    void setEPower(int minPower, int maxPower);
    void setECap(int minCapacity, int maxCapacity);

    void setAHealth(int minHealth, int maxHealth);
    void setAPower(int minPower, int maxPower);
    void setACap(int minCapacity, int maxCapacity);
    void setGameManager(GameManager* gm);

    // Getters
    /*int getES_Percentage() const;
    int getET_Percentage() const;
    int getEG_Percentage() const;
    int getEH_Percentage() const;
    int getAS_Percentage() const;
    int getAM_Percentage() const;
    int getAD_Percentage() const;*/
    int getProb();
    int getNumber();





};

