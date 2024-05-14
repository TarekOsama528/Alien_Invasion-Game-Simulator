#include "GameManager.h"
#include "LinkedQueue.h"
//#include "SpecialQueue.h"
//#include <string>


void GameManager::killally() {
	SU* su = NULL;
	while (!ally.getsaver().isEmpty()) {
		su = NULL;
		ally.removesaver(su);
		if (su) {
			su->setTd(getTimestep());
			su->setDd();
			su->setDb();
			kill(su);
		}
	}
}
void GameManager::removesave(SU*& su) {
	ally.removesaver(su);
}

AllyArmy* GameManager::Getally() {
	return &ally;
}

void GameManager::kill(Unit* unit) {
	KilledList.enqueue(unit);
}
priQueue<ES*> GameManager::getUMLsoldier() {
	return UMLsoldier;
}
void GameManager::removesoldier(ES*& es,int& k) {
	UMLsoldier.dequeue(es, k);
}
void GameManager::removetank(ET*& et) {
	UMLtank.dequeue(et);
}
void GameManager::aidsoldier(ES* unit,int pri) {
	UMLsoldier.enqueue(unit, pri);
}
LinkedQueue<ET*> GameManager::getUMLtank() {
	return UMLtank;
}
void GameManager::aidtank(ET* tank) {
	UMLtank.enqueue(tank);
}


bool GameManager::setOpMode(string mode)
{
	// Check for Availble Modes
	if (mode == "Interactive" || mode == "Silent") 
	{
		OpMode = mode;
		return true; // Mode set successfully to be used later for detection of mode
	}
	else
	{
		return false; // Invalid mode 
	}
}

bool GameManager::setResult(string result) 
{
	// Check if the result is valid
	if (result == "Win" || result == "Loss" || result == "Draw") {
		BattleResult = result;
		return true; // Result set successfully
	}
	else {
		return false; // Invalid result
	}
}

string GameManager::getOpMode() 
{
	return OpMode ;


}

string GameManager::getBattleResult() 
{
	return BattleResult;
}




