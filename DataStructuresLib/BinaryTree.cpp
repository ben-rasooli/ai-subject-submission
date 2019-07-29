#include "pch.h"
#include "BinaryTree.h"
#include <stdexcept>

BinaryTree::BinaryTree()
{
	_count = 0;
	_rootNode = nullptr;
}


BinaryTree::~BinaryTree()
{
	while (_rootNode)
		remove(_rootNode);
}

int BinaryTree::Count()
{
	return _count;
}

bool BinaryTree::IsEmpty()
{
	return _count == 0;
}

void BinaryTree::Insert(int value)
{
	BinaryTreeNode* insertedNode = new BinaryTreeNode();
	insertedNode->Value = value;
	insertedNode->supernode = nullptr;
	insertedNode->leftSubnode = nullptr;
	insertedNode->rightSubnode = nullptr;

	if (!_rootNode)
	{
		_rootNode = insertedNode;
		_count++;
		return;
	}

	BinaryTreeNode* currentNode = _rootNode;
	
	while (currentNode)
	{
		insertedNode->supernode = currentNode;

		if (insertedNode->Value < currentNode->Value)
			if (currentNode->leftSubnode)
				currentNode = currentNode->leftSubnode;
			else
			{
				currentNode->leftSubnode = insertedNode;
				break;
			}
		else if (insertedNode->Value > currentNode->Value)
			if (currentNode->rightSubnode)
				currentNode = currentNode->rightSubnode;
			else
			{
				currentNode->rightSubnode = insertedNode;
				break;
			}
		else
			return;
	}

	_count++;
}

BinaryTreeNode* BinaryTree::Find(int value)
{
	if (_count == 0)
		throw std::out_of_range("Can't find on empty collection");

	return find(value, _rootNode);
}

void BinaryTree::Remove(int value)
{
	BinaryTreeNode* nodeToBeRemoved = Find(value);

	if (!nodeToBeRemoved)
		throw std::out_of_range("Value not found");

	remove(nodeToBeRemoved);
}

List<int>* BinaryTree::GetSortedItems()
{
	List<int>* result = new List<int>();
	traverseInorder(_rootNode, result);
	return result;
}

BinaryTreeNode* BinaryTree::find(int value, BinaryTreeNode *node)
{
	if (node)
	{
		if (value == node->Value)
			return node;
		if (value < node->Value)
			return find(value, node->leftSubnode);
		else
			return find(value, node->rightSubnode);
	}
	else 
		return nullptr;
}

void BinaryTree::remove(BinaryTreeNode* node)
{
	// if leaf node
	if (!node->leftSubnode && !node->rightSubnode)
		removeLeafNode(node);
	// if node has a single subnode
	else if (!node->leftSubnode != !node->rightSubnode)
		removeSingleSubnodedNode(node);
	// if node has two subnodes
	else
		removeDoubleSubnodedNode(node);

	_count--;
}

void BinaryTree::removeLeafNode(BinaryTreeNode* node)
{
	if (node == _rootNode)
		_rootNode = nullptr;
	else
		if (node->supernode->leftSubnode == node)
			node->supernode->leftSubnode = nullptr;
		else
			node->supernode->rightSubnode = nullptr;

	delete node;
	node = nullptr;
}

void BinaryTree::removeSingleSubnodedNode(BinaryTreeNode* node)
{
	BinaryTreeNode* subnodeOfRemovedNode;

	if (node->leftSubnode)
		subnodeOfRemovedNode = node->leftSubnode;
	else
		subnodeOfRemovedNode = node->rightSubnode;

	subnodeOfRemovedNode->supernode = node->supernode;

	if (node == _rootNode)
		_rootNode = subnodeOfRemovedNode;
	else
		// find which of its supernode's subnodes is this node
		if (node->supernode->leftSubnode == node)
			node->supernode->leftSubnode = subnodeOfRemovedNode;
		else
			node->supernode->rightSubnode = subnodeOfRemovedNode;

	delete node;
	node = nullptr;
}

void BinaryTree::removeDoubleSubnodedNode(BinaryTreeNode* node)
{
	BinaryTreeNode* currentNode = node->rightSubnode;

	// find the smallest subnode
	while (currentNode->leftSubnode != nullptr)
		currentNode = currentNode->leftSubnode;

	node->Value = currentNode->Value;

	remove(currentNode);
}

void BinaryTree::traverseInorder(BinaryTreeNode* node, List<int>* accumilator) {
	if (!node) return;

	traverseInorder(node->leftSubnode, accumilator);
	accumilator->PushBack(node->Value);
	traverseInorder(node->rightSubnode, accumilator);
}

