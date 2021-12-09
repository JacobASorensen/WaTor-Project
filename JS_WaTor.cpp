#include "Entities.h"
#include "WorldT.h"
#include "GodT.h"
#include "Display.h"
//#include <iostream>
//using namespace std;

void PrintInitialSettings(InfoT& initConds);

int main() {
	GodT Poseidon;

	//cout << "Getting Info..." << endl;
	Poseidon.GetInfo("wator.init");
	
	//cout << "Creating World..." << endl;
	WorldT theEarthIsATorus(Poseidon.OrdainedWidth(),Poseidon.OrdainedHeight());
	
	//cout << "Populating World..." << endl;
	if( (theEarthIsATorus.WorldWidth() > 0) 
		&& (theEarthIsATorus.WorldHeight() > 0) ){
		Poseidon.Populate(theEarthIsATorus);
	}
	Display worldWindow;

	PrintInitialSettings(Poseidon.InitialConditions());

	//cout << "Displaying World..." << endl;
	worldWindow.PrintWorld(theEarthIsATorus,Poseidon.InitialConditions());
	worldWindow.PressEnter();
	while(true) {
		theEarthIsATorus.Tick();
		worldWindow.PrintWorld(theEarthIsATorus,Poseidon.InitialConditions());
		worldWindow.PressEnter();
	}
	
	return 0;
}