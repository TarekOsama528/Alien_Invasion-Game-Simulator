#include "RandomGenerator.h"
#include "GameManager.h"
#include <cstdlib>
#include <ctime>
using namespace std;
RandomGenerator::RandomGenerator()
{
    SetSeed(time(0));
    srand(SeedValue);
}
void RandomGenerator::SetSeed(int number)
{
    SeedValue = number;
}
void RandomGenerator::SetNumber(int number)
{
    unit_Number = number;
}
void RandomGenerator::setES_Percentage(int percentage) {
    ES_Percentage = percentage;
}

void RandomGenerator::setET_Percentage(int percentage) {
    ET_Percentage = percentage;
}

void RandomGenerator::setEG_Percentage(int percentage) {
    EG_Percentage = percentage;
}

void RandomGenerator::setEH_Percentage(int percentage) {
    EH_Percentage = percentage;
}

void RandomGenerator::setAS_Percentage(int percentage) {
    AS_Percentage = percentage;
}

void RandomGenerator::setAM_Percentage(int percentage) {
    AM_Percentage = percentage;
}

void RandomGenerator::setAD_Percentage(int percentage) {
    AD_Percentage = percentage;
}

void RandomGenerator::setProb(int probability) {
    Prob = probability;
}

void RandomGenerator::setEHealth(int minHealth, int maxHealth) {
    Min_Earth_Health = minHealth;
    Max_Earth_Health = maxHealth;
}

void RandomGenerator::setEPower(int minPower, int maxPower) {
    Min_Earth_Power = minPower;
    Max_Earth_Power = maxPower;
}

void RandomGenerator::setECap(int minCapacity, int maxCapacity) {
    Min_Earth_Capacity = minCapacity;
    Max_Earth_Capacity = maxCapacity;
}

void RandomGenerator::setAHealth(int minHealth, int maxHealth) {
    Min_Alien_Health = minHealth;
    Max_Alien_Health = maxHealth;
}

void RandomGenerator::setAPower(int minPower, int maxPower) {
    Min_Alien_Power = minPower;
    Max_Alien_Power = maxPower;
}

void RandomGenerator::setACap(int minCapacity, int maxCapacity) {
    Min_Alien_Capacity = minCapacity;
    Max_Alien_Capacity = maxCapacity;
}
void RandomGenerator::setGameManager(GameManager* g)
{
    gManger = g;
}
void RandomGenerator::setinf_Prob(double inf_Prob)
{
    infection_Prob = inf_Prob;
}
double RandomGenerator::getinf_Prob()
{
    return infection_Prob;
}
int RandomGenerator::getProb()
{
    return Prob;
}
int RandomGenerator::getNumber()
{
    return unit_Number;
}
void RandomGenerator::GenerateStats(int& Power, int& Health, int& Cap,string type)
{
    //using formula of rand()%(max-min+1)+min
    if (type == "Alien")
    {
        Power = (rand() % (Max_Alien_Power - Min_Alien_Power + 1)) + Min_Alien_Power;
        Health = (rand() % (Max_Alien_Health - Min_Alien_Health + 1)) + Min_Alien_Health;
        Cap = (rand() % (Max_Alien_Capacity - Min_Alien_Capacity + 1)) + Min_Alien_Capacity;
    }
    else if (type == "Earth")
    {
        Power = (rand() % (Max_Earth_Power - Min_Earth_Power + 1)) + Min_Earth_Power;
        Health = (rand() % (Max_Earth_Health - Min_Earth_Health + 1)) + Min_Earth_Health;
        Cap = (rand() % (Max_Earth_Capacity - Min_Earth_Capacity + 1)) + Min_Earth_Capacity;
    }
    else
    {
        Power = Health = Cap = 0;
        //cout<<"Invalid DataType";
    }
}
Unit* RandomGenerator::CreateUnit(int B,string type)
{
    int Health, Power, Cap;
    Unit* temp = NULL;
    if (type == "Earth")
    {
        GenerateStats(Power, Health, Cap, "Earth");
        if (B <= ES_Percentage)
        {
            temp = new ES(Health, Cap, gManger->getTimestep(), Power, gManger->GetEarth()->getCounter(),gManger);
        }
        else if (B <= (ES_Percentage + ET_Percentage))
        {
            temp = new ET(Health, Cap, gManger->getTimestep(), Power, gManger->GetEarth()->getCounter(),gManger);
        }
        else if (B <= (ES_Percentage + ET_Percentage+EG_Percentage))
        {
            temp = new EG(Health, Cap, gManger->getTimestep(), Power, gManger->GetEarth()->getCounter(),gManger);
        }
        else if (B <= (ES_Percentage + ET_Percentage + EG_Percentage + EH_Percentage))
        {
            temp = new HU(Health, Cap, gManger->getTimestep(), Power, gManger->GetEarth()->getCounter(), gManger);
        }
    }
    else if (type == "Alien")
    {
        GenerateStats(Power, Health, Cap, "Alien");
        if (B <= AS_Percentage)
        {
            temp = new AS(Health, Cap, gManger->getTimestep(), Power, gManger->GetAlien()->getCounter(),gManger);
        }
        else if (B <= (AS_Percentage + AM_Percentage))
        {
            temp = new AM(Health, Cap, gManger->getTimestep(), Power, gManger->GetAlien()->getCounter(),gManger);
        }
        else if (B<=(AS_Percentage + AM_Percentage+AD_Percentage))
        {
            temp = new AD(Health, Cap, gManger->getTimestep(), Power, gManger->GetAlien()->getCounter(),gManger);
        }
    }
    return temp;
}
void RandomGenerator::RandomUnitGenratorAlgortihm()
{
    int A,B;
    Unit* inputUnit;
    A = (rand() % 100) + 1; //from zero to 100 then adding one to make it from 1
    //cout << "The Number Generated is" << A << endl;
    if (A <= getProb())
    {
        for (int i=0; i < getNumber(); i++) 
        {
            B = (rand() % 100) + 1;
            //cout << "The Number Generated is" << B << endl;
            inputUnit = CreateUnit(B,"Earth");
            //cout << "The Type of created earth is:" << inputUnit->gettype()<<endl;
            gManger->GetEarth()->AddEarthUnit(inputUnit);
        }
        for (int i=0; i < getNumber(); i++)
        {
            B = (rand() % 100) + 1;
            //cout << "The Number Generated is" << B << endl;
            inputUnit = CreateUnit(B, "Alien");
            //cout << "The Type of created alien is:" << inputUnit->gettype() << endl;
            gManger->GetAlien()->addAlienUnit(inputUnit);
        }
    }
}