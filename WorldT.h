#include <list>
#include <vector>
#include <memory>
#include "Entities.h"

struct CoordT {
	public:
	CoordT(int coordx, int coordy): x(coordx), y(coordy) {}
	CoordT(const CoordT & Coord): x(Coord.x), y(Coord.y) {}
	
	friend class WorldT;

	private:
	int x;
	int y;
};


class WorldT {
	public:
	WorldT(int wW, int wH);

	bool CoordIsGood(const CoordT & coord);
	CoordT Up(const CoordT currentLoc);
	CoordT Down(const CoordT currentLoc);
	CoordT Left(const CoordT currentLoc);
	CoordT Right(const CoordT currentLoc);
	
	int WorldWidth();
	int WorldHeight();

	bool IsEmpty(CoordT entityLoc);
	void WorldT::WhatIsNearby(const CoordT& entityLoc,int sight,std::vector<CoordT>& nearbyCoords);
	std::shared_ptr<EntityT*> EntityAt(CoordT entityLoc);

	void MoveEntity(CoordT locFrom, CoordT locTo);
	void AddEntity(std::shared_ptr<EntityT*> entityToAdd, CoordT locTo);
	void RemoveEntity(CoordT locTo);

	

	private:

	
	int worldWidth;
	int worldHeight;

	std::list<CoordT> existingEntities;

	std::vector<std::vector<std::shared_ptr<EntityT*>>> Map;
};
