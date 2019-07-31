#include "Level.h"

Level::Level()
{
	_grid = new Grid();
	_pathfinder = new Pathfinder(_grid->Nodes());
	_wanderingTarget = new GameObject();
	_wanderingInterval = 2.0f;
	_timer = _wanderingInterval;
	//Path* path = _pathfinder->FindPath("1_1", "28_14");
	//_grid->ShowPath(path);

	Hero* _hero = new Hero(this);
	_hero->SetParent(this);

	_masterFlyingRock = new FlyingRock(90);
	_masterFlyingRock->SetParent(this);
	_masterFlyingRock->SetPosition(_grid->GetARandomReachablePosition());

	for (int i = 0; i < FlyingRocksCount; i++)
	{
		FlyingRock* flyingRock = new FlyingRock();
		flyingRock->SetParent(this);
		flyingRock->SetSeekingTarget(_masterFlyingRock);
		flyingRock->SetPosition(_grid->GetARandomReachablePosition());
		flyingRock->SetActive(false);
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

void Level::InstanciateRocks()
{
	_masterFlyingRock->SetPosition(_grid->GetARandomReachablePosition());
	
	for (int i = 0; i < _slaveFlyingRocks.Count(); i++)
		_slaveFlyingRocks[i]->SetPosition(_grid->GetARandomReachablePosition());
}

void Level::setWanderingTarget()
{
	_wanderingTarget->SetPosition(_grid->GetARandomReachablePosition());
	_grid->ShowWanderingTarget(_wanderingTarget->GetPosition());
	_masterFlyingRock->SetSeekingTarget(_wanderingTarget);
}
