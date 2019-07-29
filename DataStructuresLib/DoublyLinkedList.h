#pragma once
#include <stdexcept>
#include "pch.h"
#include "LinkedListNode.h"

template <typename T>
class DoublyLinkedList
{
public:
	DoublyLinkedList()
	{
		_count = 0;

		_head = new LinkedListNode();
		_tail = new LinkedListNode();

		_head->prevNode = nullptr;
		_head->nextNode = _tail;

		_tail->prevNode = _head;
		_tail->nextNode = nullptr;
	}

	~DoublyLinkedList()
	{
		Clear();
		delete _head;
		delete _tail;
	}

	int Count()
	{
		return _count;
	}

	bool IsEmpty()
	{
		return _count == 0 && _head->nextNode == _tail && _tail->prevNode == _head;
	}

	void PushBack(int item)
	{
		insert(_tail->prevNode, _tail, item);
	}

	void PushFront(int item)
	{
		insert(_head, _head->nextNode, item);
	}

	void PushAfter(LinkedListNode* node, T item)
	{
		insert(node, node->nextNode, item);
	}

	void PushBefore(LinkedListNode* node, T item)
	{
		insert(node->prevNode, node, item);
	}

	T First()
	{
		if (_head->nextNode == _tail)
			throw std::out_of_range("Linked list is empty");

		return _head->nextNode->Value;
	}

	T Last()
	{
		if (_tail->prevNode == _head)
			throw std::out_of_range("Linked list is empty");

		return _tail->prevNode->Value;
	}


	//--------------------------------------------------
	// It returns the first matching Item
	//--------------------------------------------------
	LinkedListNode* Find(T item)
	{
		if (_count == 0)
			throw std::out_of_range("Can't find on empty collection");

		LinkedListNode* currentNode = _head->nextNode;
		while (currentNode != _tail)
		{
			if (currentNode->Value == item)
				return currentNode;

			currentNode = currentNode->nextNode;
		}

		return nullptr;
	}

	//--------------------------------------------------
	// It returns the last matching Item
	//--------------------------------------------------
	LinkedListNode* FindLast(T item)
	{
		if (_count == 0)
			throw std::out_of_range("Can't find on empty collection");

		LinkedListNode* currentNode = _tail->prevNode;
		while (currentNode != _head)
		{
			if (currentNode->Value == item)
				return currentNode;

			currentNode = currentNode->prevNode;
		}

		return nullptr;
	}

	void Remove(T item)
	{
		if (_count == 0)
			throw std::out_of_range("Can't remove on empty collection");

		remove(Find(item));
	}

	void Remove(LinkedListNode* itemNode)
	{
		remove(itemNode);
	}

	void Clear()
	{
		_count = 0;

		LinkedListNode* currentNode = _head->nextNode;
		while (currentNode != _tail)
		{
			LinkedListNode* nextNode = currentNode->nextNode;
			delete currentNode;
			currentNode = nextNode;
		}

		_head->nextNode = _tail;
		_tail->prevNode = _head;
	}

private:
	int _count;
	LinkedListNode* _head;
	LinkedListNode* _tail;
	
	void insert(LinkedListNode *leftNode, LinkedListNode *rightNode, int item)
	{
		auto pushedItem = new LinkedListNode();
		pushedItem->Value = item;
		pushedItem->prevNode = leftNode;
		pushedItem->nextNode = rightNode;

		leftNode->nextNode = pushedItem;
		rightNode->prevNode = pushedItem;

		_count++;
	}

	void remove(LinkedListNode* node)
	{
		LinkedListNode* prevNode = node->prevNode;
		LinkedListNode* nextNode = node->nextNode;

		delete node;
		prevNode->nextNode = nextNode;
		nextNode->prevNode = prevNode;

		_count--;
	}
};
