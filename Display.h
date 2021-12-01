#include <string>
#include <iostream>
#include <iomanip>
#include <list>
#include "WorldT.h"
#include "Entities.h"
#include "GodT.h"

#pragma once


const char FISH_CHAR = 'F';


class Display {
	public:
	char GetEntityChar(std::shared_ptr<EntityT> entity);
	std::string CreateFirstLine(WorldT& world);
	std::string CreateLine(WorldT& world, CoordT& current);
	void PrintWorld(WorldT& world, InfoT& initialConditions);
	void PrintFishInfo(WorldT & world,InfoT& initialConditions);
	void PressEnter();
	private:

	int aquaticCounts[20]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
};