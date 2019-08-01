#pragma once
#include "List.h"
#include "Input.h"
#include <functional>

class IState;
class GameObject;
class Hero;

class HeroFSM
{
public:
	HeroFSM(Hero* hero, function <void()>* onSpaceKeyPressed, function <int()>* getFlyingRocksCount);
	~HeroFSM();

	void Update();
	void OnCollision(GameObject* other);

	void ChangeState(int stateIndex);

private:
	IState* _currentState;
	List<IState*> _states;
	int _collectedRockes;
};