GameManager::GameManager()
{
	setTimestep(1);
	//Random Generator 
	RandGen.setGameManager(this);
	setResult("Draw");
}
void GameManager::setTimestep(int t)
{
	Timestep = t;
}
int GameManager::getTimestep()
{
	return Timestep;
}
AlienArmy* GameManager::GetAlien()
{
	return &Aliens;
}
EarthArmy* GameManager::GetEarth()
{
	return &Earth;
}
RandomGenerator* GameManager::getRandomGen()
{
	return &RandGen;
}
bool GameManager::GetInput()
{
	int FileNumber = SelectSencario();
	Color(7);
	int unit_Number;
	double ES_Percentage, ET_Percentage, EG_Percentage, EH_Percentage, AS_Percentage, AM_Percentage, AD_Percentage, Prob;
	double Ranges[12];
	string input_text;
	fstream MyfileHandler;
	switch (FileNumber) {
	case 1:
		MyfileHandler.open("Input_files/Input_1.txt", ios::in); //weak earth strong alien
		break;
	case 2:
		MyfileHandler.open("Input_files/Input_2.txt", ios::in); //weak alien strong earth
		break;
	case 3:
		MyfileHandler.open("Input_files/Three.txt", ios::in); //mid equal
		break;
	case 4:
		MyfileHandler.open("Input_files/Input_4.txt", ios::in); //mid earth strong alien
		break;
	case 5:
		MyfileHandler.open("Input_files/Input_5.txt", ios::in); //mid alien strong earth
		break;
	case 6:
		MyfileHandler.open("Input_files/Input_6.txt", ios::in); //infection zero and mid earth strong alien
		break;
	default:
		MyfileHandler.open("Input.txt.txt", ios::in);
		break;
	}
	//MyfileHandler.open("Input.txt.txt", ios::in);
	if (MyfileHandler.is_open())
	{
		//cout << "I Am in if Condittion\n"; 
		MyfileHandler >> unit_Number;
		MyfileHandler >> ES_Percentage >> ET_Percentage >> EG_Percentage >> EH_Percentage;
		MyfileHandler >> AS_Percentage >> AM_Percentage >> AD_Percentage;
		MyfileHandler >> Prob >>inf_Prob >> inf_thres;
		if (EH_Percentage > 5 || (ES_Percentage + ET_Percentage + EG_Percentage + EH_Percentage) != 100 || (AS_Percentage + AM_Percentage + AD_Percentage) != 100)
		{
			cout << "Error In Percentages" << endl;
			return false;
		}
		else
		{


			//----------------------------------Test Code For Reading From the File----------------------
			/*cout << "The Number of units is:" << unit_Number << endl;
			cout << "The Percentage of ES is:" << ES_Percentage << endl;
			cout << "The Percentage of ET is:" << ET_Percentage << endl;
			cout << "The Percentage of EG is:" << EG_Percentage << endl;
			cout << "The Percentage of EH is:" << EH_Percentage << endl;
			cout << "The Percentage of AS is:" << AS_Percentage << endl;
			cout << "The Percentage of AM is:" << AM_Percentage << endl;
			cout << "The Percentage of AD is:" << AD_Percentage << endl;
			cout << "The Probability Used By Random Generator is:" << Prob << endl;*/

			//---------------------------------------------------------------------------------
			RandGen.SetNumber(unit_Number);
			//Earth Data
			//RandGen.SetNumber(unit_Number);
			RandGen.setES_Percentage(ES_Percentage);
			RandGen.setET_Percentage(ET_Percentage);
			RandGen.setEG_Percentage(EG_Percentage);
			RandGen.setEH_Percentage(EH_Percentage);
			//Alien Data
			RandGen.setAS_Percentage(AS_Percentage);
			RandGen.setAM_Percentage(AM_Percentage);
			RandGen.setAD_Percentage(AD_Percentage);
			RandGen.setProb(Prob);
			RandGen.setInfection_Thres(inf_thres);
			int counter = 0;
			for (int i = 0; i < 6; i++)
			{
				//Here SS Stream Libirary Gave error so we found another method
				/*MyfileHandler >> input_text;
				istringstream iss(input_text);
				int num1, num2;
				char c;
				iss >> num1 >> c >> num2;
				Ranges[counter] = num1;
				counter++;
				Ranges[counter] = num2;
				counter++;*/
				MyfileHandler >> input_text;
				size_t pos = input_text.find('-');

				// Extract the substrings before and after the hyphen
				string numStr1 = input_text.substr(0, pos);
				string numStr2 = input_text.substr(pos + 1);

				// Convert the substrings to integers
				Ranges[counter] = stoi(numStr1);
				counter++;
				Ranges[counter] = stoi(numStr2);
				counter++;

			}

			// Test Code To check Loading from the File the Parts That is needed to be separated
			/*for (int i = 0; i < 12; i++)
			{
				cout << Ranges[i] << endl;
			}*/
			//--------------------------------------------------------------
			RandGen.setEPower(Ranges[0], Ranges[1]);
			RandGen.setEHealth(Ranges[2], Ranges[3]);
			RandGen.setECap(Ranges[4], Ranges[5]);
			RandGen.setAPower(Ranges[6], Ranges[7]);
			RandGen.setAHealth(Ranges[8], Ranges[9]);
			RandGen.setACap(Ranges[10], Ranges[11]);



			MyfileHandler.close();
			return true;
		}
	}
	else
	{
		cout << "The File Cannot be Opened\n";
		return false;
	}

}
void GameManager::Print()
{
	cout << "Current TimeStep " <<getTimestep()<<endl;
	cout << "==============Earth Army Alive Units ==============\n";
	Earth.Earthprint();
	cout << "==============Alien Army Alive Units ==============\n";
	Aliens.Alienprint();
	cout << endl;
	cout << "==============Units In UML==============\n";
	cout << "ES ";
	UMLsoldier.print();
	cout << "ET ";
	UMLtank.print();
	cout << "==============Killed/Destructed Units ==============\n";
	cout<<KilledList.getcount()<<" ";
	KilledList.print();
	cout << endl;
}
void GameManager::print1() {
	cout << "Current TimeStep " << getTimestep() << endl;
	cout << "==============Earth Army Alive Units ==============\n";
	Earth.Earthprint();
	cout << endl;
	cout << "==============Alien Army Alive Units ==============\n";
	Aliens.Alienprint();
	cout << endl;
	cout << "==============Ally Army Alive Units ==============\n";
	ally.print();
	cout << endl;
	cout << "============== Units Fighting at current timestep ==============\n";
}
void GameManager::print2() {
	cout << endl;
	cout << "==============Units In UML==============\n";
	cout << "ES ";
	UMLsoldier.print(); cout << endl;
	cout << "ET ";
	UMLtank.print(); cout << endl;
	cout << "==============Killed/Destructed Units ==============\n";
	cout << KilledList.getcount() << " ";
	KilledList.print();
	cout << endl;
	Earth.Calc_inf_Perc();

	cout << "Percentage of Infection: "<< round(Earth.getinfection_Per())<<"%";
	cout << endl;

}
double GameManager::getinf_Prob()
{
	return inf_Prob;
}
void GameManager::SimulatePhase1()
{
	bool flag = false;
	GetInput();
	while (getTimestep() <= 50)
	{
		RandGen.RandomUnitGenratorAlgortihm();
		int X = 1 + (rand() % 100);
		//cout << "the X value is:" << X << endl; This Line Was For Testing And Tracing Which test case is used
		if (X < 10)
		{
			ES* temp=NULL;
			Earth.removeEsoldier(temp);
			/*cout << "ID:" << temp->getid() << endl;
			cout << "tj:" << temp->gettj() << endl;
			cout << "Health:" << temp->gethealth() << endl;
			cout << "Power:" << temp->getpower() << endl;
			cout << "Less Than 10:" << flag << endl;*/
			if (temp)
			{
				Earth.AddEarthUnit(temp); //Can be done using Earth.ESlist.enque
			}
		}
		else if (X < 20 && X >= 10)
		{
			ET* temp;
			Earth.removetank(temp);
			if (temp == NULL)
			{

			}
			else
			{
				/*cout << "Tank ID:" << temp->getid() << endl; // To Trace Error Becuase There Was error in Linked Stack So here We were Tracing were is the error
				cout << "Less Than 20:" << flag << endl;*/
				KilledList.enqueue(temp);

			}
			
			
		}
		else if (X < 30 && X >= 20)
		{
			EG* temp;
			int pri;
			flag = Earth.GetEGunnery().dequeue(temp, pri);
			if (flag)
			{
				int Health = temp->gethealth();
				temp->sethealth(Health / 2);
				Earth.AddEarthUnit(temp);
			}
		}
		else if (X < 40 && X >= 30)
		{
			AS* temp;
			LinkedQueue<AS*> templist;
			for (int i = 0; i < 5; i++)
			{
				flag = Aliens.GetASoldier().dequeue(temp);
				if (flag)
				{
					int Health = temp->gethealth();
					temp->sethealth(Health - (Health / 4));
					templist.enqueue(temp);
				}
			}
			while (templist.dequeue(temp))
			{
				Aliens.addAlienUnit(temp);
			}
		}
		else if (X < 50) 
		{
			AM* m;
			LinkedQueue<AM*> templist;
			for (int j = 0; j < 5; j++)
			{
				Aliens.pickAM(m);
				if (m != NULL) {
					Aliens.GetAMonster().remove(m);
					templist.enqueue(m);
				}
			}
			Aliens.GetAMonster().print();
			bool check = false;
			for (size_t i = 0; i < 5; i++)
			{
				check = templist.dequeue(m);
				if (check) {
					Aliens.addmonster(m);
				}
			}
			//Aliens.GetAMonster().print();

			
		}
		else if (X < 60) {
			AD* d1 = NULL; AD* d2 = NULL;
			bool check = false;
			for (int i = 0; i < 6; i++)
			{
				check = Aliens.removedrone(d1, d2);
				if (check) {
					KilledList.enqueue(d1);
					KilledList.enqueue(d2);
				}
			}
		}
		Print();
		cout << "Press Enter to continue..." << endl;
		cin.get();
		setTimestep(getTimestep() + 1);
	}
	ProduceOutputFile();
}

