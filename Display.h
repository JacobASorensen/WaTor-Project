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


class Display {
	public:
	Display() : aquaticCounts(20,0) {};
	char GetEntityChar(std::shared_ptr<EntityT> entity);
	std::string CreateFirstLine(WorldT& world);
	std::string CreateLine(WorldT& world, CoordT current);
	void PrintWorld(WorldT& world, InfoT& initialConditions);
	void PrintFishInfo(InfoT& initialConditions);
	void PressEnter();
	private:

	std::vector<int> aquaticCounts;
};