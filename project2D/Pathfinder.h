#pragma once
#include "List.h"
#include "Path.h"
#include "Node.h"

using namespace std;

class Pathfinder
{
public:
	Pathfinder(List<Node*>* nodes);
	~Pathfinder();

	/*------------------------------------------------------
	Returns a path from a GridNode to another one containing
	all the connecting GridNodes in between.

	@param from: origin GridNode Id
	@param from: destination GridNode Id
	------------------------------------------------------*/
	void FindPath(string from, string to, Path* path);

private:
	List<Node*>* _nodes;;
	List<Node*> _openSet;
	List<Node*> _closedSet;
	int _diagnalMovementCost;
	int _straightMovementCost;

	int calculateHCost(Node* from, Node* to);
	int findDiagnalMovementCost(Node* node);
	int findStraightMovementCost(Node* node);
};

