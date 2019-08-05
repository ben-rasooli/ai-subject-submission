#include "Hero.h"
#include "Level.h"
#include <iostream>

Hero::Hero(Level* level, Grid* grid)
	: GameObject("hero.png")
{
	_type = "Hero";
	_level = level;
	_grid = grid;
	_path = nullptr;
	_moveSpeed = 0.1f;
	_timer = 0.0f;
	_collider = new Collider(Vector2(10, 10));
	CollisionManager::I()->AddGameObject(this, CollisionLayer::HERO);
}

Hero::~Hero()
{
	delete _FSM;
}

void Hero::Update(float deltaTime)
{
	_FSM->Update();


		if (_path)
		{
			_grid->ShowPath(_path);

			// move hero toward target
			if (_path->Corners.Count() >= 2)
				if (_timer <= 0)
				{
 					_timer = _moveSpeed;
					Vector2 position = _grid->GetPositionOnScreen(_path->Corners[1]);
					SetPosition(position);
				}
		}

		_timer -= deltaTime;
}

void Hero::OnCollision(GameObject * other)
{
	cout << other->GetType() << endl;
	_FSM->OnCollision(other);
}

void Hero::SetFSM(HeroFSM * FSM)
{
	_FSM = FSM;
}

void Hero::SetPath(Path* path)
{
	_path = path;
}


