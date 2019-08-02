#include "Level.h"

Level::Level()
{
	_grid = new Grid();
	_wanderingTarget = new GameObject();
	_wanderingInterval = 2.0f;
	_timer = _wanderingInterval;
	_slaveRocksCount = 4;

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
	

	HeroFSM* heroFSM = new HeroFSM(_hero, &_instanciateRocks, &_getFlyingRocksCount);

	Hero* _hero = new Hero(heroFSM, this, _grid);
	_hero->SetParent(this);
	_hero->SetPosition(_grid->GetARandomReachablePosition());

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
