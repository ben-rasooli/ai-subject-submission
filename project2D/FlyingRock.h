#pragma once
#include "GameObject.h"

using namespace std;

class FlyingRock :
	public GameObject
{
public:
	FlyingRock();
	FlyingRock(float speed);
	void SetSeekingTarget(GameObject* target);

	void Update(float deltaTime);
	//void OnCollision(GameObject* other);

private:
	float _speed;
	Vector2 _velocity;
	GameObject* _target;
};

