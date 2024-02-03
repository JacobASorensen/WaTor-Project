#pragma once
#include <random>
#include <memory>
#include "WorldT.h"


int RandBetween(int low, int high);

class EntityT {
	public:
	virtual void TakeTurn(CoordT& myLoc,WorldT& World) = 0;
};

template <typename T> 
bool IsEntityType(const std::shared_ptr<EntityT> check) {
    bool isType = false;
    if(T* testVar = dynamic_cast<T*>(check.get()) ) {
        isType = true;
    }
    return isType;
}


class AnimalT: public EntityT {
	public:
	
	protected:
	virtual void Reproduce(const CoordT& newLoc,WorldT& World) = 0;
	virtual bool Move(CoordT& myLoc,WorldT& World);

	std::vector<CoordT> nearbyCoords;
	int sightDistance;
	int breedCooldown;
	bool isReadyToBreed;
	int turnsSinceLastBreed;

};

//moves around randomly
//reproduces every fishBreed turns
class FishT: public AnimalT {
	public:
	//FishT();
	FishT(const int& breedCool);

	void TakeTurn(CoordT& myLoc,WorldT& World) override;

	protected:
	int breedCooldown;
	
	void Reproduce(const CoordT& newLoc,WorldT& World) override;

};

//swallows animals whole. 
//moves randomly; gets beached and dies on rocks
//releases all swallowed animals on death 
class WhaleT : public FishT {
	public:
	WhaleT(const int& breed,const bool& isCanB,const CoordT& newLoc, WorldT& world);
	~WhaleT();
	private:
	std::list<std::shared_ptr<EntityT>> swallowedAnimals;
	bool isCannibal;
	CoordT lastKnownCoord;
	WorldT& lastKnownWorld;
	void Reproduce(const CoordT& newLoc,WorldT& World) override;
	bool Move(CoordT& myLoc,WorldT& World) override;
};

class StarveT: public AnimalT {
	protected:
	int starveTime;
	int turnsSinceLastMeal;
};

//eats fishies. can't eat inanimates (rocks and volcanoes) and whales
//starves if runs out of nutrients.
class SharkT: public StarveT {
	public:
	SharkT();
	SharkT(int& sharkBreed,int& sharkStarve);
	void TakeTurn(CoordT& myLoc,WorldT& World) override;

	protected:
	void Reproduce(const CoordT& newLoc,WorldT& World) override;
	//prioritizes fish, so it won't starve
	bool Move(CoordT& myLoc,WorldT& World) override;
	
};


//likes to stay put near rocks, and feed on the nutrients there
//sends out babies from its location
class BottomFeederT: public StarveT {
	
	public:
	BottomFeederT(int bFB,int bFS);
	void TakeTurn(CoordT& myLoc,WorldT& World) override;
	
	protected:
	void Reproduce(const CoordT& newLoc,WorldT& World) override;
	bool IsNearRock(WorldT& World);
	void Reproduce(WorldT& World);
};

//inanimate entity: mainly for blocking movement for animals
class InanimateT: public EntityT {
};

//has a random chance to erode based off of 2 input values
class RockT: public InanimateT {
	
	public:
	RockT(int& erMin,int& erMax);
	void TakeTurn(CoordT& myLoc,WorldT& World) override;

	private:
	int age;
	int erodeMin;
	int erodeMax;
	bool Erode();
	//
};

//moves like a rook in chess. has an increasing chance to move each turn until it moves
//has an increasing chance to spawn rocks each turn until it does.
//can spawn rocks in different amounts, ranges, and frequencies around it
//approaches doomsday, which fills most of the map with rocks
class VolcanoT: public InanimateT {
	
	public:
	VolcanoT(int& rMin,int& rMax,int& mF,int& sF,int& sM,int& sR,int& ddT);
	void TakeTurn(CoordT& myLoc,WorldT& World) override;

	private:
	int age;
	int rockErodeMin;
	int rockErodeMax;
	int moveFreq;
	int timeSinceLastMove;
	int spewFreq;
	int timeSinceLastSpew;
	int spewMag;
	int spewRange;
	int doomsdayTimer;

	int xMove;
	bool eastMoving;
	int yMove;
	bool northMoving;
	std::vector<CoordT> nearbyCoords;

	void Doomsday(const CoordT& myLoc,WorldT& World);
	void Move(CoordT& myLoc,WorldT& World);
	void XMove(CoordT& myLoc,WorldT& World);
	void YMove(CoordT& myLoc,WorldT& World);

	void SpawnRocks(const CoordT& myLoc,WorldT& World);
	
};