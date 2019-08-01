#pragma once
#include "GameObject.h"
#include "CollisionManager.h"

using namespace std;

class FlyingRock :
	public GameObject
{
public:
	FlyingRock();
	FlyingRock(float speed);
	void SetSeekingTarget(GameObject* target);

	void Update(float deltaTime);

private:
	float _speed;
	Vector2 _velocity;
	GameObject* _target;

	void init();
};

