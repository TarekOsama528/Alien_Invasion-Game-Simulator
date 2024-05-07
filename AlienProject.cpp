#include <iostream>
using namespace std;
#include "EartArmy.h"
#include "AlienArmy.h"
#include "Base_Unit.h"
#include "GameManager.h"

int main()
{
   
    GameManager Game;
    /*Game.GetInput();
    Game.getRandomGen()->RandomUnitGenratorAlgortihm();*/
    //Game.SilentMode();
    //return 0;
    Game.simulate_phase2();

}

