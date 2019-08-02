#pragma once
#include "GameObject.h"
#include "HeroSFM.h"
#include "Grid.h"
#include "Path.h"
#include "Pathfinder.h"

class Level;

class Hero 
	: public GameObject
{
public:
	Hero(HeroFSM* FSM, Level* level, Grid* grid);
	~Hero();

	void Update(float deltaTime);
	void OnCollision(GameObject* other);

	void SeekSlaveFlyingRock();
	void SeekMasterFlyingRock();
	void SeekNothing();

private:
	HeroFSM* _FSM;
	Level* _level;
	Grid* _grid;
	Path* _path;
	Pathfinder* _pathfinder;
	GameObject* _target;
};

