//#pragma once
#include "WorldT.h"
#include <list>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include "Entities.h"
#include <iostream>

bool WorldT::CoordIsGood(const CoordT & coord) {
	return (coord.x < worldWidth && coord.x >= 0) && (coord.y < worldHeight && coord.y >= 0);
}

CoordT WorldT::Up(const CoordT& currentLoc) {
    
    int newY = currentLoc.y - 1;
    if(newY < 0) {
        newY = WorldHeight() - 1;
    }

    CoordT newcoord(currentLoc.x,newY);
    return newcoord;
}

CoordT WorldT::Down(const CoordT& currentLoc) {
    int newY = currentLoc.y + 1;
    if(newY >= WorldHeight()) {
        newY = 0;
    }

    CoordT newcoord(currentLoc.x,newY);
    return newcoord;
}

CoordT WorldT::Left(const CoordT& currentLoc) {
    int newX = currentLoc.x;
    newX--;
    if(newX < 0) {
        newX = WorldWidth() - 1;
    }

    CoordT newcoord(newX,currentLoc.y);
    return newcoord;
}

CoordT WorldT::Right(const CoordT& currentLoc) {
    int newX = currentLoc.x;
    newX++;
    if(newX >= WorldWidth() ) {
        newX = 0;
    }

    CoordT newcoord(newX,currentLoc.y);
    return newcoord;
}

CoordT WorldT::ZeroCoord() {
    return CoordT(0,0);
}

CoordT WorldT::RandomCoord(bool careAboutOccupancy,bool unoccupied) {
    CoordT newCoord(0,0);
    if(careAboutOccupancy) {
		//std::cout << "Care about occupancy..." << std::endl;
        int totalCoords = worldHeight*worldWidth;
        std::vector<CoordT> unoccupiedCoords;
        std::vector<CoordT> occupiedCoords;
        int randIndex = 0;
        for(int i = 0; i < worldWidth; i++) {
            for(int x = 0; x < worldHeight; x++) {
                if(Map[i][x] == nullptr) {
                    unoccupiedCoords.push_back(CoordT(i,x));
                } else {
                    occupiedCoords.push_back(CoordT(i,x));
                }
            }
        }
		//std::cout << "Randing..." << std::endl;
        if(unoccupied && unoccupiedCoords.size() > 0 && (NumOccupiedLocs() < totalCoords) ) {
		    //std::cout << "unoccopied prio..." << std::endl;
            randIndex = RandBetween(0,static_cast<int>(unoccupiedCoords.size()) - 1);
            newCoord = unoccupiedCoords[randIndex];
        } else {
            randIndex = RandBetween(0,static_cast<int>(occupiedCoords.size()) - 1);
            newCoord = occupiedCoords[randIndex];
        }
		//std::cout << "Done..." << std::endl;
    } else {
        std::random_device dev;
        static std::mt19937 generator(dev());
        std::uniform_int_distribution<int> xRand(0,worldWidth - 1);
        std::uniform_int_distribution<int> yRand(0,worldHeight - 1);

        newCoord.x = xRand(generator);
        newCoord.y = yRand(generator);
    }

    return newCoord;
}

int WorldT::WorldWidth() const {
    return worldWidth;
}

int WorldT::WorldHeight() const {
    return worldHeight;
}


bool WorldT::IsEmpty(const CoordT& entityLoc) {
    return Map[entityLoc.x][entityLoc.y] == nullptr;
}

void WorldT::WhatIsNearby(const CoordT& entityLoc,int sight,std::vector<CoordT>& nearbyCoords) {
    
    CoordT currentCoord(entityLoc);
    if(sight >= 1) {
        
        for(int i = 0; i < sight; i++) {
            currentCoord = Up(currentCoord);
            nearbyCoords.emplace_back(currentCoord);

            for(int x = 0; x < i + 1; x++) {
                currentCoord = Right(currentCoord);
                currentCoord = Down(currentCoord);
                nearbyCoords.emplace_back(currentCoord);
            }
            for(int x = 0; x < i + 1; x++) {
                currentCoord = Left(currentCoord);
                currentCoord = Down(currentCoord);
                nearbyCoords.emplace_back(currentCoord);
            }
            for(int x = 0; x < i + 1; x++) {
                currentCoord = Left(currentCoord);
                currentCoord = Up(currentCoord);
                nearbyCoords.emplace_back(currentCoord);
            }
            for(int x = 0; x < i + 1; x++) {
                currentCoord = Right(currentCoord);
                currentCoord = Up(currentCoord);
                nearbyCoords.emplace_back(currentCoord);
            }
            //this was done to prevent the repeated up
            //so that "up" will always be first
            nearbyCoords.pop_back();
        }
    }
}

