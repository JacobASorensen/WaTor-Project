#include "WorldT.h"

CoordT::CoordT(int coordx, int coordy) {
    x = coordx;
    y = coordy;
}

CoordT WorldT::Up(CoordT currentLoc) {
    int newY = currentLoc.y;
    newY--;
    if(newY < 0) {
        newY = WorldHeight() + newY;
    }

    CoordT newcoord(currentLoc.x,newY);
    return newcoord;
}