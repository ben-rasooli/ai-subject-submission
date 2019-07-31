#include "Hero.h"

Hero::Hero(HeroFSM * FSM)
	: GameObject("hero.png")
{
	_FSM = FSM;
}

void Hero::Update(float deltaTime)
{
}