void WorldT::WhatIsNearbyOcto(const CoordT& entityLoc,int sight,std::vector<CoordT>& nearbyCoords) {
    CoordT currentCoord(entityLoc);
    if(sight >= 1) {
        
        for(int i = 0; i < sight; i++) {
            currentCoord = Up(currentCoord);
            nearbyCoords.emplace_back(currentCoord);

            for(int x = 0; x < i + 1; x++) {
                currentCoord = Right(currentCoord);
                nearbyCoords.emplace_back(currentCoord);
            }
            for(int x = 0; x < 2*(i + 1); x++) {
                currentCoord = Down(currentCoord);
                nearbyCoords.emplace_back(currentCoord);
            }

            for(int x = 0; x < 2*(i + 1); x++) {
                currentCoord = Left(currentCoord);
                nearbyCoords.emplace_back(currentCoord);
            }
            for(int x = 0; x < 2*(i + 1); x++) {
                currentCoord = Up(currentCoord);
                nearbyCoords.emplace_back(currentCoord);
            }
            for(int x = 0; x < i + 1; x++) {
                currentCoord = Right(currentCoord);
                nearbyCoords.emplace_back(currentCoord);
            }
            //this was done to prevent the repeated up
            //and so "up" will always be first
            nearbyCoords.pop_back();
        }
    }
}

std::shared_ptr<EntityT> WorldT::EntityAt(const CoordT& entityLoc) {
    return Map[entityLoc.x][entityLoc.y];
}


void WorldT::MoveEntity(CoordT& locFrom, const CoordT& locTo) {
    if(CoordIsGood(locFrom) && CoordIsGood(locTo)) {
        if(locTo == locFrom) {
        } else {
            Map[locTo.x][locTo.y] = Map[locFrom.x][locFrom.y];
            Map[locFrom.x][locFrom.y] = nullptr;
            locFrom = locTo;
        }
    }
    return;
}

void WorldT::AddEntity(std::shared_ptr<EntityT> entityToAdd, const CoordT& locTo) {
    if(CoordIsGood(locTo)) {
        Map[locTo.x][locTo.y] = entityToAdd;
    }
    return;
}

void WorldT::RemoveEntity(const CoordT& locTo) {
    if(CoordIsGood(locTo)) {
        //we wait to delete the postions until the end of the tick
        Map[locTo.x][locTo.y] = nullptr;
    }
    return;
}

int WorldT::WorldAge() const{
    return worldAge;
}

bool WorldT::EntityExists(std::shared_ptr<EntityT> entity) {
    bool entityExists = false;
    for(int x = 0; x < worldWidth; x++) {
        for(int i = 0; i < worldHeight; i++) {
            if(Map[x][i] == entity) {
                entityExists = true;
            }
        }
    }
    return entityExists;
}

CoordT WorldT::FindEntity(std::shared_ptr<EntityT> entity) {
    for(int x = 0; x < worldWidth; x++) {
        for(int i = 0; i < worldHeight; i++) {
            if(Map[x][i] == entity) {
                return CoordT(x,i);
            }
        }
    }
    return CoordT(-1,-1);
}

void WorldT::Tick() {
    /*
    -iterate through map and add entities to validForTurn vector
    -iterate through validForTurn vector randomly, until the number
    of taken turns is equal to the vector size
            if(not hasTakenTurn) {
                Look at the entityLoc to see if its the same as entity
                if not, look for the entity in the Map
                if it doesn't exist there, then hasTakenTurn = true
                    takenTurns++;
                if it does then call TakeTurn() and then hasTakenTurn = true
                    takenTurns++;
            }

    */
   worldAge++;
   std::list<turnInfo> existingEntities;
    for(int x = 0; x < worldWidth; x++) {
        for(int i = 0; i < worldHeight; i++) {
            if(Map[x][i] != nullptr) {
                turnInfo newEntity(CoordT(x,i),Map[x][i]);
                existingEntities.push_back(newEntity);
            }
        }
    }

    std::list<turnInfo>::iterator ptr;
    int numTurnsTaken = 0;
    int i = 0;
    int n = 0;
    while(existingEntities.size() > 0) {
        //we want the order the entities to take their turn to be
        //random, but we also dont want to guess forever
        i = RandBetween(0,static_cast<int>(existingEntities.size()) - 1);
        ptr = existingEntities.begin();
        for(n = 0; n < i; n++) {
            ptr++;
        }

        //check to see if the entity is still at that coordinate
        //if it isn't, try to find it
        if(EntityAt(ptr->entityLoc) != ptr->entity) {
            ptr->entityLoc = FindEntity(ptr->entity);
        }
        //if the entity doesn't exist, the coord won't be any good
        if(CoordIsGood(ptr->entityLoc)) {
            ptr->entity->TakeTurn(ptr->entityLoc,*this);
        }
        existingEntities.erase(ptr);
        numTurnsTaken++;
    }
    return;
}

int WorldT::NumOccupiedLocs() const {
    int numEntities = 0;
    for(int x = 0; x < worldWidth; x++) {
        for(int i = 0; i < worldHeight; i++) {
            if(Map[x][i] != nullptr) {
                numEntities++;
            }
        }
    }
    return numEntities;
}

WorldT::WorldT(int wW, int wH): worldWidth(wW), worldHeight(wH) {
     worldAge = 0;
    if(worldWidth <= 0) {
        worldWidth = 1;
    }
    if(worldHeight <= 0) {
        worldHeight = 1;
    }
    
    Map.resize(worldWidth);
    for(int i = 0; i < worldWidth; i++) {
        Map[i].resize(worldHeight);
    }
    return;
}

