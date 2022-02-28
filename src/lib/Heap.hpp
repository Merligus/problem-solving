#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

class HeapCell
{
public:
	HeapCell(int value, int index);
	~HeapCell();

	void SetValue(int value);
	int GetValue();
	void SetIndex(int index);
	int GetIndex();

private:
	int _value;
	int _index;
};

class Heap
{
public:
	Heap(bool bMinheap);
	Heap(std::vector<int> v, bool bMinheap = true);
	~Heap();
	int Size();
	bool Empty();

	// HEAP
	void Add(int ind, int val);
	std::pair<int, int> Pop();
	std::pair<int, int> Delete(int index);
	void UpdateHeap(int index);
	void UpdateHeapUp(int index);
	void UpdateValue(int ind, int newVal);
	int Front();

	// DEBUG
	void Print(std::string s);

private:
	// holds the index of the HeapCell->index in the heap
	std::unordered_map<int, int> _index;
	std::vector<HeapCell*> _heap;
	bool _bMinHeap;
};