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
        } else if(IsEntityType<SharkT>(entity)) {
            aquaticCounts[1]++;
            return SHARK_CHAR;
        }
    }
    return '.';
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
            if(i < 10) {
                std::cout << i << " ";
            } else {
                std:: cout << std::to_string(i);
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
    std::cout << std::endl;
    if(initialConditions.fishNum > 0) {
        std::cout << "\tSharks (" << SHARK_CHAR << "): " << aquaticCounts[1];
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