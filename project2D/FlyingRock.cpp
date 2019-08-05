#include "FlyingRock.h"

FlyingRock::FlyingRock()
	: GameObject("slave_rock.png")
{
	_type = "SlaveFlyingRock";
	_speed = rand() % 60 + 30;
	init();
}

FlyingRock::FlyingRock(float speed)
	: GameObject("master_rock.png")
{
	_type = "MasterFlyingRock";
	_speed = speed;
	init();
}

void FlyingRock::init()
{
	_state = FlyingRockState::Seek;
	_velocity = Vector2(0, 0);
	_target = nullptr;
	_timer = 3.0f;
	_collider = new Collider(Vector2(10, 10));
	CollisionManager::I()->AddGameObject(this, CollisionLayer::FLYING_ROCK);
}

void FlyingRock::SetSeekingTarget(GameObject* target)
{
	_target = target;
}

void FlyingRock::Update(float deltaTime)
{
	if (_type == "SlaveFlyingRock")
	{
		if (_timer <= 0)
		{
			if (_state == FlyingRockState::Seek)
			{
				_state = FlyingRockState::Flee;
				_timer = 1.5f;
			}
			else
			{
				_state = FlyingRockState::Seek;
				_timer = 3.5f;
			}
		}
		else
			_timer -= deltaTime;
	}

	if (!_target)
		return;

	if (!_isActive)
		_velocity = Vector2(0, 0);

	Vector2 targetPosition = _target->GetPosition();
	Vector2 originPosition = GetPosition();

	switch (_state)
	{
	case Seek:
		targetPosition = _target->GetPosition();
		originPosition = GetPosition();
		break;
	case Flee:
		targetPosition = GetPosition();
		originPosition = _target->GetPosition();
		break;
	}

	Vector2 directionToTarget = (targetPosition - originPosition).normalised();
	Vector2 v = directionToTarget * _speed;
	Vector2 force = v - _velocity;
	_velocity += force * deltaTime;
	Translate(_velocity * deltaTime);
}
