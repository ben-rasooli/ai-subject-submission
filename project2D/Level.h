#pragma once
#include <iostream>
#include <functional>
#include "Renderer2D.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "Grid.h"
#include "Hero.h"
#include "HeroSFM.h"
#include "FlyingRock.h"
#include "Pathfinder.h"

class Level :
	public GameObject
{
public:
	Level();
	~Level();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

	GameObject* GetSlaveFlyingRock();
	GameObject* GetMasterFlyingRock();

private:
	Grid* _grid;
	GameObject* _wanderingTarget;
	float _randomDestinationPickingInterval;
	float _timer;
	Pathfinder* _pathfinder;
	Hero* _hero;
	FlyingRock* _masterFlyingRock;
	int _slaveRocksCount;
	List<FlyingRock*> _slaveFlyingRocks;

	function <void()> _instanciateRocks;
	function <int()> _getFlyingRocksCount;

	void setWanderingTarget();
};

