#pragma once
#include <string>
#include "List.h"
#include "Vector2.h"

using namespace std;

enum NodeType
{
	Normal,
	Wall
};

struct NodeNeighbor;

struct Node
{
	string Id;
	NodeType Type = NodeType::Normal;
	List<NodeNeighbor*> Neighbors;
	Vector2 Position;
	Node* Origin;
	int GCost = 0;
	int HCost = 0;
	int FCost() { return GCost + HCost; }
};

struct NodeNeighbor
{
	Node* Node;
	int Cost;
};
