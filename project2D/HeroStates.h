#pragma once
#include "GameObject.h"
#include "Renderer2D.h"
#include "Font.h"
#include "Hero.h"

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
	SlaveRockCollecting(HeroFSM* FSM, function <int()>* getFlyingRocksCount, Hero* hero)
	{
		_FSM = FSM;
		_getFlyingRocksCount = getFlyingRocksCount;
		_hero = hero;
	}

	void Update() {}

	void OnCollision(GameObject* other)
	{
		if (other->GetType() == "SlaveFlyingRock")
			other->SetActive(false);

		if ((*_getFlyingRocksCount)() == 1)
		{
			_hero->SeekMasterFlyingRock();
			_FSM->ChangeState(2);
		}
		else
			_hero->SeekSlaveFlyingRock();
	}

private:
	HeroFSM* _FSM;
	function <int()>* _getFlyingRocksCount;
	Hero* _hero;
};

//-----------------------------MasterRockCollecting
class MasterRockCollecting
	: public  IState
{
public:
	MasterRockCollecting(HeroFSM* FSM, function <int()>* getFlyingRocksCount, Hero* hero)
	{
		_FSM = FSM;
		_getFlyingRocksCount = getFlyingRocksCount;
		_hero = hero;
	}

	void Update() {}

	void OnCollision(GameObject* other)
	{
		if (other->GetType() == "MasterFlyingRock")
		{
			other->SetActive(false);
			_hero->SeekNothing();
			_FSM->ChangeState(0);
		}
	}

private:
	HeroFSM* _FSM;
	function <int()>* _getFlyingRocksCount;
	Hero* _hero;
};