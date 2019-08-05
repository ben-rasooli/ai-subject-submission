#pragma once
#include "GameObject.h"
#include "HeroSFM.h"
#include "Grid.h"
#include "Path.h"

class Level;

class Hero 
	: public GameObject
{
public:
	Hero(Level* level, Grid* grid);
	~Hero();

	void Update(float deltaTime);
	void OnCollision(GameObject* other);

	void SetFSM(HeroFSM* FSM);
	void SetPath(Path* path);

private:
	HeroFSM* _FSM;
	Level* _level;
	Grid* _grid;
	Path* _path;
	float _moveSpeed;
	float _timer;
};