bool GameManager::ProduceOutputFile()
{
	fstream MyfileHandler;
	Unit* temp = NULL;
	string unit_type;
	double Destrcuted[8] = {0,0,0,0,0,0,0,0}; //Destruction unit of ES,ET,EG,EH,AS,AM,AD
	double sumOfDs[9] = {0,0,0,0,0,0,0,0,0};//Has format of[DF Earth,Dd Earth,Db Earth,Df Alien,Dd Alien,Db Alien,Df Saver,Dd Saver,Db Sacer]
	int CountOfEarth = 0, CountOfAlien = 0, CountOfSaver = 0;
	MyfileHandler.open("OutputFile.txt", ios::out);
	if (MyfileHandler.is_open())
	{
		MyfileHandler << "Td\t" << "ID\t" << "Tj\t" << "Df\t" << "Dd\t" << "Db\n";
		while (KilledList.dequeue(temp))
		{
			//First Task of Output File
			MyfileHandler << temp->getTd() << "\t" << temp->getid() << "\t" << temp->gettj() << "\t" << temp->getDf() << "\t" << temp->getDd() << "\t" << temp->getDb() << endl;
			unit_type = temp->gettype();
			if (unit_type == "Earth Soldier")
			{
				//cout << "I am Soldier hey \n";
				Destrcuted[0]=Destrcuted[0]+1;
				//cout << Destrcuted[0];
				sumOfDs[0] = sumOfDs[0] + temp->getDf();
				sumOfDs[1] = sumOfDs[1] + temp->getDd();
				sumOfDs[2] = sumOfDs[2] + temp->getDb();
				CountOfEarth++;


			}
			else if (unit_type == "Tank")
			{
				//cout << "I am Tank hey \n";
				Destrcuted[1]= Destrcuted[1]+1;
				//cout << Destrcuted[1];
				sumOfDs[0] = sumOfDs[0] + temp->getDf();
				sumOfDs[1] = sumOfDs[1] + temp->getDd();
				sumOfDs[2] = sumOfDs[2] + temp->getDb();
				CountOfEarth++;

			}
			else if (unit_type == "Gunnery")
			{
				//cout << "I am Gunn hey \n";

				Destrcuted[2]= Destrcuted[2]+1;
				sumOfDs[0] = sumOfDs[0] + temp->getDf();
				sumOfDs[1] = sumOfDs[1] + temp->getDd();
				sumOfDs[2] = sumOfDs[2] + temp->getDb();
				CountOfEarth++;
				//cout << Destrcuted[2];

			}
			else if (unit_type == "Heal")
			{
				//cout << "I am Heal hey \n";
				Destrcuted[3]= Destrcuted[3]+1;
				sumOfDs[0] = sumOfDs[0] + temp->getDf();
				sumOfDs[1] = sumOfDs[1] + temp->getDd();
				sumOfDs[2] = sumOfDs[2] + temp->getDb();
				CountOfEarth++;
			}
			else if (unit_type == "Alien Soldier")
			{
				//cout << "I am Heal hey \n";
				Destrcuted[4] = Destrcuted[4] + 1;
				sumOfDs[3] = sumOfDs[3] + temp->getDf();
				sumOfDs[4] = sumOfDs[4] + temp->getDd();
				sumOfDs[5] = sumOfDs[5] + temp->getDb();
				CountOfAlien++;
			}
			else if (unit_type == "Alien Monster")
			{
				//cout << "I am Heal hey \n";
				Destrcuted[5] = Destrcuted[5] + 1;
				sumOfDs[3] = sumOfDs[3] + temp->getDf();
				sumOfDs[4] = sumOfDs[4] + temp->getDd();
				sumOfDs[5] = sumOfDs[5] + temp->getDb();
				CountOfAlien++;
			}
			else if (unit_type == "Drone")
			{
				//cout << "I am Heal hey \n";
				Destrcuted[6] = Destrcuted[6] + 1;
				sumOfDs[3] = sumOfDs[3] + temp->getDf();
				sumOfDs[4] = sumOfDs[4] + temp->getDd();
				sumOfDs[5] = sumOfDs[5] + temp->getDb();
				CountOfAlien++;
			}
			else if (unit_type == "Saver Unit")
			{
				//cout << "I am Heal hey \n";
				Destrcuted[7] = Destrcuted[7] + 1;
				sumOfDs[6] = sumOfDs[6] + temp->getDf();
				sumOfDs[7] = sumOfDs[7] + temp->getDd();
				sumOfDs[8] = sumOfDs[8] + temp->getDb();
				CountOfSaver++;
			}

			else
			{
			}
			//ES* tempSoldier = NULL;
			//int pri = 0;
			//while (UMLsoldier.dequeue(tempSoldier,pri))
			//{
			//	//First Task of Output File
			//	MyfileHandler << tempSoldier->getTd() << "\t" << tempSoldier->getid() << "\t" << tempSoldier->gettj() << "\t" << tempSoldier->getDf() << "\t" << tempSoldier->getDd() << "\t" << tempSoldier->getDb() << endl;
			//	unit_type = tempSoldier->gettype();
			//	if (unit_type == "Earth Soldier")
			//	{
			//		//cout << "I am Soldier hey \n";
			//		Destrcuted[0] = Destrcuted[0] + 1;
			//		//cout << Destrcuted[0];
			//		sumOfDs[0] = sumOfDs[0] + temp->getDf();
			//		sumOfDs[1] = sumOfDs[1] + temp->getDd();
			//		sumOfDs[2] = sumOfDs[2] + temp->getDb();
			//		CountOfEarth++;
			//	}
			//}
			//ET* tempTank = NULL;
			//while (UMLtank.dequeue(tempTank))
			//{
			//	//First Task of Output File
			//	MyfileHandler << tempTank->getTd() << "\t" << tempTank->getid() << "\t" << tempTank->gettj() << "\t" << tempTank->getDf() << "\t" << tempTank->getDd() << "\t" << tempTank->getDb() << endl;
			//	unit_type = tempTank->gettype();
			//	if (unit_type == "Tank")
			//	{
			//		//cout << "I am Tank hey \n";
			//		Destrcuted[1] = Destrcuted[1] + 1;
			//		//cout << Destrcuted[1];
			//		sumOfDs[0] = sumOfDs[0] + temp->getDf();
			//		sumOfDs[1] = sumOfDs[1] + temp->getDd();
			//		sumOfDs[2] = sumOfDs[2] + temp->getDb();
			//		CountOfEarth++;
			//	}
			//}
		}



		MyfileHandler << "Battle Result\t" << getBattleResult() << endl<<endl;
		//--------------------------------------------For Earth Army Data-------------------------------------------------
		MyfileHandler << "For Earth Army: " << endl;
		MyfileHandler << "Total number of each unit\t" << Earth.get_ESCreated() << " ES\t" << Earth.get_ETCreated() << " ET\t" << Earth.get_EGCreated() << " EG\t" << Earth.get_EHCreated() << " EH\t" << endl;
		MyfileHandler << "Percentage of  destructed units relative to their total\tES\tET\tEG\tEH" << endl;
		MyfileHandler << "                                                       \t" << ((Earth.get_ESCreated() != 0) ? ((Destrcuted[0] / Earth.get_ESCreated()) * 100) : 0) << "\t" << ((Earth.get_ETCreated() != 0) ? ((Destrcuted[1] / Earth.get_ETCreated()) * 100) : 0) << "\t" << ((Earth.get_EGCreated() != 0) ? ((Destrcuted[2] / Earth.get_EGCreated()) * 100) : 0) << "\t" << (Earth.get_EHCreated() != 0 ? (Destrcuted[3] / Earth.get_EHCreated()) * 100 : 0) << "\n";
		MyfileHandler << "Percentage of total destructed unit relative to total units\t" << ((Earth.get_ESCreated() + Earth.get_ETCreated() + Earth.get_EGCreated() + Earth.get_EHCreated()) != 0 ? ((Destrcuted[0] + Destrcuted[1] + Destrcuted[2] + Destrcuted[3]) / (Earth.get_ESCreated() + Earth.get_ETCreated() + Earth.get_EGCreated() + Earth.get_EHCreated()) * 100) : 0)<<endl;
		MyfileHandler << "The Percentage Of Units Healed Successfully Relative to Total Earth Units Created\t" << ((Earth.gethealed_soldeir_count() + Earth.gethealed_Tank_count()) / ((Earth.get_ESCreated() + Earth.get_ETCreated() + Earth.get_EGCreated() + Earth.get_EHCreated()))) * 100<<endl;
		MyfileHandler << "Average of Df\t" << "Average of Dd\t" << "Average of Db" << endl;
		MyfileHandler <<"       " << (CountOfEarth != 0 ? (sumOfDs[0] / CountOfEarth) : 0) <<"       " << "\t" << (CountOfEarth != 0 ? (sumOfDs[1] / CountOfEarth) : 0) << "\t" << "       " << (CountOfEarth != 0 ? (sumOfDs[2] / CountOfEarth) : 0) << endl;
		MyfileHandler << "Df/Db %" <<"\t" << "Dd/Db %\n";
		MyfileHandler << (sumOfDs[2] != 0 ? (sumOfDs[0] / sumOfDs[2]) : 0) << "\t" << (sumOfDs[2] != 0 ? (sumOfDs[1] / sumOfDs[2]) : 0) <<endl;
		MyfileHandler << endl << endl;
		//-------------------------------------------For Alien Army Data-----------------------------------
		MyfileHandler << "For Alien Army: " << endl;
		MyfileHandler << "Total number of each unit \t" << Aliens.get_ASCreated() << " AS\t" << Aliens.get_AMCreated() << " AM\t" << Aliens.get_ADCreated() << " AD\t" <<endl;
		MyfileHandler << "Percentage of  destructed units relative to their total\tAS\tAM\tAD" << endl;
		MyfileHandler << "                                                       \t" << (Aliens.get_ASCreated() != 0 ? (Destrcuted[4] / Aliens.get_ASCreated()) * 100 : 0) << "\t" << (Aliens.get_AMCreated() != 0 ? (Destrcuted[5] / Aliens.get_AMCreated()) * 100 : 0)<< "\t" << (Aliens.get_ADCreated() != 0 ? (Destrcuted[6] / Aliens.get_ADCreated()) * 100 : 0)<<"\n";
		MyfileHandler << "Percentage of total destructed unit relative to total units\t" << ((Aliens.get_ASCreated() + Aliens.get_AMCreated() + Aliens.get_ADCreated()) != 0 ? ((Destrcuted[4] + Destrcuted[5] + Destrcuted[6]) / (Aliens.get_ASCreated() + Aliens.get_AMCreated() + Aliens.get_ADCreated())) * 100 : 0)<< endl;
		MyfileHandler << "Average of Df\t" << "Average of Dd\t" << "Average of Db" << endl;
		MyfileHandler << "       " << (CountOfAlien != 0 ? (sumOfDs[3] / CountOfAlien) : 0)<< "       " << "\t" << (CountOfAlien != 0 ? (sumOfDs[4] / CountOfAlien) : 0) << "\t" << "       " << (CountOfAlien != 0 ? (sumOfDs[5] / CountOfAlien) : 0) << endl;
		MyfileHandler << "Df/Db %" << "\t" << "Dd/Db %\n";
		MyfileHandler << (sumOfDs[5] != 0 ? (sumOfDs[3] / sumOfDs[5]) : 0) << "\t" << (sumOfDs[5] != 0 ? (sumOfDs[4] / sumOfDs[5]) : 0)<< endl;
		//--------------------------------------------For Saver Army------------------------------------------------------
		MyfileHandler << "For Saver Army: " << endl;
		MyfileHandler << "Total number of Saver unit \t"<<ally.getCounter()-3000<<endl;

		MyfileHandler << "Percentage of total destructed unit relative to total units\t" << (ally.getCounter()-3000 != 0 ? (Destrcuted[7] / (ally.getCounter()-3000)) * 100 : 0) << endl;
		MyfileHandler << "Average of Df\t" << "Average of Dd\t" << "Average of Db" << endl;
		MyfileHandler << "       " << (CountOfSaver != 0 ? (sumOfDs[6] / CountOfSaver) : 0) << "       " << "\t" << (CountOfSaver != 0 ? (sumOfDs[7] / CountOfSaver) : 0) << "\t" << "       " << (CountOfSaver != 0 ? (sumOfDs[8] / CountOfSaver) : 0) << endl;
		MyfileHandler << "Df/Db %" << "\t" << "Dd/Db %\n";
		MyfileHandler << (sumOfDs[8] != 0 ? (sumOfDs[6] / sumOfDs[8]) : 0) << "\t" << (sumOfDs[8] != 0 ? (sumOfDs[7] / sumOfDs[8]) : 0) << endl;

		
		
		
		//-------------------------------------------For Infected-----------------------------------
		MyfileHandler << "For Infected Soldier: "<<endl;
		MyfileHandler<<"Total number of infected Soldiers: \t" << Earth.getinfectioncount() << endl;
		MyfileHandler << "Percantage of infected Soldiers: \t " << (Earth.get_ESCreated() != 0 ? Earth.getinfectioncount() / Earth.get_ESCreated() * 100 : 0);

		cout << "Produced Output File Check it out";
		return true;
	}
	else
	{
		cout << "Cannot Create The output File";
		return false;
	}

}
string GameManager::SelectMode()
{
	string returnMode="";
	int mode=0;
	while (mode != 1 && mode != 2)
	{
		cout << "Select The Mode Of Operation" << endl;
		cout << "1-Interactive Mode\n"<<"2-Silent Mode\n"<<"Option Number:";
		cin >> mode;
		cout << "------------------------------------------\n";
	}
	switch (mode)
	{
	case 1:
		setOpMode("Interactive");
		break;
	case 2:
		setOpMode("Silent");
	default:
		break;
	}
	cout << getOpMode();
	return getOpMode();
}
void GameManager::SilentMode() // Can Be modified Later to use Timers
{
	cout << "Silent Mode\n";
	char wait[] = { "..." };
	char OutputMsg[] = { "Simulation ends, Output file is Created" };
	cout << "Simulation Starts";
	int j = 0;
	while (wait[j] != '\0')
	{
		cout << wait[j];
		Sleep(500);
		j++;
	}
	cout << endl;


	int i = 0;
	while (OutputMsg[i] != '\0')
	{
		cout << OutputMsg[i];
		Sleep(100);
		i++;
	}
	cout << endl;
}
//priQueue<Unit*> GameManager::SortKilledList()
//{
//	priQueue<Unit*> Sorted;
//	
//	Unit* temp=NULL;
//	//LinkedQueue <Unit*> templist = KilledList;
//	while (KilledList.dequeue(temp))
//	{
//		Sorted.enqueue(temp, temp->getid());
//	}
//	LinkedStack<Unit*> tempstack;
//	while(Sorted.dequeue())
//	return Sorted;
//}

