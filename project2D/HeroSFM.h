#pragma once
#include "List.h"
#include "Input.h"
#include <functional>
#include "Grid.h"
#include "Pathfinder.h"
#include "Path.h"

class IState;
class GameObject;
class Level;
class Hero;

class HeroFSM
{
public:
	HeroFSM(Level* level,
		Hero* hero,
		Grid* grid,
		Pathfinder* pathfinder,
		function<void()>* onSpaceKeyPressed,
		function<int()>* getFlyingRocksCount);
	~HeroFSM();

	void Update();
	void OnCollision(GameObject* other);

	void ChangeState(int stateIndex);
	void SetPath();

	GameObject* Target;
	Level* Level_;
	Hero* Hero_;
	Grid* Grid_;
	Pathfinder* Pathfinder_;
	Path* Path_;

private:
	IState* _currentState;
	List<IState*> _states;
	int _collectedRockes;
};