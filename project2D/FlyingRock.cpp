#include "FlyingRock.h"

FlyingRock::FlyingRock()
	: GameObject("slave_rock.png")
{
	_speed = rand() % 60 + 30;
	_velocity = Vector2(0, 0);
	_target = nullptr;
}

FlyingRock::FlyingRock(float speed)
	: GameObject("master_rock.png")
{
	_speed = speed;
	_velocity = Vector2(0, 0);
	_target = nullptr;
}

void FlyingRock::SetSeekingTarget(GameObject* target)
{
	_target = target;
}

void FlyingRock::Update(float deltaTime)
{
	if (!_target)
		return;

	Vector2 targetPos = _target->GetPosition();
	Vector2 myPos = GetPosition();

	Vector2 directionToTarget = (targetPos - myPos).normalised();
	Vector2 v = directionToTarget * _speed;
	Vector2 force = v - _velocity;
	_velocity += force * deltaTime;
	Translate(_velocity * deltaTime);
}
