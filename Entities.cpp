#include "Entities.h"
#include "WorldT.h"
#include <random>

int RandBetween(int low, int high) {
    std::random_device dev;
    static std::mt19937 generator(dev());
    std::uniform_int_distribution<int> randNum(low,high);
    return randNum(generator);
}


//Its very basic, and only looks at the 4 locations around itself
//The base animal Move function just prevents the animal
//from moving onto another animal
bool AnimalT::Move(const CoordT& myLoc,WorldT& World) {
    nearbyCoords.clear();
    World.WhatIsNearby(myLoc,1,nearbyCoords);
    std::vector<int> emptyLocs;
    bool haveMoved = false;
    
    for(size_t i = 0; i < nearbyCoords.size(); i++) {
        if(World.IsEmpty(nearbyCoords[i])) {
            emptyLocs.emplace_back(i);
        }
    }
    if(emptyLocs.size() > 0) {
        int randIndex = RandBetween(0, static_cast<int>(emptyLocs.size() - 1));
        World.MoveEntity(myLoc,nearbyCoords[emptyLocs[randIndex]]);
        haveMoved = true;
    }
    return haveMoved;
}

FishT::FishT(const int& breedCool) {
    breedCooldown = breedCool;
    sightDistance = 1;
    isReadyToBreed = false;
    turnsSinceLastBreed = 0;
}

void FishT::Reproduce(const CoordT& newLoc,WorldT& World) {
    auto newFishy = std::make_shared<FishT>(breedCooldown);
    World.AddEntity(newFishy,newLoc);
    return;
}

void FishT::TakeTurn(const CoordT& newLoc,WorldT& World) {
    CoordT startingLoc(newLoc);
    turnsSinceLastBreed++;

    if( (not isReadyToBreed) && (turnsSinceLastBreed >= breedCooldown) ) {
        isReadyToBreed = true;
    }

    if(Move(newLoc,World) && isReadyToBreed) {
        Reproduce(startingLoc,World);
        isReadyToBreed = false;
        turnsSinceLastBreed = 0;
    }
    return;
}

SharkT::SharkT(int& sharkBreed,int& sharkStarve) {
    breedCooldown = sharkBreed;
    starveTime = sharkStarve;
    sightDistance = 0;
    isReadyToBreed = false;
    turnsSinceLastBreed = 0;
    turnsSinceLastMeal = 0;
}

void SharkT::Reproduce(const CoordT& newLoc,WorldT& World) {
    auto newSharky = std::make_shared<SharkT>(breedCooldown,starveTime);
    World.AddEntity(newSharky,newLoc);
    return;
}

bool SharkT::Move(const CoordT& myLoc,WorldT& World) {
    nearbyCoords.clear();
    World.WhatIsNearby(myLoc,1,nearbyCoords);
    std::vector<int> emptyLocs;
    std::vector<int> fishLocs;
    bool haveMoved = false;
    
    for(size_t i = 0; i < nearbyCoords.size(); i++) {
        if(World.IsEmpty(nearbyCoords[i])) {
            emptyLocs.emplace_back(i);
        } else {
            if( not IsEntityType<SharkT>(World.EntityAt(nearbyCoords[i]))
                && not IsEntityType<InanimateT>(World.EntityAt(nearbyCoords[i]))) {
                fishLocs.emplace_back(i);
            }
        }
    }

    if(fishLocs.size() > 0) {
        int randIndex = RandBetween(0, static_cast<int>(fishLocs.size() - 1));
        World.MoveEntity(myLoc,nearbyCoords[fishLocs[randIndex]]);
        haveMoved = true;
        turnsSinceLastMeal = 0;
    } else if(emptyLocs.size() > 0) {
        int randIndex = RandBetween(0, static_cast<int>(emptyLocs.size() - 1));
        World.MoveEntity(myLoc,nearbyCoords[emptyLocs[randIndex]]);
        haveMoved = true;
    }

    return haveMoved;
}

void SharkT::TakeTurn(const CoordT& myLoc,WorldT& World) {
    CoordT startingLoc(myLoc);
    turnsSinceLastBreed++;
    turnsSinceLastMeal++;

    if(turnsSinceLastMeal >= starveTime) {
        World.RemoveEntity(myLoc);
    } else {
        if( (not isReadyToBreed) && (turnsSinceLastBreed >= breedCooldown) ) {
            isReadyToBreed = true;
        }

        if(Move(myLoc,World) && isReadyToBreed) {
            Reproduce(startingLoc,World);
            isReadyToBreed = false;
            turnsSinceLastBreed = 0;
        }
    }

    return;
}