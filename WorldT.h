#pragma once
#include <list>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>

class EntityT;

struct CoordT {
	public:
	bool operator==(const CoordT& E) const {return (x == E.x && y == E.y);}
	CoordT(const CoordT & Coord): x(Coord.x), y(Coord.y) {}
	
	int X() {return x;}
	int Y() {return y;}

	friend class WorldT;

	private:
	CoordT(): x(0), y(0) {}
	CoordT(int coordx, int coordy): x(coordx), y(coordy) {}
	int x;
	int y;
};

struct turnInfo{
	turnInfo(CoordT eL,std::shared_ptr<EntityT> eY): entityLoc(eL), entity(eY) {}
	CoordT entityLoc;
	std::shared_ptr<EntityT> entity;
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

	CoordT RandomCoord(bool careAboutOccupancy = true,bool unoccupied = true);

	int WorldWidth() const;
	int WorldHeight() const;

	bool IsEmpty(const CoordT& entityLoc);
	void WhatIsNearby(const CoordT& entityLoc,int sight,std::vector<CoordT>& nearbyCoords);
	void WhatIsNearbyOcto(const CoordT& entityLoc,int sight,std::vector<CoordT>& nearbyCoords);
	std::shared_ptr<EntityT> EntityAt(const CoordT& entityLoc);
	bool EntityExists(std::shared_ptr<EntityT> entity);
	CoordT FindEntity(std::shared_ptr<EntityT> entity);
	int NumOccupiedLocs() const;

	void MoveEntity(const CoordT& locFrom, const CoordT& locTo);
	void AddEntity(std::shared_ptr<EntityT> entityToAdd, const CoordT& locTo);
	void RemoveEntity(const CoordT& locTo);
	int WorldAge() const;

	void Tick();

	private:


	int worldAge;
	int worldWidth;
	int worldHeight;

	std::vector<std::vector<std::shared_ptr<EntityT>>> Map;
};
