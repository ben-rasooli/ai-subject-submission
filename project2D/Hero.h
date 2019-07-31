#pragma once
#include "GameObject.h"

class Level;
class HeroFSM;

class Hero 
	: public GameObject
{
public:
	Hero(HeroFSM* FSM);

	void Update(float deltaTime);

private:
	HeroFSM* _FSM;
};

