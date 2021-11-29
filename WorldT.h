#include <list>
#include <vector>
#include <memory>
#include "Entities.h"

struct CoordT {
	CoordT(int coordx, int coordy);
	int x;
	int y;
};


class WorldT {
	public:

	CoordT Up(CoordT currentLoc);
	CoordT Down(CoordT currentLoc);
	CoordT Left(CoordT currentLoc);
	CoordT Right(CoordT currentLoc);
	
	int WorldWidth();
	int WorldHeight();

	bool IsEmpty(CoordT entityLoc);
	EntityT* EntityAt(CoordT entityLoc);


	std::vector<CoordT> WhatIsNearby(int sight,const CoordT entityLoc);


	private:

	
	int worldWidth;
	int worldHeight;

	std::list<CoordT> existingEntities;

	std::vector<std::vector<std::shared_ptr<EntityT*>>> Map;
};
