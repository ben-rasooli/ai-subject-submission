#pragma once
#include "Renderer2D.h"
#include "List.h"
#include "Node.h"
#include "Path.h"
#include "Settings.h"
#include "Vector2.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/filereadstream.h"
#include <cstdio>

using namespace std;
using namespace rapidjson;

class Grid
{
public:
	Grid();
	~Grid();

	void Draw(aie::Renderer2D* renderer);
	Vector2 GetARandomReachablePosition();

	List<Node*>* Nodes() { return &_nodes; }

	void ShowPath(Path* path);
	void ClearPath();
	
	void ShowWanderingTarget(Vector2 position);

	string ToString();

private:
	List<Node*> _nodes;
	Path* _path;
	Vector2 _wanderingTargetPosition;

	void populateNodes();

	// This is used for ToString() method, so we can see the type
	// of the node instead of just a number
	string castNodeTypeToString(NodeType nodeType);
};

