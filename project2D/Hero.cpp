#include "Hero.h"
#include "Level.h"

Hero::Hero(HeroFSM * FSM, Level* level, Grid* grid)
	: GameObject("hero.png")
{
	_type = "Hero";
	_FSM = FSM;
	_level = level;
	_grid = grid;
	_path = new Path();
	_pathfinder = new Pathfinder(_grid->Nodes());
	_target = nullptr;
}

Hero::~Hero()
{
	delete _FSM;
	delete _path;
	delete _pathfinder;
}

void Hero::Update(float deltaTime)
{
	_FSM->Update();

	if (!_target)
		return;

	_pathfinder->FindPath("1_1", "28_14", _path);
	_grid->ShowPath(_path);
}

void Hero::OnCollision(GameObject * other)
{
	_FSM->OnCollision(other);
}

void Hero::SetSeekingTarget(GameObject * target)
{
	_target = target;
}

