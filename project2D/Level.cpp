#include "Level.h"

Level::Level()
{
	Hero* hero = new Hero();
	hero->SetParent(this);

	for (int i = 0; i < 10; i++)
	{
		FlyingRock* flyingRock = new FlyingRock();
		flyingRock->SetParent(this);
	}

	for (int i = 0; i < _childList.Count(); i++)
	{

	}
}

void Level::Update(float deltaTime)
{
	CollisionManager::I()->Update(deltaTime);
	GameObject::Update(deltaTime);
}

void Level::Draw(aie::Renderer2D * renderer)
{
	GameObject::Draw(renderer);
	CollisionManager::I()->Draw(renderer);
}
