#include "Entities.h"
#include "WorldT.h"
#include "GodT.h"
#include "Display.h"
//using namespace std;

int main() {
	GodT Poseidon;

	Poseidon.GetInfo("wator.init");

	WorldT theEarthIsATorus(Poseidon.OrdainedWidth(),Poseidon.OrdainedWidth());

	if( (theEarthIsATorus.WorldWidth() > 0) 
		&& (theEarthIsATorus.WorldHeight() > 0) ){
		Poseidon.Populate(theEarthIsATorus);
	}
	Display worldWindow;

	worldWindow.PrintWorld(theEarthIsATorus,Poseidon.InitialConditions());
	worldWindow.PressEnter();
	while(true) {
		theEarthIsATorus.Tick();
		worldWindow.PrintWorld(theEarthIsATorus,Poseidon.InitialConditions());
		worldWindow.PressEnter();
	}

	
	return 0;
}