#include "Entities.h"
#include "WorldT.h"
#include <random>

int RandBetween(int low, int high) {
    std::default_random_engine static generator;
    std::uniform_int_distribution<int> randNum(low,high);
    return randNum(generator);
}
/*
template <typename T> 
bool IsEntityType(const std::shared_ptr<EntityT> check) {
    bool isType = false;
    if(T* testVar = dynamic_cast<T*>(check.get()) ) {
        isType = true;
    }
    return isType;
} */

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
        World.MoveEntity(myLoc,nearbyCoords[emptyLocs[RandBetween(0, static_cast<int>(emptyLocs.size() - 1))]]);
        haveMoved = true;
    }
    return haveMoved;
}

FishT::FishT(int& breedCool) {
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


