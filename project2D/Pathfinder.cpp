#include "Pathfinder.h"

Pathfinder::Pathfinder(List<Node*>* nodes)
{
	_nodes = nodes;
	_diagnalMovementCost = findDiagnalMovementCost(_nodes->First());
	_straightMovementCost = findStraightMovementCost(_nodes->First());
}

Pathfinder::~Pathfinder()
{
}

Path* Pathfinder::FindPath(string from, string to)
{
	Path* path = new Path();
	Node* origin = _nodes->Find([from](auto node) { return node->Id == from; });
	Node* destination = _nodes->Find([to](auto node) { return node->Id == to; });

	_openSet.PushBack(origin);

	while (_openSet.Count() > 0)
	{
		// find the cheapest node to explore
		Node* currentNode = _openSet.First();
		for (int i = 1; i < _openSet.Count(); i++)
			// if there is a better/cheaper node to choose
			if (_openSet[i]->FCost() < currentNode->FCost() || _openSet[i]->FCost() == currentNode->FCost() && _openSet[i]->HCost < currentNode->HCost)
				currentNode = _openSet[i];

		_openSet.Remove(currentNode);
		_closedSet.PushBack(currentNode);

		// build the path if the destination is reached
		if (currentNode == destination)
		{
			Node* currentPathNode = destination;

			while (currentPathNode != origin)
			{
				path->Corners.PushFront(currentPathNode->Position);
				currentPathNode = currentPathNode->Origin;
			}
			path->Corners.PushFront(origin->Position);
			break;
		}

		// expand the to-be-explored collection
		for (int i = 0; i < currentNode->Neighbors.Count(); i++)
		{
			NodeNeighbor* neighbor = currentNode->Neighbors[i];

			if (neighbor->Node->Type == NodeType::Wall || _closedSet.HasValue(neighbor->Node))
				continue;

			int totalCostToNeighbor = currentNode->GCost + neighbor->Cost;
			if (totalCostToNeighbor < neighbor->Node->GCost || !_openSet.HasValue(neighbor->Node))
			{
				neighbor->Node->GCost = totalCostToNeighbor;
				neighbor->Node->HCost = calculateHCost(neighbor->Node, destination);
				neighbor->Node->Origin = currentNode;

				if (!_openSet.HasValue(neighbor->Node))
					_openSet.PushBack(neighbor->Node);
			}
		}
	}

	return path;
}

int Pathfinder::calculateHCost(Node* from, Node* to)
{
	int distanceX = abs(from->Position.x - to->Position.x) / _straightMovementCost;
	int distanceY = abs(from->Position.y - to->Position.y) / _straightMovementCost;

	if (distanceX > distanceY)
		return _diagnalMovementCost * distanceY + _straightMovementCost * (distanceX - distanceY);
	return _diagnalMovementCost * distanceX + _straightMovementCost * (distanceY - distanceX);
}

int Pathfinder::findDiagnalMovementCost(Node* node)
{
	int result = node->Neighbors.First()->Cost;

	for (int i = 0; i < node->Neighbors.Count(); i++)
		if (result < node->Neighbors[i]->Cost)
			result = node->Neighbors[i]->Cost;

	return result;
}

int Pathfinder::findStraightMovementCost(Node* node)
{
	int result = node->Neighbors.First()->Cost;

	for (int i = 0; i < node->Neighbors.Count(); i++)
		if (result > node->Neighbors[i]->Cost)
			result = node->Neighbors[i]->Cost;

	return result;
}
