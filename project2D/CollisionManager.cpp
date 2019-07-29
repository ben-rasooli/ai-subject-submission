#include "CollisionManager.h"

CollisionManager* CollisionManager::_inst = nullptr;

CollisionManager::CollisionManager()
{
	ColliderSet* colSet_hero = new ColliderSet();
	colSet_hero->Layer = CollisionLayer::HERO;
	colSet_hero->CollidableLayers.PushBack(CollisionLayer::FLYING_ROCK);
	_colliderSets.PushBack(colSet_hero);

	ColliderSet* colSet_flyingRock = new ColliderSet();
	colSet_flyingRock->Layer = CollisionLayer::FLYING_ROCK;
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
	for (int i = 0; i < _colliderSets.Count(); i++)
	{
		// find target collider owners inside collidableLayers
		for (int ii = 0; ii < _colliderSets[i]->CollidableLayers.Count(); ii++)
		{
			for (int iii = 0; iii < _colliderSets.Count(); iii++)
				if (_colliderSets[iii]->Layer == _colliderSets[i]->CollidableLayers[ii])
				{
					for (int iiii = 0; iiii < _colliderSets[i]->ColliderOwners.Count(); iiii++)
						for (int iiiii = 0; iiiii < _colliderSets[iii]->ColliderOwners.Count(); iiiii++)
						{
							GameObject* targetColliderOwner = _colliderSets[iii]->ColliderOwners[iiiii];
							if (_colliderSets[i]->ColliderOwners[iiii]->GetCollider()->IsCollidingWith(targetColliderOwner->GetCollider()))
							{
								targetColliderOwner->OnCollision(_colliderSets[i]->ColliderOwners[iiii]);
							}
						}
				}
		}
	}
}

void CollisionManager::Draw(aie::Renderer2D* renderer)
{
	// draw every colliderOwner/GameObject in every colliderSets
	for (int i = 0; i < _colliderSets.Count(); i++)
		for (int ii = 0; ii < _colliderSets[i]->ColliderOwners.Count(); ii++)
			_colliderSets[i]->ColliderOwners[ii]->GetCollider()->Draw(renderer);
}

void CollisionManager::AddGameObject(GameObject * gameObject, CollisionLayer layer)
{
	for (int i = 0; i < _colliderSets.Count(); i++)
		if (_colliderSets[i]->Layer == layer)
			_colliderSets[i]->ColliderOwners.PushBack(gameObject);
}
