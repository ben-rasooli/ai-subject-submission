#pragma once
#include "List.h"
#include "Level.h"
#include "Input.h"

class IState
{
public:
	virtual void Update() = 0;
};

class HeroFSM;

//-----------------------------Idle
class Idle
	: public IState
{
public:
	Idle(HeroFSM* FSM, const function <void()> onSpaceKeyPressed)
	{
		_FSM = FSM;
		_onSpaceKeyPressed = onSpaceKeyPressed;
		_input = aie::Input::GetInstance();
	}

	void Update()
	{
		if (_input->WasKeyReleased(aie::INPUT_KEY_SPACE))
			_onSpaceKeyPressed();
	}

private:
	HeroFSM* _FSM;
	const function <void()> _onSpaceKeyPressed;
	aie::Input* _input;
};

//-----------------------------SlaveRockCollecting
class SlaveRockCollecting
	: public  IState
{
public:
	SlaveRockCollecting(HeroFSM* FSM)
	{
		_FSM = FSM;
	}

	void Update()
	{

	}

private:
	HeroFSM* _FSM;
};

//-----------------------------MasterRockCollecting
class MasterRockCollecting
	: public  IState
{
public:
	MasterRockCollecting(HeroFSM* FSM)
	{
		_FSM = FSM;
	}

	void Update()
	{

	}

private:
	HeroFSM* _FSM;
};

//-----------------------------HeroFSM
class HeroFSM
{
public:
	HeroFSM(const function <void()> onSpaceKeyPressed)
	{
		_states.PushBack(new Idle(this));
		_states.PushBack(new SlaveRockCollecting(this));
		_states.PushBack(new MasterRockCollecting(this));

		ChangeState(0);
	}

	~HeroFSM()
	{
		for (int i = 0; i < _states.Count(); i++)
			delete _states[i];
	}

	void ChangeState(int stateIndex)
	{
		_currentState = _states[stateIndex];
	}

private:
	IState* _currentState;
	List<IState*> _states;
	int _collectedRockes;
};