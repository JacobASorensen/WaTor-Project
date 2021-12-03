#include "Entities.h"
#include "WorldT.h"
#include "GodT.h"
#include "Display.h"
#include <iostream>
using namespace std;

void PrintInitialSettings(InfoT& initConds);

int main() {
	GodT Poseidon;

	cout << "Getting Info..." << endl;
	Poseidon.GetInfo("wator.init");
	
	cout << "Creating World..." << endl;
	WorldT theEarthIsATorus(Poseidon.OrdainedWidth(),Poseidon.OrdainedWidth());
	
	cout << "Populating World..." << endl;
	if( (theEarthIsATorus.WorldWidth() > 0) 
		&& (theEarthIsATorus.WorldHeight() > 0) ){
		Poseidon.Populate(theEarthIsATorus);
	}
	Display worldWindow;

	PrintInitialSettings(Poseidon.InitialConditions());

	cout << "Displaying World..." << endl;
	worldWindow.PrintWorld(theEarthIsATorus,Poseidon.InitialConditions());
	worldWindow.PressEnter();
	while(true) {
		theEarthIsATorus.Tick();
		worldWindow.PrintWorld(theEarthIsATorus,Poseidon.InitialConditions());
		worldWindow.PressEnter();
	}

	

	
	return 0;
}

void PrintInitialSettings(InfoT& initConds) {
	cout << endl << endl;
	cout << "Initial Settings: " << endl;

	cout << "World Width: " << initConds.worldWidth;
	cout << ", World Height: " << initConds.worldHeight << endl;

	cout << "Fish Num: " << initConds.fishNum;
	cout << "Fish Breed: " << initConds.fishBreed << endl;

	cout << "Shark Num: " << initConds.sharkNum;
	cout << ", Shark Starve: " << initConds.sharkStarve;
	cout << ", Shark Breed: " << initConds.sharkBreed << endl;

	cout << "Bottom Feeder Num: " << initConds.bottomFeederNum;
	cout << ", Bottom Feeder Num: " << initConds.bottomFeederBreed;
	cout << ", Bottom Feeder Num: " << initConds.bottomFeederStarve << endl;

	cout << "Whale Num: " << initConds.whaleNum;
	cout << ", Whale Breed: " << initConds.whaleBreed << endl;

	cout << "Rock Num: " << initConds.rockNum;
	cout << "Volcano Num: " << initConds.volcanoNum << endl;
	cout << endl << endl;
	return;
}