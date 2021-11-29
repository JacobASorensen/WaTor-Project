#include "WorldT.h"

bool WorldT::CoordIsGood(const CoordT & coord) {
	return (coord.x < worldWidth && coord.x >= 0) && (coord.y < worldHeight && coord.y >= 0);
}

CoordT WorldT::Up(const CoordT currentLoc) {
    int newY = currentLoc.y;
    newY--;
    if(newY < 0) {
        newY = WorldHeight() - 1;
    }

    CoordT newcoord(currentLoc.x,newY);
    return newcoord;
}

CoordT WorldT::Down(const CoordT currentLoc) {
    int newY = currentLoc.y;
    newY++;
    if(newY >= WorldHeight()) {
        newY = 0;
    }

    CoordT newcoord(currentLoc.x,newY);
    return newcoord;
}

CoordT WorldT::Left(const CoordT currentLoc) {
    int newX = currentLoc.x;
    newX--;
    if(newX < 0) {
        newX = WorldWidth() - 1;
    }

    CoordT newcoord(newX,currentLoc.y);
    return newcoord;
}

CoordT WorldT::Right(const CoordT currentLoc) {
    int newX = currentLoc.x;
    newX++;
    if(newX >= WorldWidth() ) {
        newX = 0;
    }

    CoordT newcoord(newX,currentLoc.y);
    return newcoord;
}


int WorldT::WorldWidth() {
    return worldWidth;
}

int WorldT::WorldHeight() {
    return worldHeight;
}


bool WorldT::IsEmpty(CoordT entityLoc) {
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
            //and so "up" will always be first
            nearbyCoords.pop_back();
        }
    }
}

std::shared_ptr<EntityT*> WorldT::EntityAt(CoordT entityLoc) {
    return Map[entityLoc.x][entityLoc.y];
}




void WorldT::MoveEntity(CoordT locFrom, CoordT locTo) {
    if(CoordIsGood(locFrom)) {


    }

}

WorldT::WorldT(int wW, int wH): worldWidth(wW), worldHeight(wH) {

}
