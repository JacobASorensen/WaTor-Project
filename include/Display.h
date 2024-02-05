#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include "WorldT.h"
#include "Entities.h"
#include "GodT.h"


const std::string FISH_CHAR = "\033[32mf\033[0m";
const std::string SHARK_CHAR = "\033[34mS\033[0m";
const std::string BOTTOM_FEEDER_CHAR = "\033[33mB\033[0m";
const std::string WHALE_CHAR = "W\033[0m";
const std::string ROCK_CHAR = "\033[35mR\033[0m";
const std::string VOLCANO_CHAR = "\033[31mV\033[0m";
const std::string EMPTY_WATER = "\033[36m.\033[0m";
//const char WHALE_CHAR = 'W';
//const char WHALE_CHAR = 'W';
//const char WHALE_CHAR = 'W';


class Display {
	public:
	Display() : aquaticCounts(20,0) {};
	std::string GetEntityChar(std::shared_ptr<EntityT> entity);
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