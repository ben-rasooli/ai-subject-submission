#pragma once
#include "GameObject.h"
#include "Renderer2D.h"
#include "Font.h"
#include "Level.h"
#include "Hero.h"
#include "Pathfinder.h"

using namespace std;

class IState
{
public:
	virtual void Update() = 0;
	virtual void OnCollision(GameObject* other) = 0;
};

//-----------------------------Idle
class Idle
	: public IState
{
public:
	Idle(HeroFSM* FSM, function <void()>* onSpaceKeyPressed)
	{
		_FSM = FSM;
		_onSpaceKeyPressed = onSpaceKeyPressed;
		_input = aie::Input::GetInstance();
	}

	void Update()
	{
		if (_input->WasKeyReleased(aie::INPUT_KEY_SPACE))
		{
			(*_onSpaceKeyPressed)();
			_FSM->Target = _FSM->Level_->GetSlaveFlyingRock();
			Vector2 pos = _FSM->Target->GetPosition();
			_FSM->ChangeState(1);
		}
	}

	void OnCollision(GameObject* other) {}

private:
	HeroFSM* _FSM;
	function <void()>* _onSpaceKeyPressed;
	aie::Input* _input;
};

//-----------------------------SlaveRockCollecting
class SlaveRockCollecting
	: public  IState
{
public:
	SlaveRockCollecting(HeroFSM* FSM, function <int()>* getFlyingRocksCount)
	{
		_FSM = FSM;
		_getFlyingRocksCount = getFlyingRocksCount;
	}

	void Update()
	{
		_FSM->SetPath();
		_FSM->Hero_->SetPath(_FSM->Path_);
	}

	void OnCollision(GameObject* other)
	{
		if (other->GetType() == "SlaveFlyingRock")
			other->SetActive(false);

		if ((*_getFlyingRocksCount)() == 1)
		{
			_FSM->Target = _FSM->Level_->GetMasterFlyingRock();
			_FSM->ChangeState(2);
		}
		else
			_FSM->Target = _FSM->Level_->GetSlaveFlyingRock();
	}

private:
	HeroFSM* _FSM;
	function <int()>* _getFlyingRocksCount;
};

//-----------------------------MasterRockCollecting
class MasterRockCollecting
	: public  IState
{
public:
	MasterRockCollecting(HeroFSM* FSM, function <int()>* getFlyingRocksCount)
	{
		_FSM = FSM;
		_getFlyingRocksCount = getFlyingRocksCount;
	}

	void Update()
	{
		_FSM->SetPath();
		_FSM->Hero_->SetPath(_FSM->Path_);
	}

	void OnCollision(GameObject* other)
	{
		if (other->GetType() == "MasterFlyingRock")
		{
			other->SetActive(false);
			_FSM->Target = nullptr;
			_FSM->Hero_->SetPath(nullptr);
			_FSM->ChangeState(0);
		}
	}

private:
	HeroFSM* _FSM;
	function <int()>* _getFlyingRocksCount;
};