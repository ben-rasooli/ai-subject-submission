#pragma once
#include "GameObject.h"
#include "CollisionManager.h"

using namespace std;

enum FlyingRockState
{
	Seek,
	Flee
};

class FlyingRock :
	public GameObject
{
public:
	FlyingRock();
	FlyingRock(float speed);
	void SetSeekingTarget(GameObject* target);

	void Update(float deltaTime);

private:
	FlyingRockState _state;
	float _speed;
	Vector2 _velocity;
	GameObject* _target;
	float _timer;

	void init();
};