void GameManager::simulate_phase2() {
	string mode = SelectMode();
	if (true) {
		GetInput();


		while ((getTimestep() <= 40 || getBattleResult() == "Draw") && getTimestep() <= 500) {
			RandGen.RandomUnitGenratorAlgortihm();
			if (Earth.getinfection_Per() == 0) {
				killally();
			}
			if (mode == "Interactive") {
				print1();
			}
			
			Earth.attack();
			Aliens.attack();
			ally.setInfectionPercentage(Earth.getinfection_Per());
			ally.attack();
			Earth.spreadinfection();
			Earth.Calc_inf_Perc();
			
			if (mode == "Interactive") {
				print2();
				cout << "Press Enter to continue..." << endl;
				cin.get();
			}
			if ((Earth.GetEGunnery().getcount() + Earth.GetETank().getcount() + Earth.GetESoldier().getcount()+UMLsoldier.getcount()+UMLtank.getcount()) == 0) {
				//setResult("Loss");
				if (getTimestep() >40)
				{
					setResult("Loss");
					break;

				}
			}
			else if ((Aliens.GetADrone().getcount() + Aliens.GetAMonster().getcount() + Aliens.GetASoldier().getcount()) == 0) {
				if (getTimestep() > 40)
				{
					setResult("Win");

					break;

				}
			}
			setTimestep(getTimestep() + 1);
		}
	}
	if (mode == "Silent")
	{
		SilentMode();
	}
	ProduceOutputFile();
}

