#pragma once
#include "Renderer2D.h"
#include "GameObject.h"
#include "ColliderSet.h"

class CollisionManager
{
public:
	~CollisionManager();

	static CollisionManager* I();

	void Update(float deltaTime);

	void AddGameObject(GameObject* gameObject, CollisionLayer layer);

private:
	CollisionManager();
	static CollisionManager* _inst;
	List<ColliderSet*> _colliderSets;
};

