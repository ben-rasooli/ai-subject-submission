#pragma once
#include <stdexcept>
#include "List.h"

using namespace std;

template <typename T>
class Heap
{
public:
	Heap()
	{
		_heap = new List<T>();
	}

	~Heap()
	{
		delete _heap;
	}

	void Insert(T item)
	{
		_heap->PushBack(item);
		heapifyUp(_heap->Count() - 1);
	}

	void DeleteMin()
	{
		if (_heap->Count() == 0)
			return;
		
		_heap[0] = _heap[_heap->Count() - 1];
		_heap->PopBack();
		heapifyDown(0);
	}

	T ExtractMin()
	{
		if (_heap->Count() == 0)
			return -1;
		else
			return _heap->First();
	}

	int Count()
	{
		return _heap->Count();
	}


	bool IsEmpty()
	{
		return _heap->Count() == 0;
	}

private:
	List<T>* _heap;

	T getLeftSubNode(int superNodeIndex) 
	{
		T result = 2 * superNodeIndex + 1;

		if (result < _heap->Count())
			return result;
		else
			return -1;
	}

	T getRightSubNode(int superNodeIndex) 
	{
		T result = 2 * superNodeIndex + 2;

		if (result < _heap->Count())
			return result;
		else
			return -1;
	}

	T getSuperNode(int subNodeIndex) 
	{
		T result = (subNodeIndex - 1) / 2;

		if (subNodeIndex == 0)
			return -1;
		else
			return result;
	}

	void heapifyUp(int index)
	{
		if (index >= 0 && getSuperNode(index) >= 0 && (*_heap)[getSuperNode(index)] > (*_heap)[index]) {
			swap(&(*_heap)[index], &(*_heap)[getSuperNode(index)]);
			heapifyUp(getSuperNode(index));
		}
	}

	void heapifyDown(int index) 
	{
		T leftSubNode = getLeftSubNode(index);
		T rightSubNode = getRightSubNode(index);

		if (leftSubNode >= 0 && rightSubNode >= 0 && (*_heap)[leftSubNode] > (*_heap)[rightSubNode]) {
			leftSubNode = rightSubNode;
		}
		if (leftSubNode > 0 && (*_heap)[index] > (*_heap)[leftSubNode]) {
			swap((*_heap)[index], (*_heap)[leftSubNode]);
			heapifyDown(leftSubNode);
		}
	}

	void swap(T* a, T* b)
	{
		T t = *a;
		*a = *b;
		*b = t;
	}
};