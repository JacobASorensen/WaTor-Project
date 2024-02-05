#include "Display.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <list>
#include "WorldT.h"
#include "Entities.h"
#include "GodT.h"

std::string Display::GetEntityChar(std::shared_ptr<EntityT> entity) {

    if(entity.get() != nullptr) {
        if(IsEntityType<FishT>(entity)) {
            if(IsEntityType<WhaleT>(entity)) {
                aquaticCounts[3]++;
                return WHALE_CHAR;
            } else {
                aquaticCounts[0]++;
                return FISH_CHAR;
            }
        } else if(IsEntityType<SharkT>(entity)) {
            aquaticCounts[1]++;
            return SHARK_CHAR;
        } else if(IsEntityType<BottomFeederT>(entity)) {
            aquaticCounts[2]++;
            return BOTTOM_FEEDER_CHAR;
        } else if(IsEntityType<RockT>(entity)) {
            aquaticCounts[4]++;
            return ROCK_CHAR;
        } else if(IsEntityType<VolcanoT>(entity)) {
            aquaticCounts[5]++;
            return VOLCANO_CHAR;
        } 
    }
    return EMPTY_WATER;
}

std::string Display::CreateFirstLine( WorldT& world) {
    std::string returnString;
    returnString = "   ";
    for(int i = 0; i < world.WorldWidth(); i++) {
        if(i < 9) {
            returnString += static_cast<char>(i + static_cast<int>('0'));
            if(i <= world.WorldWidth() - 1) {
                returnString += ' ';
            }
        } else {
            returnString += std::to_string(i);
        }
    }
    return returnString;
}

std::string Display::CreateLine( WorldT& world, CoordT current) {
    std::string returnString;
    returnString = " ";
    for(int i = 0; i < world.WorldWidth(); i++) {
        returnString += GetEntityChar(world.EntityAt(current));
        if(i <= world.WorldWidth() - 1) {
            returnString += ' ';
        }
        current = world.Right(current);
    }
    return returnString;
}

void Display::PrintWorld(WorldT& world, InfoT& initialConditions) {
    std::list<std::string> worldAsString;
    CoordT current(world.ZeroCoord());
    worldAsString.push_back(CreateFirstLine(world));

    for(int i = 0; i < world.WorldHeight();i++ ) {
        worldAsString.push_back(CreateLine(world,current));
        current = world.Down(current);
    }
    
    std::cout << "Turn: " << world.WorldAge() << std::endl;

    PrintFishInfo(initialConditions);

    std::list<std::string>::iterator ptr;

    int i = 0;
    for(ptr = worldAsString.begin(); ptr != worldAsString.end(); ptr++) {
        if(i > 0) {
            if(i <= 10) {
                std::cout << i - 1 << " ";
            } else {
                std:: cout << std::to_string(i-1);
            }
        }
       
       std::cout << *ptr << std::endl;
       i++;
    }
    
}

void Display::PrintFishInfo(InfoT& initialConditions) {
    
    if(initialConditions.fishNum > 0) {
        std::cout << "\tFish (" << FISH_CHAR << "): " << aquaticCounts[0];
    }
    if(initialConditions.bottomFeederNum > 0) {
        std::cout << "\tBottom Feeders (" << BOTTOM_FEEDER_CHAR << "): " << aquaticCounts[2];
    }
    if(initialConditions.whaleNum > 0) {
        std::cout << "\tWhales (" << WHALE_CHAR << "): " << aquaticCounts[3];
    }

    std::cout << std::endl;
    if(initialConditions.sharkNum > 0) {
        std::cout << "\tSharks (" << SHARK_CHAR << "): " << aquaticCounts[1];
    }
    if( (initialConditions.rockNum > 0) || (initialConditions.volcanoNum > 0) ) {
        std::cout << "\tRocks (" << ROCK_CHAR << "): " << aquaticCounts[4];
    }
    if(initialConditions.volcanoNum > 0) {
        std::cout << "\tVolcanos (" << VOLCANO_CHAR << "): " << aquaticCounts[5];
    }

    for(size_t i = 0; i < aquaticCounts.size(); i++) {
        aquaticCounts[i] = 0;
    }
    std::cout << std::endl;
}

void Display::PressEnter() {
    std::string literalGarbage; 
    std::cout << "Press Enter to continue...";
    getline(std::cin,literalGarbage);
    return;
}

void PrintInitialSettings(InfoT& initConds) {
    using namespace std;
	cout << endl;
	cout << "Initial Settings: " << endl;

	cout << "World Width: " << initConds.worldWidth << endl;
	cout << "World Height: " << initConds.worldHeight << endl << endl;

	cout << "Fish Num: " << initConds.fishNum << endl;
	cout << "Fish Breed: " << initConds.fishBreed << endl << endl;

	cout << "Shark Num: " << initConds.sharkNum << endl;
	cout << "Shark Starve: " << initConds.sharkStarve << endl;
	cout << "Shark Breed: " << initConds.sharkBreed << endl << endl;

	cout << "Bottom Feeder Num: " << initConds.bottomFeederNum << endl;
	cout << "Bottom Feeder Starve: " << initConds.bottomFeederStarve << endl;
	cout << "Bottom Feeder Breed: " << initConds.bottomFeederBreed << endl << endl;

	cout << "Whale Num: " << initConds.whaleNum << endl;
	cout << "Whale Breed: " << initConds.whaleBreed << endl;
	cout << "Whale Cannibal: ";
	if (initConds.whaleCannibal == 1) {
		cout << "TRUE";
	} else {
		cout << "FALSE";
	}
	cout << endl << endl;

	cout << "Rock Num: " << initConds.rockNum << endl;
	cout << "Rock Erode Min: " << initConds.rockErodeMin << endl;
	cout << "Rock Erode Max: " << initConds.rockErodeMax << endl << endl;

	cout << "Volcano Num: " << initConds.volcanoNum << endl;
	cout << "Volcano Move Freq: " << initConds.volcanoMoveFreq << endl;
	cout << "Volcano Spew Freq: " << initConds.volcanoSpewFreq << endl << endl;
	cout << "Volcano Spew Magnitude: " << initConds.volcanoSpewMag << endl;
	cout << "Volcano Spew Range: " << initConds.volcanoSpewRange << endl;
	cout << "Volcano Doomsday Delay: " << initConds.volcanoDoomsday << endl << endl;
	cout << endl << endl;
	return;
}