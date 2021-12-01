#include <list>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
//#include <ctime>
#include "Entities.h"

#pragma once

struct CoordT {
	public:
	bool operator==(const CoordT& E) {
		return (x == E.x && y == E.y);
	}
	CoordT(const CoordT & Coord): x(Coord.x), y(Coord.y) {}
	
	friend class WorldT;

	private:
	CoordT(int coordx, int coordy): x(coordx), y(coordy) {}
	int x;
	int y;
};


class WorldT {
	public:
	WorldT(int wW, int wH);

	bool CoordIsGood(const CoordT & coord);
	CoordT Up(const CoordT& currentLoc);
	CoordT Down(const CoordT& currentLoc);
	CoordT Left(const CoordT& currentLoc);
	CoordT Right(const CoordT& currentLoc);
	CoordT ZeroCoord();

	CoordT RandomCoord(bool unoccupied = true);

	int WorldWidth() const;
	int WorldHeight() const;

	bool IsEmpty(const CoordT& entityLoc);
	void WorldT::WhatIsNearby(const CoordT& entityLoc,int sight,std::vector<CoordT>& nearbyCoords);
	void WorldT::WhatIsNearbyOcto(const CoordT& entityLoc,int sight,std::vector<CoordT>& nearbyCoords);
	std::shared_ptr<EntityT> EntityAt(const CoordT& entityLoc);

	void MoveEntity(const CoordT& locFrom, const CoordT& locTo);
	void AddEntity(std::shared_ptr<EntityT> entityToAdd, const CoordT& locTo);
	void RemoveEntity(const CoordT& locTo);

	void Tick();

	private:

	
	int worldWidth;
	int worldHeight;

	std::vector<std::list<CoordT>::iterator> positionsToDelete;

	std::list<CoordT> existingEntities;

	std::vector<std::vector<std::shared_ptr<EntityT>>> Map;
};
