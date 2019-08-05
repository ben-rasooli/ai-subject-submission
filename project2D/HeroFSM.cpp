#include "HeroSFM.h"
#include "HeroStates.h"
#include "GameObject.h"
#include "Level.h"
#include "Hero.h"

HeroFSM::HeroFSM(Level * level, 
	Hero* hero,
	Grid* grid,
	Pathfinder* pathfinder,
	function<void()>* onSpaceKeyPressed, 
	function<int()>* getFlyingRocksCount)
{
	Level_ = level;
	Hero_ = hero;
	Grid_ = grid;
	Pathfinder_ = pathfinder;
	Path_ = new Path();
	_states.PushBack(new Idle(this, onSpaceKeyPressed));
	_states.PushBack(new SlaveRockCollecting(this, getFlyingRocksCount));
	_states.PushBack(new MasterRockCollecting(this, getFlyingRocksCount));

	ChangeState(0);
}

HeroFSM::~HeroFSM()
{
	for (int i = 0; i < _states.Count(); i++)
		delete _states[i];

	delete Path_;
}

void HeroFSM::Update()
{
	_currentState->Update();
}

void HeroFSM::OnCollision(GameObject * other)
{
	_currentState->OnCollision(other);
}

void HeroFSM::ChangeState(int stateIndex)
{
	_currentState = _states[stateIndex];
}

void HeroFSM::SetPath()
{
	Vector2 heroPosition = Hero_->GetPosition();
	Vector2 targetPosition = Target->GetPosition();

	string heroPositionOnGrid = Grid_->GetCellID(heroPosition);
	string targetPositionOnGrid = Grid_->GetCellID(targetPosition);

	Pathfinder_->FindPath(heroPositionOnGrid, targetPositionOnGrid, Path_);
}
