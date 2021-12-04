#include "Entities.h"
#include "WorldT.h"
#include <random>
//#include <iostream>

int RandBetween(int low, int high) {
    std::random_device dev;
    static std::mt19937 generator(dev());
    std::uniform_int_distribution<int> randNum(low,high);
    return randNum(generator);
}


//The base animal Move function is very basic
//it only looks at the 4 locations around itself and just
//prevents the animal from moving onto another entity
bool AnimalT::Move(CoordT& myLoc,WorldT& World) {
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

//***************************************
//Fish Section
//***************************************

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

void FishT::TakeTurn(CoordT& newLoc,WorldT& World) {
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

//***************************************
//Shark Section
//***************************************

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

bool SharkT::Move(CoordT& myLoc,WorldT& World) {
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
                && not IsEntityType<InanimateT>(World.EntityAt(nearbyCoords[i]))
                && not IsEntityType<WhaleT>(World.EntityAt(nearbyCoords[i]))) {
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

void SharkT::TakeTurn(CoordT& myLoc,WorldT& World) {
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

//***************************************
//Rock Section
//***************************************

RockT::RockT(int& erMin,int& erMax): erodeMin(erMin), erodeMax(erMax) {
    age = 0;
}

bool RockT::Erode() {
    if(age > erodeMin) {
        int diff = erodeMax - (age - erodeMin);
        if(diff <= 0) {
            return true;
        } else if(RandBetween(0,diff) == 0) {
            return true;
        }
    }
    return false;
}

void RockT::TakeTurn(CoordT& myLoc,WorldT& World) {
    age++;
    if(Erode()) {
        World.RemoveEntity(myLoc);
    }
}

//***************************************
//Volcano Section
//***************************************

VolcanoT::VolcanoT(int& rMin,int& rMax,int& mF,int& sF,int& sM,int& sR,int& ddT) {
    age = 0;
    rockErodeMin = rMin;
    rockErodeMax = rMax;
	moveFreq = mF;
	spewFreq = sF;
	spewMag = sM;
	spewRange = sR;
    doomsdayTimer = ddT;
    timeSinceLastMove = 0;
    timeSinceLastSpew = 0;

    xMove = 1;
    if (RandBetween(0,1) == 0) {
        xMove = 2;
    }
    yMove = 3 - xMove;

    eastMoving = (RandBetween(0,1) == 0);
    northMoving = (RandBetween(0,1) == 0);
}

void VolcanoT::Move(CoordT& myLoc,WorldT& World) {
    if (RandBetween(0,1) == 0) {
        XMove(myLoc,World);
        YMove(myLoc,World);
    } else {
        YMove(myLoc,World);
        XMove(myLoc,World);
    }
    timeSinceLastMove = 0;
}

void VolcanoT::XMove(CoordT& myLoc,WorldT& World) {
   for(int i = 0; i < xMove; i++) {
        if(eastMoving) {
            World.MoveEntity(myLoc,World.Right(myLoc));
        } else {
            World.MoveEntity(myLoc,World.Left(myLoc));
        }
    }
}

void VolcanoT::YMove(CoordT& myLoc,WorldT& World) {
    for(int i = 0; i < yMove; i++) {
        if(northMoving) {
            World.MoveEntity(myLoc,World.Up(myLoc));
        } else {
            World.MoveEntity(myLoc,World.Down(myLoc));
        }
    }
}

void VolcanoT::Doomsday(const CoordT& myLoc,WorldT& World) {
    int x = 0;
    int i = 0;
    while(x < World.WorldWidth() * World.WorldHeight()) {
        x = 4*i + x;
        i++;
    }
    x = x - 4*i;
    i--;
    nearbyCoords.clear();
    World.WhatIsNearby(myLoc,i,nearbyCoords);
    for(size_t z = 0; z < nearbyCoords.size(); z++) {
        if(not IsEntityType<VolcanoT>(World.EntityAt(nearbyCoords[z]))) {
            auto newEntity = std::make_shared<RockT>(rockErodeMin,rockErodeMax);
            World.AddEntity(newEntity,nearbyCoords[z]);
        }
    }
    nearbyCoords.clear();
    return;
}

void VolcanoT::SpawnRocks(const CoordT& myLoc,WorldT& World) {
    if(spewMag > 0 && spewRange > 0) {
        nearbyCoords.clear();
        World.WhatIsNearby(myLoc,spewRange,nearbyCoords);
        int randIndex = 0;
        for(int i = 0; i < spewMag; i++) {
            randIndex = RandBetween(0,static_cast<int>(nearbyCoords.size()) - 1);
            if(not IsEntityType<VolcanoT>(World.EntityAt(nearbyCoords[randIndex]))) {
                auto newEntity = std::make_shared<RockT>(rockErodeMin,rockErodeMax);
                World.AddEntity(newEntity,nearbyCoords[randIndex]);
            }
        }
    }
    return;
}

void VolcanoT::TakeTurn(CoordT& myLoc,WorldT& World) {
    age++;
    timeSinceLastMove++;
    int randChance = 0;

    if(age % doomsdayTimer == 0) {
        Doomsday(myLoc,World);
    } else {
        randChance = spewFreq - timeSinceLastSpew;
        if(randChance <= 0 || RandBetween(0,randChance) == 0) {
            SpawnRocks(myLoc,World);
        }
        randChance = moveFreq - timeSinceLastMove;
        if(randChance <= 0 || RandBetween(0,randChance) == 0) {
            Move(myLoc,World);
        }
    }

}

//***************************************
//Bottom Feeder Section
//***************************************

BottomFeederT::BottomFeederT(int bFB,int bFS) {
    sightDistance = 1;
	breedCooldown = bFB;
	turnsSinceLastBreed = 0;

    starveTime = bFS;
    turnsSinceLastMeal = 0;
	isReadyToBreed = false;
}

bool BottomFeederT::IsNearRock(WorldT& World) {
    bool isNearRock = false;
    for(size_t i = 0; i < nearbyCoords.size(); i++) {
        if(IsEntityType<RockT>(World.EntityAt(nearbyCoords[i]))) {
            isNearRock = true;
        }
    }
    return isNearRock;
}

void BottomFeederT::Reproduce(WorldT& World) {
    std::vector<int> emptyLocs;
    
    for(size_t i = 0; i < nearbyCoords.size(); i++) {
        if(World.IsEmpty(nearbyCoords[i])) {
            emptyLocs.emplace_back(i);
        }
    }
    if(emptyLocs.size() > 0) {
        int randIndex = RandBetween(0, static_cast<int>(emptyLocs.size() - 1));
        auto newFishy = std::make_shared<BottomFeederT>(breedCooldown,starveTime);
        World.AddEntity(newFishy,nearbyCoords[emptyLocs[randIndex]]);
    }
    
    return;
}

//a combination of pedantic compiler flags and a pure virtual 
//version of Reproduce in AnimalT necessitates the following useless function
//I would fix this by templating AnimalT's Reproduce function, but alas; no time
void BottomFeederT::Reproduce(const CoordT& newLoc,WorldT& World) {
    if(IsEntityType<EntityT>(World.EntityAt(newLoc))) {
        return;
    } else {
        return;
    }
}

void BottomFeederT::TakeTurn(CoordT& myLoc,WorldT& World) {
    turnsSinceLastBreed++;
    turnsSinceLastMeal++;
    
    if(turnsSinceLastBreed >= breedCooldown) {
        isReadyToBreed = true;
    }

    nearbyCoords.clear();
    World.WhatIsNearby(myLoc,1,nearbyCoords);

    if(IsNearRock(World)) {
        turnsSinceLastMeal = 0;
        if(isReadyToBreed) {
            BottomFeederT::Reproduce(World);
            isReadyToBreed = false;
            turnsSinceLastBreed = 0;
        }
    } else if (turnsSinceLastMeal >= starveTime) {
        World.RemoveEntity(myLoc);
    } else {
        Move(myLoc,World);
    }
    return;
}

//***************************************
//Whale Section
//***************************************

WhaleT::WhaleT(const int& breed,const bool& isCanB,const CoordT& newLoc, WorldT& world): FishT(breed),isCannibal(isCanB), lastKnownCoord(newLoc), lastKnownWorld(world) {
}

WhaleT::~WhaleT() {
   // std::cout << "Whale Destructor Called..." << std::endl;
   // std::cout << "There are " << swallowedAnimals.size() << " animals inside the whale..." << std::endl;
    size_t x = 0;
    int i = 0;
    while(x < static_cast<size_t>(lastKnownWorld.WorldHeight() * lastKnownWorld.WorldWidth())) {
        x = 4*static_cast<size_t>(i) + x;
        i++;
    }
    i--;
    //std::cout << "looking around last coord x: " << lastKnownCoord.X() << " y: " << lastKnownCoord.Y() << std::endl;
    //std::cout << x << " number of spaces, with " << i << "vision..." << std::endl;
    nearbyCoords.clear();
    lastKnownWorld.WhatIsNearby(lastKnownCoord,i,nearbyCoords);

    std::list<std::shared_ptr<EntityT>>::iterator ptr;
    ptr = swallowedAnimals.begin();
    int z = 0;
    while(ptr != swallowedAnimals.end() 
            && static_cast<size_t>(z) < nearbyCoords.size()) {
        if(lastKnownWorld.IsEmpty(nearbyCoords[z])) {
           // std::cout << "spilling entity to: " << nearbyCoords[z].X() << " y: " << nearbyCoords[z].Y() << std::endl;
            lastKnownWorld.AddEntity(*ptr,nearbyCoords[z]);
        }
        z++;
        ptr++;
    }

}

bool WhaleT::Move(CoordT& myLoc,WorldT& World) {
    bool hasMoved = false;
    CoordT randCoord(myLoc);
    int RandLoc = 0;
    RandLoc = RandBetween(0,3);
    if(RandLoc == 0) {
        randCoord = World.Up(randCoord);
    } else if(RandLoc == 1) {
        randCoord = World.Down(randCoord);
    } else if(RandLoc == 2) {
        randCoord = World.Left(randCoord);
    } else if(RandLoc == 3) {
        randCoord = World.Right(randCoord);
    }
    if(IsEntityType<InanimateT>(World.EntityAt(randCoord))) {
        lastKnownCoord = randCoord;
        World.RemoveEntity(myLoc);
    } else {
        if(not World.IsEmpty(randCoord)) {
            if(isCannibal 
                || not IsEntityType<WhaleT>(World.EntityAt(randCoord))) {
                swallowedAnimals.emplace_back(World.EntityAt(randCoord));
            }   
        }
        World.MoveEntity(myLoc,randCoord);
        hasMoved = true;
    }
    return hasMoved;
}

void WhaleT::Reproduce(const CoordT& newLoc,WorldT& World) {
    auto newWhaley = std::make_shared<WhaleT>(breedCooldown,isCannibal,newLoc,World);
    World.AddEntity(newWhaley,newLoc);
    return;
}
