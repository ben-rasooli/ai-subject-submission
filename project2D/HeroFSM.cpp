#include "HeroSFM.h"
#include "HeroStates.h"
#include "GameObject.h"
#include "Hero.h"

HeroFSM::HeroFSM(Hero* hero, function<void()>* onSpaceKeyPressed, function<int()>* getFlyingRocksCount)
{
	_states.PushBack(new Idle(this, onSpaceKeyPressed));
	_states.PushBack(new SlaveRockCollecting(this, getFlyingRocksCount, hero));
	_states.PushBack(new MasterRockCollecting(this, getFlyingRocksCount, hero));

	ChangeState(0);
}

HeroFSM::~HeroFSM()
{
	for (int i = 0; i < _states.Count(); i++)
		delete _states[i];
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
