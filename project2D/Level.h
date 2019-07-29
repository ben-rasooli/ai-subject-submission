#pragma once
#include "Renderer2D.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "Hero.h"
#include "FlyingRock.h"

class Level :
	public GameObject
{
public:
	Level();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

private:
};

