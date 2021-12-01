#include "WorldT.h"
#include "Entities.h"
#include <fstream>
#include <string>

#pragma once

struct InfoT {
int worldWidth = 0;
int worldHeight = 0;
int fishNum = 0;
int fishBreed = 0;
int sharkNum = 0;
int sharkStarve = 0;
int sharkBreed = 0;
int bottomFeederNum = 0;
int bottomFeederStarve = 0;
int sonarFishNum = 0;
int rockNum = 0;
int volcanoNum = 0;
};

class GodT {
	public: 
	GodT();
	void GetInfo(std::string fileName);
	
	void Populate(WorldT& theEarthIsATorus);

	int OrdainedWidth();
	int OrdainedHeight();
	InfoT& InitialConditions();

	private:
	void ObtainData(int& num, std::ifstream& gameData);
	InfoT worldInfo;
};
