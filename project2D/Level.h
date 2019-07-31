#pragma once
#include <iostream>
#include "Renderer2D.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "Grid.h"
#include "Path.h"
#include "Pathfinder.h"
#include "Hero.h"
#include "FlyingRock.h"

class Level :
	public GameObject
{
public:
	Level();
	~Level();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

	int FlyingRocksCount = 3;
	void InstanciateRocks();

private:
	Grid* _grid;
	Pathfinder* _pathfinder;
	GameObject* _wanderingTarget;
	float _wanderingInterval;
	float _timer;
	Hero* _hero;
	FlyingRock* _masterFlyingRock;
	List<FlyingRock*> _slaveFlyingRocks;

	void setWanderingTarget();
};

