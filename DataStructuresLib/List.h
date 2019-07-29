#pragma once
#include "pch.h"
#include <stdexcept>
#include <sstream>
#include <functional>

using namespace std;

template <typename T>
class List
{
public:
	List()
	{
		_count = 0;
		_size = 10;
		_items = new T[_size];
	}

	~List()
	{
		delete[] _items;
	}


	int Count()
	{
		return _count;
	}


	int Size()
	{
		return _size;
	}


	bool IsEmpty()
	{
		return _count == 0;
	}


	void PushBack(T item)
	{
		Insert(_count, item);
	}


	void PushFront(T item)
	{
		Insert(0, item);
	}


	void Insert(int index, T item)
	{
		if (index < 0 || index > _count)
			throw std::out_of_range("index out of range");

		if (_count == _size)
			expandArray();

		for (auto i = _count - 1; i >= index; i--)
			_items[i + 1] = _items[i];

		_items[index] = item;

		_count++;
	}


	T PopBack()
	{
		return Erase(_count - 1);
	}


	T PopFront()
	{
		return Erase(0);
	}


	T Erase(int index)
	{
		if (index < 0 || index >= _count)
			throw std::out_of_range("index out of range");

		int result = _items[index];

		for (auto i = index; i < _count - 1; i++)
			_items[i] = _items[i + 1];

		_count--;

		return result;
	}


	void Remove(T item)
	{
		int itemIndex = -1;
		for (auto i = 0; i < _count; i++)
			if (_items[i] == item)
				itemIndex = i;

		if (itemIndex > 0)
			Erase(itemIndex);
	}


	void Clear()
	{
		_count = 0;
	}


	T First()
	{
		return _items[0];
	}


	T Last()
	{
		return _items[_count - 1];
	}


	T operator[] (int index)
	{
		if (index < 0 || index >= _count)
			throw std::out_of_range("index out of range");

		return _items[index];
	}

	void Sort()
	{
		bubleSort([](int l, int r) {return l > r; });
	}

	void Sort(const function <bool(T, T)> predicate)
	{
		bubleSort(predicate);
	}

	void QuickSort()
	{
		quickSort(_items, 0, _count - 1, [](int item) {return item; });
	}

	void QuickSort(const function <int(T)> sortBy)
	{
		quickSort(_items, 0, _count - 1, sortBy);
	}

	void MergeSort()
	{
		mergeSort(_items, 0, _count - 1, [](int item) {return item; });
	}

	void MergeSort(const function <int(T)> sortBy)
	{
		mergeSort(_items, 0, _count - 1, sortBy);
	}

	string ToString()
	{
		stringstream result;
		for (int i = 0; i < _count - 1; i++)
		{
			string item = to_string(_items[i]) + ",";
			result << item;
		}

		result << _items[_count - 1];

		return result.str();
	}

	bool Equals(List<T>* other)
	{
		return GetHash() == other->GetHash();
	}

	unsigned int GetHash()
	{
		unsigned int hash = 0;

		for (unsigned int i = 0; i < _count; ++i)
			hash = (hash * 1313) + _items[i] * 13;

		return hash;
	}

private:
	int _count;
	int _size;
	T* _items;

	void expandArray()
	{
		_size *= 2;
		T* biggerItems = new T[_size];

		for (auto i = 0; i < _count; i++)
			biggerItems[i] = _items[i];

		delete[] _items;
		_items = biggerItems;
	}

	void bubleSort(const function <bool(T, T)> predicate)
	{
		bool swapped;
		for (int i = 0; i < _count - 1; i++)
		{
			swapped = false;
			for (int j = 0; j < _count - i - 1; j++)
			{
				if (predicate(_items[j], _items[j + 1]))
				{
					swap(&_items[j], &_items[j + 1]);
					swapped = true;
				}
			}

			if (swapped == false)
				break;
		}
	}

	void quickSort(T* items, int low, int high, const function <int(T)> sortBy)
	{
		if (sortBy(low) < sortBy(high))
		{
			int partitionIndex = partition(items, low, high, sortBy);

			quickSort(items, low, partitionIndex - 1, sortBy);
			quickSort(items, partitionIndex + 1, high, sortBy);
		}
	}

	int partition(T* items, int low, int high, const function <int(T)> sortBy)
	{
		T pivot = items[high];
		int smallerIndex = (low - 1);

		for (int j = low; j <= high - 1; j++)
		{
			if (sortBy(items[j]) <= sortBy(pivot))
			{
				smallerIndex++;
				swap(&items[smallerIndex], &items[j]);
			}
		}
		swap(&items[smallerIndex + 1], &items[high]);
		return (smallerIndex + 1);
	}

	void swap(int* a, int* b)
	{
		int t = *a;
		*a = *b;
		*b = t;
	}

	void mergeSort(T* items, int low, int high, const function <int(T)> sortBy)
	{
		if (low < high)
		{
			int middle = low + (high - low) / 2;
 
			mergeSort(items, low, middle, sortBy);
			mergeSort(items, middle + 1, high, sortBy);

			merge(items, low, middle, high, sortBy);
		}
	}

	void merge(T* items, int low, int mid, int high, const function <int(T)> sortBy)
	{
		int p1 = low;
		int p2 = mid + 1;
		T* merged = (T*)malloc(sizeof(T) * (high - low + 1));
		int p = 0;
		while (p1 < mid + 1 && p2 < high + 1)
		{
			if (sortBy(items[p1]) > sortBy(items[p2]))
			{
				merged[p] = items[p2];
				p2++;
			}
			else
			{
				merged[p] = items[p1];
				p1++;
			}
			p++;
		}

		while (p1 < mid + 1)
			merged[p++] = items[p1++];

		while (p2 < high + 1)
			merged[p++] = items[p2++];

		for (int i = 0; i < (high - low + 1); i++)
			items[low + i] = merged[i];

		free(merged);
	}
};
