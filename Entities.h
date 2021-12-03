#pragma once
#include <random>
#include <memory>
#include "WorldT.h"


int RandBetween(int low, int high);

class EntityT {
	public:
	virtual void TakeTurn(const CoordT& myLoc,WorldT& World) = 0;
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
	virtual bool Move(const CoordT& myLoc,WorldT& World);

	std::vector<CoordT> nearbyCoords;
	int sightDistance;
	int breedCooldown;
	bool isReadyToBreed;
	int turnsSinceLastBreed;

};

class FishT: public AnimalT {
	public:
	//FishT();
	FishT(const int& breedCool);

	void TakeTurn(const CoordT& myLoc,WorldT& World) override;

	protected:
	
	void Reproduce(const CoordT& newLoc,WorldT& World) override;

};

/*
maybe add a whale that will hold fish/sharks in its mouth until it
moves onto a rock and becomes beached and dies, and then it releases
all of its held animals

*/

class StarveT: public AnimalT {
	protected:
	int starveTime;
	int turnsSinceLastMeal;
};

class SharkT: public StarveT {
	public:
	SharkT();
	SharkT(int& sharkBreed,int& sharkStarve);
	void TakeTurn(const CoordT& myLoc,WorldT& World) override;

	protected:
	void Reproduce(const CoordT& newLoc,WorldT& World) override;
	//prioritizes fish, so it won't starve
	bool Move(const CoordT& myLoc,WorldT& World) override;
	
};

/*
class BottomFeederT: public StarveT {
	public:
	void TakeTurn(CoordT myLoc) const override;

	private:
	void Move(); //likes to stay put near rocks
	void Reproduce(); //when at a rock, sends out babies from its stagnant location
};


*/
class InanimateT: public EntityT {
};
/*

class RockT: public InanimateT {
	public:
	void TakeTurn(CoordT myLoc) const override;

	private:
	void Erode();
	void SpawnBottomFeeder();
};

class VolcanoT: public InanimateT {
	public:
	void TakeTurn(CoordT myLoc) const override;

	private:
	//random chance to extinction event event
	//moves in a cardinal direction, maybe can change direction?
	//kills entities in its way
	void Move();
	//spawns between 0 and 4 rocks around it, killing entities present there
	void SpawnRocks();
};

*/