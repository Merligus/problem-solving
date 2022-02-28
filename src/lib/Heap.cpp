#include "Heap.hpp"

HeapCell::HeapCell(int value, int index)
{
	SetValue(value);
	SetIndex(index);
}

HeapCell::~HeapCell()
{
	// std::cout << _index << ":" << _value << " removed\n";
}

void HeapCell::SetValue(int value)
{
	_value = value;
}

int HeapCell::GetValue()
{
	return _value;
}

void HeapCell::SetIndex(int index)
{
	_index = index;
}

int HeapCell::GetIndex()
{
	return _index;
}

// **************************************************
// **************************************************
// **************************************************
// **************************************************
// **************************************************
// **************************************************
// **************************************************
// **************************************************
// **************************************************

Heap::Heap(bool bMinheap)
{
	_bMinHeap = bMinheap;
}

Heap::Heap(std::vector<int> v, bool bMinheap)
{
	_bMinHeap = bMinheap;
	// Make a min heap with the largest numbers and store the k
	for (int i = 0; i < v.size(); i++)
		Add(i, v[i]);
}

Heap::~Heap()
{
	for (auto& cell : _heap)
		delete cell;
}

// O(lgn)
void Heap::Add(int ind, int val)
{
	HeapCell* cell;
	cell = new HeapCell(val, ind);
	_heap.push_back(cell);
	_index[ind] = _heap.size() - 1;

	// O(lgn)
	UpdateHeapUp(_heap.size() - 1);
}

// O(1)
int Heap::Size()
{
	return _heap.size();
}

// O(1)
bool Heap::Empty()
{
	return _heap.empty();
}

// O(lgn)
std::pair<int, int> Heap::Pop()
{
	HeapCell* removedCell;
	std::pair<int, int> max;
	// pop the max number of the array
	max = { _heap[0]->GetIndex(), _heap[0]->GetValue() };
	_index[_heap[0]->GetIndex()] = -1;
	removedCell = _heap[0];
	_heap[0] = _heap[_heap.size() - 1];
	_index[_heap[0]->GetIndex()] = 0;
	_heap.pop_back();
	delete removedCell;

	// update the heap
	// O(lgn)
	UpdateHeap(0);

	return max;
}

// O(lgn)
std::pair<int, int> Heap::Delete(int index)
{
	HeapCell* removedCell;
	std::pair<int, int> max;
	int ind = _index[index];
	// pop the max number of the array
	max = { _heap[ind]->GetIndex(), _heap[ind]->GetValue() };
	_index[_heap[ind]->GetIndex()] = -1;
	removedCell = _heap[ind];
	_heap[ind] = _heap[_heap.size() - 1];
	_index[_heap[ind]->GetIndex()] = ind;
	_heap.pop_back();
	delete removedCell;

	// update the heap
	// O(lgn)
	UpdateHeap(ind);
	UpdateHeapUp(ind);

	return max;
}

// O(lgn)
void Heap::UpdateHeap(int index)
{
	int l = 2 * index + 1;
	int r = 2 * (index + 1);
	// find the top priority between index, left and right son in the heap
	int top_priority = index;
	if (_bMinHeap)
	{
		if (r < _heap.size() && _heap[r]->GetValue() < _heap[index]->GetValue())
			top_priority = r;
		if (l < _heap.size() && _heap[l]->GetValue() < _heap[top_priority]->GetValue())
			top_priority = l;
	}
	else
	{
		if (r < _heap.size() && _heap[r]->GetValue() > _heap[index]->GetValue())
			top_priority = r;
		if (l < _heap.size() && _heap[l]->GetValue() > _heap[top_priority]->GetValue())
			top_priority = l;
	}

	// if the top priority is not the index, then...
	if (top_priority != index)
	{
		// update the top priority to be the parent
		HeapCell* aux;
		aux = _heap[index];
		_heap[index] = _heap[top_priority];
		_heap[top_priority] = aux;

		// update the index in the heap
		_index[_heap[top_priority]->GetIndex()] = top_priority;
		_index[_heap[index]->GetIndex()] = index;

		// update the heap
		// O(lgn)
		UpdateHeap(top_priority);
	}
}

// O(lgn)
void Heap::UpdateHeapUp(int index)
{
	bool bUpdate(false);
	int p = (index - 1) / 2;
	if (p < 0 || index >= _heap.size())
		return;
	if (_bMinHeap)
	{
		if (_heap[index]->GetValue() < _heap[p]->GetValue())
			bUpdate = true;
	}
	else
	{
		if (_heap[index]->GetValue() > _heap[p]->GetValue())
			bUpdate = true;
	}

	if (bUpdate)
	{
		HeapCell* aux;
		aux = _heap[index];
		_heap[index] = _heap[p];
		_heap[p] = aux;

		// update the index in the heap
		_index[_heap[p]->GetIndex()] = p;
		_index[_heap[index]->GetIndex()] = index;

		// O(lgn)
		UpdateHeapUp(p);
	}
}

// O(lgn)
void Heap::UpdateValue(int ind, int newVal)
{
	std::unordered_map<int, int>::const_iterator finder;
	int heapIndex;

	// Average O(1)
	finder = _index.find(ind);
	if (finder != _index.end())
	{
		heapIndex = finder->second;
		if (heapIndex >= 0)
		{
			_heap[heapIndex]->SetValue(newVal);
			// O(lgn)
			UpdateHeap(heapIndex);
			UpdateHeapUp(heapIndex);
		}
		else
			std::cout << "Not Found\n";
	}
	else
		std::cout << "Not Found\n";
}

int Heap::Front()
{
	return _heap[0]->GetValue();
}

void Heap::Print(std::string s)
{
	std::cout << s;
	for (int i = 0; i < _heap.size(); i++)
		std::cout << _heap[i]->GetValue() << " ";
	std::cout << "\n";
}