#include "Level.h"

Level::Level()
{
	_grid = new Grid();
	_pathfinder = new Pathfinder(_grid->Nodes());
	_wanderingTarget = new GameObject();
	_wanderingInterval = 2.0f;
	_timer = _wanderingInterval;

	_masterFlyingRock = new FlyingRock(90);
	_masterFlyingRock->SetParent(this);
	_masterFlyingRock->SetPosition(_grid->GetARandomReachablePosition());

	for (int i = 0; i < 10; i++)
	{
		FlyingRock* flyingRock = new FlyingRock();
		flyingRock->SetParent(this);
		flyingRock->SetPosition(_grid->GetARandomReachablePosition());
		flyingRock->SetSeekingTarget(_masterFlyingRock);
		_slaveFlyingRocks.PushBack(flyingRock);
	}
}

Level::~Level()
{
	delete _grid;
	delete _pathfinder;
	delete _wanderingTarget;
}

void Level::Update(float deltaTime)
{
	CollisionManager::I()->Update(deltaTime);
	GameObject::Update(deltaTime);
	UpdateGlobalTransform();

	if (_timer < 0)
	{
		_timer = _wanderingInterval;
		setWanderingTarget();
	}
	else
		_timer -= deltaTime;
}

void Level::Draw(aie::Renderer2D * renderer)
{
	_grid->Draw(renderer);
	GameObject::Draw(renderer);
	CollisionManager::I()->Draw(renderer);
}

void Level::setWanderingTarget()
{
	_wanderingTarget->SetPosition(_grid->GetARandomReachablePosition());
	_grid->ShowWanderingTarget(_wanderingTarget->GetPosition());
	_masterFlyingRock->SetSeekingTarget(_wanderingTarget);
}
