


class EntityT {
	public:
	virtual void TakeTurn()const = 0;
};

class AnimalT: public EntityT {
	public:

	private:
	void Reproduce();
	void Move();


	int sightDistance = 1;
	int breedCooldown = 1;
	bool isReadyToBreed = false;
	int turnsSinceLastBreed = 0;

};

class FishT: public AnimalT {
	public:

	void TakeTurn() const override;

};

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
	void TakeTurn() const override;

	private:
	void Move(); //prioritizes fish, so it won't starve
};

class BottomFeederT: public StarveT {
	public:
	void TakeTurn() const override;

	private:
	void Move(); //likes to stay put near rocks
	void Reproduce(); //when at a rock, sends out babies from its stagnant location
};



class InanimateT: public EntityT {
};

class RockT: public InanimateT {
	public:
	void TakeTurn() const override;

	private:
	void Erode();
	void SpawnBottomFeeder();
};

class VolcanoT: public InanimateT {
	public:
	void TakeTurn() const override;

	private:
	//moves in a cardinal direction, maybe can change direction?
	//kills entities in its way
	void Move();
	//spawns between 0 and 4 rocks around it, killing entities present there
	void SpawnRocks();
};

*/