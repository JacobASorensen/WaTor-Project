

#pragma once
//bool EntitiesAreSameClass(EntityT* ent1, EntityT* ent2);
int RandBetween(int low, int high);


class EntityT {
	public:
	virtual void TakeTurn(const CoordT& myLoc,WorldT& World) = 0;
};

template <typename T> 
bool IsEntityType(const std::shared_ptr<EntityT> check);

class AnimalT: public EntityT {
	public:
	
	protected:
	virtual void Reproduce(const CoordT& newLoc,WorldT& World) = 0;
	virtual bool Move(const CoordT& myLoc,WorldT& World);

	std::vector<CoordT> nearbyCoords;
	int sightDistance{0};
	int breedCooldown{0};
	bool isReadyToBreed{false};
	int turnsSinceLastBreed{0};

};

class FishT: public AnimalT {
	public:
	FishT(int& breedCool);

	void TakeTurn(const CoordT& myLoc,WorldT& World) override;

	protected:
	
	void Reproduce(const CoordT& newLoc,WorldT& World) override;

};

/*
maybe add a whale that will hold fish/sharks in its mouth until it
moves onto a rock and becomes beached and dies, and then it releases
all of its held animals

*/


//focus on getting the fish to work
/*
class SonarFishT: public FishT {


};

class StarveT: public AnimalT {
	private:
	int starveTime = 2;
	int turnsSinceLastMeal = 0;
	virtual void Starve();
};

class SharkT: public StarveT {
	public:
	void TakeTurn(CoordT myLoc) const override;

	private:
	void Move(); //prioritizes fish, so it won't starve
};

class BottomFeederT: public StarveT {
	public:
	void TakeTurn(CoordT myLoc) const override;

	private:
	void Move(); //likes to stay put near rocks
	void Reproduce(); //when at a rock, sends out babies from its stagnant location
};



class InanimateT: public EntityT {
};

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
	//moves in a cardinal direction, maybe can change direction?
	//kills entities in its way
	void Move();
	//spawns between 0 and 4 rocks around it, killing entities present there
	void SpawnRocks();
};

*/