#include "GodT.h"
#include "WorldT.h"
#include "Entities.h"
#include <fstream>
#include <string>
#include <iostream>

GodT::GodT() {
}

void GodT::ObtainData(int& num, std::ifstream& gameData) {
	if(gameData) {
		gameData >> num;
		if(num < 0) {
			num = 0;
		}
	}
}


void GodT::GetInfo(std::string fileName) {
	std::ifstream gameData;

	gameData.open(fileName.c_str());
	ObtainData(worldInfo.worldWidth,gameData);
	ObtainData(worldInfo.worldHeight,gameData);

	ObtainData(worldInfo.fishNum,gameData);
	ObtainData(worldInfo.fishBreed,gameData);

	ObtainData(worldInfo.sharkNum,gameData);
	ObtainData(worldInfo.sharkStarve,gameData);
	ObtainData(worldInfo.sharkBreed,gameData);

	ObtainData(worldInfo.bottomFeederNum,gameData);
	ObtainData(worldInfo.bottomFeederBreed,gameData);
	ObtainData(worldInfo.bottomFeederStarve,gameData);

	
	ObtainData(worldInfo.whaleNum,gameData);
	ObtainData(worldInfo.whaleBreed,gameData);

	ObtainData(worldInfo.rockNum,gameData);
	ObtainData(worldInfo.volcanoNum,gameData);
	ObtainData(worldInfo.volcanoDoomsday,gameData);
	gameData.close();

	return;
}

InfoT& GodT::InitialConditions() {
	return worldInfo;
}

int GodT::OrdainedWidth() {
	return worldInfo.worldWidth;
}

int GodT::OrdainedHeight() {
	return worldInfo.worldHeight;
}

void GodT::Populate(WorldT& theEarthIsATorus) {

	
	//std::cout << "Populating Fish..." << std::endl;
	for(int i = 0; i < worldInfo.fishNum; i++) {
		CoordT newCoord(theEarthIsATorus.RandomCoord());
		//std::cout << "Making Fish..." << i << " at " << newCoord.X() << "," << newCoord.Y() << std::endl;
		auto newFishy = std::make_shared<FishT>(worldInfo.fishBreed);
		theEarthIsATorus.AddEntity(newFishy,newCoord);
	}

	//std::cout << "Populating Sharks..." << std::endl;
	for(int i = 0; i < worldInfo.sharkNum; i++) {
		CoordT newCoord(theEarthIsATorus.RandomCoord());
		auto newFishy = std::make_shared<SharkT>(worldInfo.sharkBreed,worldInfo.sharkStarve);
		theEarthIsATorus.AddEntity(newFishy,newCoord);
	}


}


