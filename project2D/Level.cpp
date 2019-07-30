#include "Level.h"

Level::Level()
{
	_grid = new Grid();
	std::cout << _grid->ToString();

	_pathfinder = new Pathfinder(_grid->Nodes());

	Path* path = _pathfinder->FindPath("1_1", "8_8");
	_grid->ShowPath(path);
	

	Hero* _hero = new Hero();
	_hero->SetParent(this);

	for (int i = 0; i < 10; i++)
	{
		FlyingRock* flyingRock = new FlyingRock();
		flyingRock->SetParent(this);
	}
}

Level::~Level()
{
	delete _grid;
	delete _pathfinder;
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
	_grid->Draw(renderer);
}
