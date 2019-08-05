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

	/*------------------------------------------------------
	Returns the id of a cell located at the provided position.

	@param worldPosition: position in the screen coordinates
	------------------------------------------------------*/
	string GetCellID(Vector2 worldPosition);

	List<Node*>* Nodes() { return &_nodes; }

	void ShowPath(Path* path);
	void ClearPath();

	/*------------------------------------------------------
	Returns a position on the screen considering the grid's
	offset from the screen edge.

	@param gridPosition: position in the grid coordinates
	------------------------------------------------------*/
	Vector2 GetPositionOnScreen(Vector2 gridPosition);
	
	/*------------------------------------------------------
	Renders a red qsuare on the grid indicading the wandering
	location.

	@param position: position in the screen coordinates
	------------------------------------------------------*/
	void ShowWanderingTarget(Vector2 position);

	string ToString();

private:
	List<Node*> _nodes;
	Path* _path;
	Vector2 _wanderingTargetPosition;

	void populateNodes();

	/*------------------------------------------------------
	Returns a position on the grid considering its offset
	from the screen edge.

	@param worldPosition: position in the screen coordinates
	------------------------------------------------------*/
	Vector2 GetPositionOnGrid(Vector2 worldPosition);

	// This is used for ToString() method, so we can see the type
	// of the node instead of just a number
	string castNodeTypeToString(NodeType nodeType);
};

