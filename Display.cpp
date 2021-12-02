#include "Display.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <list>
#include "WorldT.h"
#include "Entities.h"
#include "GodT.h"

char Display::GetEntityChar(std::shared_ptr<EntityT> entity) {

    if(entity.get() != nullptr) {
        if(IsEntityType<FishT>(entity)) {
            aquaticCounts[0]++;
            return FISH_CHAR;
        }
    }
    return '.';
}

std::string Display::CreateFirstLine( WorldT& world) {
    std::string returnString;
    returnString = "  ";
    for(int i = 0; i < world.WorldWidth(); i++) {
        returnString += static_cast<char>(i + static_cast<int>(0));
        if(i <= world.WorldWidth() - 1) {
            returnString += ' ';
        }
    }
    return returnString;
}

std::string Display::CreateLine( WorldT& world, CoordT& current) {
    std::string returnString;
    returnString = "  ";
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
        current = world.Right(current);
        current = world.Up(current);
    }
    
    PrintFishInfo(initialConditions);

    std::list<std::string>::iterator ptr;

    for(ptr = worldAsString.begin(); ptr != worldAsString.end(); ptr++) {
        std::cout << *ptr << std::endl;
    }
    
}

void Display::PrintFishInfo(InfoT& initialConditions) {
    
    if(initialConditions.fishNum > 0) {
        std::cout << "\tFish (" << FISH_CHAR << "): " << aquaticCounts[0];
    }
    std::cout << std::endl;


    for(size_t i = 0; i < aquaticCounts.size(); i++) {
        aquaticCounts[i] = 0;
    }
}

void Display::PressEnter() {
    std::string literalGarbage; 
    std::cout << "Press Enter to continue...";
    getline(std::cin,literalGarbage);
    return;
}