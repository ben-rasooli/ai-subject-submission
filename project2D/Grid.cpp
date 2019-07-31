#include "Grid.h"

Grid::Grid()
{
	populateNodes();
	_path = nullptr;
	_wanderingTargetPosition = Vector2(-1, -1);
}

Grid::~Grid()
{
	for (int i = 0; i < _nodes.Count(); i++)
	{
		for (int ii = 0; ii < _nodes[i]->Neighbors.Count(); ii++)
			delete _nodes[i]->Neighbors[ii];

		delete _nodes[i];
	}

	if (_path)
		delete _path;
}

void Grid::Draw(aie::Renderer2D * renderer)
{
	for (int i = 0; i < _nodes.Count(); i++)
	{
		int color = _nodes[i]->Type == NodeType::Normal ? 0xa9d6c6ff : 0xb39e4fff;

		if (_path)
			if (_path->Corners.HasValue(_nodes[i]->Position))
				color = 0x333333ff;

		if (_wanderingTargetPosition != Vector2(-1, -1))
		{
			auto nodePos = _nodes[i]->Position;
			if(_wanderingTargetPosition == nodePos)
				color = 0xe0563aff;
		}

		renderer->SetRenderColour(color);
		renderer->DrawBox(_nodes[i]->Position.x + WindowDisplayOffset * 2, _nodes[i]->Position.y + WindowDisplayOffset, GRID_CELL_SIZE - 1, GRID_CELL_SIZE - 1);
	}
}

Vector2 Grid::GetARandomReachablePosition()
{
	Vector2 result = Vector2();

	// find reachable nodes
	List<Node*> reachableNodes;

	for (int i = 0; i < _nodes.Count(); i++)
		if (_nodes[i]->Type == NodeType::Normal)
			reachableNodes.PushBack(_nodes[i]);

	// pick a random reachable node
	auto randomNode = reachableNodes[rand() % reachableNodes.Count()];

	result = randomNode->Position;

	// apply screen offset
	result.x += WindowDisplayOffset * 2;
	result.y += WindowDisplayOffset;

	return result;
}

void Grid::ShowPath(Path* path)
{
	_path = path;
}

void Grid::ClearPath()
{
	_path = nullptr;
}

void Grid::ShowWanderingTarget(Vector2 position)
{
	_wanderingTargetPosition = position;
	_wanderingTargetPosition.x -= WindowDisplayOffset * 2;
	_wanderingTargetPosition.y -= WindowDisplayOffset;
}

std::string Grid::ToString()
{
	ostringstream result;

	for (int i = 0; i < _nodes.Count(); i++)
	{
		auto node = _nodes[i];
		result << "ID: " << node->Id << " Type: " << castNodeTypeToString(node->Type) << " " << "[x: " << node->Position.x << " " << "y: " << node->Position.y << "]" << endl;
		result << "Neighbors:" << endl;
		for (int ii = 0; ii < node->Neighbors.Count(); ii++)
			result << "\tID: " << node->Neighbors[ii]->Node->Id << " cost: " << node->Neighbors[ii]->Cost << endl;
		result << endl;
	}

	return result.str();
}

// It creates nodes using a JSON file called nodes.json placed at bin folder
void Grid::populateNodes()
{
	FILE* fp = fopen("./nodes.json", "rb");
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document document;
	document.ParseStream(is);
	fclose(fp);

	auto nodes = document["Nodes"].GetArray();

	// 1. setup each cell
	for (auto& nodeData : nodes)
	{
		Node* node = new Node();

		// id
		node->Id = nodeData["Id"].GetString();

		// type
		auto type = nodeData["Type"].GetInt();
		node->Type = static_cast<NodeType>(type);

		// position
		auto position = nodeData["Position"].GetArray();
		node->Position = Vector2(position[0].GetFloat(), position[1].GetFloat());

		_nodes.PushBack(node);
	}

	// 2. setup neighbors for each cell
	for (int i = 0; i < nodes.Size(); i++)
	{
		auto neighbors = nodes[i]["Neighbors"].GetArray();
		for (int ii = 0; ii < neighbors.Size(); ii++)
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor{ _nodes.Find([=](Node* n) { return n->Id == neighbors[ii].GetString(); }) , 0 });
	}

	// 3. setup neighbors costs for each cell
	for (int i = 0; i < _nodes.Count(); i++)
	{
		Node* node = _nodes[i];
		for (int ii = 0; ii < node->Neighbors.Count(); ii++)
		{
			Node* neighborNode = node->Neighbors[ii]->Node;
			int magnitude = (int)((neighborNode->Position - node->Position).magnitude());
			node->Neighbors[ii]->Cost = magnitude;
		}
	}
}

string Grid::castNodeTypeToString(NodeType nodeType)
{
	switch (nodeType)
	{
	case Normal:
		return "Normal";
	case Wall:
		return "Wall";
	default:
		return "?";
	}
}
