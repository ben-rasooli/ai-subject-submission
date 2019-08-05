#include "Level.h"

Level::Level()
{
	_grid = new Grid();
	_wanderingTarget = new GameObject();
	_randomDestinationPickingInterval = 2.0f;
	_timer = _randomDestinationPickingInterval;
	_slaveRocksCount = 6;

	_instanciateRocks = [=]() {
		_masterFlyingRock->SetPosition(_grid->GetARandomReachablePosition());
		_masterFlyingRock->SetActive(true);

		for (int i = 0; i < _slaveFlyingRocks.Count(); i++)
		{
			_slaveFlyingRocks[i]->SetPosition(_grid->GetARandomReachablePosition());
			_slaveFlyingRocks[i]->SetActive(true);
		}
	};

	_getFlyingRocksCount = [=]() {
		int result = 0;

		for (int i = 0; i < _slaveFlyingRocks.Count(); i++)
			if (_slaveFlyingRocks[i]->GetActive())
				result++;

		if (_masterFlyingRock->GetActive())
			result++;

		return result;
	};

	Hero* _hero = new Hero(this, _grid);
	_hero->SetParent(this);
	_hero->SetPosition(_grid->GetARandomReachablePosition());

	_pathfinder = new Pathfinder(_grid->Nodes());
	HeroFSM* heroFSM = new HeroFSM(this, _hero, _grid, _pathfinder, &_instanciateRocks, &_getFlyingRocksCount);
	_hero->SetFSM(heroFSM);

	_masterFlyingRock = new FlyingRock(90);
	_masterFlyingRock->SetParent(this);
	_masterFlyingRock->SetPosition(_grid->GetARandomReachablePosition());
	_masterFlyingRock->SetActive(false);

	for (int i = 0; i < _slaveRocksCount; i++)
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
	delete _wanderingTarget;
	delete _pathfinder;
}

void Level::Update(float deltaTime)
{
	UpdateGlobalTransform();
	GameObject::Update(deltaTime);
	CollisionManager::I()->Update(deltaTime);

	if (_timer < 0)
	{
		_timer = _randomDestinationPickingInterval;
		setWanderingTarget();
	}
	else
		_timer -= deltaTime;
}

void Level::Draw(aie::Renderer2D * renderer)
{
	_grid->Draw(renderer);
	GameObject::Draw(renderer);
}

GameObject * Level::GetSlaveFlyingRock()
{
	for (int i = 0; i < _slaveFlyingRocks.Count(); i++)
		if (_slaveFlyingRocks[i]->GetActive())
			return _slaveFlyingRocks[i];

	return nullptr;
}

GameObject * Level::GetMasterFlyingRock()
{
	return _masterFlyingRock;
}

void Level::setWanderingTarget()
{
	_wanderingTarget->SetPosition(_grid->GetARandomReachablePosition());
	_grid->ShowWanderingTarget(_wanderingTarget->GetPosition());
	_masterFlyingRock->SetSeekingTarget(_wanderingTarget);
}
