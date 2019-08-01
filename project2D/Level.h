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

class Level :
	public GameObject
{
public:
	Level();
	~Level();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

	GameObject* GetASlaveFlyingRock();
	GameObject* GetMasterFlyingRock();

private:
	Grid* _grid;
	GameObject* _wanderingTarget;
	float _wanderingInterval;
	float _timer;
	Hero* _hero;
	FlyingRock* _masterFlyingRock;
	int _slaveRocksCount;
	List<FlyingRock*> _slaveFlyingRocks;

	function <void()> _instanciateRocks;
	function <int()> _getFlyingRocksCount;

	void setWanderingTarget();
};

