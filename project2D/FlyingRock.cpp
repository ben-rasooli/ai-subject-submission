#include "FlyingRock.h"

FlyingRock::FlyingRock()
	: GameObject("slave_rock.png")
{
	_speed = rand() % 60 + 30;
	init();
}

FlyingRock::FlyingRock(float speed)
	: GameObject("master_rock.png")
{
	_speed = speed;
	init();
}

void FlyingRock::init()
{
	_velocity = Vector2(0, 0);
	_target = nullptr;
	_collider = new Collider(Vector2(10, 10));
	CollisionManager::I()->AddGameObject(this, CollisionLayer::FLYING_ROCK);

}

void FlyingRock::SetSeekingTarget(GameObject* target)
{
	_target = target;
}

void FlyingRock::Update(float deltaTime)
{
	if (!_target)
		return;

	if (!_isActive)
		_velocity = Vector2(0, 0);

	Vector2 targetPos = _target->GetPosition();
	Vector2 myPos = GetPosition();

	Vector2 directionToTarget = (targetPos - myPos).normalised();
	Vector2 v = directionToTarget * _speed;
	Vector2 force = v - _velocity;
	_velocity += force * deltaTime;
	Translate(_velocity * deltaTime);
}