int GameManager::getinf_thres()
{
	return inf_thres;
}

void GameManager::Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

}

void GameManager::gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void GameManager::clearScreen()
{
	system("cls");
}
int GameManager::SelectSencario()
{
	clearScreen();
	const int DEFAULT_COLOR = 7;
	const int HIGHLIGHT_COLOR = 12;
	const int NUM_OPTIONS = 6;
	int Menu[NUM_OPTIONS] = { DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR };
	int Counter = 0;
	char key;

	while (true) {
		// Display menu options
		for (int i = 0; i < NUM_OPTIONS; i++) {
			gotoxy(0, i); // Start from the beginning of the console
			Color(Menu[i]);
			cout << "File Number " << i + 1 << "     "; // Add spaces to clear previous highlight
		}

		key = _getch(); // Wait for a key press

		// Handle key presses
		if (key == 72 && Counter > 0) { // Up arrow key
			Counter--;
		}
		if (key == 80 && Counter < NUM_OPTIONS - 1) { // Down arrow key
			Counter++;
		}
		if (key == '\r') { // Enter key
			clearScreen();
			gotoxy(0, 0); // Move to the beginning of the console
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			//cout << "You Have Selected File Number " << Counter + 1 << endl;
			return Counter + 1;
			break; // Exit the loop after selection
		}

		// Reset menu colors
		for (int i = 0; i < NUM_OPTIONS; i++) {
			Menu[i] = DEFAULT_COLOR;
		}
		Menu[Counter] = HIGHLIGHT_COLOR;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
