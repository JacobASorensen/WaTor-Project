#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include "WorldT.h"
#include "Entities.h"
#include "GodT.h"


const char FISH_CHAR = 'f';
const char SHARK_CHAR = 'S';
const char BOTTOM_FEEDER_CHAR = 'B';
const char WHALE_CHAR = 'W';
const char ROCK_CHAR = 'R';
const char VOLCANO_CHAR = 'V';

//const char WHALE_CHAR = 'W';
//const char WHALE_CHAR = 'W';
//const char WHALE_CHAR = 'W';


class Display {
	public:
	Display() : aquaticCounts(20,0) {};
	char GetEntityChar(std::shared_ptr<EntityT> entity);
	std::string CreateFirstLine(WorldT& world);
	std::string CreateLine(WorldT& world, CoordT current);
	void PrintWorld(WorldT& world, InfoT& initialConditions);
	void PrintFishInfo(InfoT& initialConditions);
	void PressEnter();
	void PrintInitialSettings(InfoT& initConds);
	private:

	//counts each type of entity for
	//PrintFishInfo output
	std::vector<int> aquaticCounts;
};