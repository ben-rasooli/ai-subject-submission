#include "CollisionManager.h"

CollisionManager* CollisionManager::_inst = nullptr;

CollisionManager::CollisionManager()
{
	ColliderSet* colSet_hero = new ColliderSet();
	colSet_hero->Layer = CollisionLayer::HERO;
	_colliderSets.PushBack(colSet_hero);

	ColliderSet* colSet_flyingRock = new ColliderSet();
	colSet_flyingRock->Layer = CollisionLayer::FLYING_ROCK;
	colSet_flyingRock->CollidableLayers.PushBack(CollisionLayer::HERO);
	_colliderSets.PushBack(colSet_flyingRock);
}


CollisionManager::~CollisionManager()
{
	for (int i = 0; i < _colliderSets.Count(); i++)
		delete _colliderSets[i];

	delete _inst;
}

CollisionManager * CollisionManager::I()
{
	if (!_inst)
		_inst = new CollisionManager();
	return _inst;
}

void CollisionManager::Update(float deltaTime)
{
	// for each collider set
	for (int i = 0; i < _colliderSets.Count(); i++)
	{
		// go through each of its collidable layers and for each target collision layer
		for (int ii = 0; ii < _colliderSets[i]->CollidableLayers.Count(); ii++)
		{
			// find all the collider ownsers in that layer
			for (int iii = 0; iii < _colliderSets.Count(); iii++)
				if (_colliderSets[iii]->Layer == _colliderSets[i]->CollidableLayers[ii])
				{
					// then compare the list of two collider owners for possible collision
					for (int iiii = 0; iiii < _colliderSets[i]->ColliderOwners.Count(); iiii++)
						for (int iiiii = 0; iiiii < _colliderSets[iii]->ColliderOwners.Count(); iiiii++)
						{
							GameObject* targetColliderOwner = _colliderSets[iii]->ColliderOwners[iiiii];
							auto firstCollider = _colliderSets[i]->ColliderOwners[iiii]->GetCollider();
							auto secondCollider = targetColliderOwner->GetCollider();
							if (firstCollider->IsCollidingWith(secondCollider))
								targetColliderOwner->OnCollision(_colliderSets[i]->ColliderOwners[iiii]);
						}
				}
		}
	}
}

void CollisionManager::AddGameObject(GameObject * gameObject, CollisionLayer layer)
{
	for (int i = 0; i < _colliderSets.Count(); i++)
		if (_colliderSets[i]->Layer == layer)
			_colliderSets[i]->ColliderOwners.PushBack(gameObject);
}
