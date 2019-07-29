#pragma once
#include "List.h"
#include "GameObject.h"

enum CollisionLayer
{
	HERO,
	FLYING_ROCK
};

struct ColliderSet
{
	CollisionLayer Layer;
	List<CollisionLayer> CollidableLayers;
	List<GameObject*> ColliderOwners;
};