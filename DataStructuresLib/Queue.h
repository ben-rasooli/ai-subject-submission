#pragma once
#include <stdexcept>
#include "pch.h"
#include "DoublyLinkedList.h"
#include "LinkedListNode.h"

template <typename T>
class Queue
{
public:
	Queue()
	{
		_items = new DoublyLinkedList<T>();
	}

	~Queue()
	{
		delete _items;
	}

	int Count()
	{
		return _items->Count();
	}

	bool IsEmpty()
	{
		return _items->IsEmpty();
	}

	void Enqueue(T item)
	{
		_items->PushFront(item);
	}

	T Dequeue()
	{
		LinkedListNode* lastNode = _items->FindLast(_items->Last());
		T result = lastNode->Value;
		_items->Remove(lastNode);
		return result;
	}

	T Peak()
	{
		return _items->Last();
	}

	void Clear()
	{
		_items->Clear();
	}

private:
	DoublyLinkedList<T>* _items;
};
