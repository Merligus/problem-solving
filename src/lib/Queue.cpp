#include "Queue.hpp"

// O(1)
QueueCell::QueueCell(int value, unsigned index)
{
	previous = NULL;
	next = NULL;
	SetValue(value);
	SetIndex(index);
}

QueueCell::~QueueCell()
{
	// std::cout << _index << ":" << _value << " removed\n";
}

void QueueCell::SetValue(int value)
{
	_value = value;
}

int QueueCell::GetValue()
{
	return _value;
}

void QueueCell::SetIndex(unsigned index)
{
	_index = index;
}

unsigned QueueCell::GetIndex()
{
	return _index;
}

// *****************************************************************
// *****************************************************************
// *****************************************************************
// *****************************************************************
// *****************************************************************
// *****************************************************************
// *****************************************************************
// *****************************************************************
// *****************************************************************

Queue::Queue()
{
	_front = NULL;
	_back = NULL;
	_size = 0;
}

// O(size)
Queue::~Queue()
{
	while (!Empty())
		Pop();
}

// O(1)
int Queue::Size()
{
	return _size;
}

// O(1)
bool Queue::Empty()
{
	if (_front == NULL)
		return true;
	else
		return false;
}

// O(1)
void Queue::Pop()
{
	QueueCell* removedCell;
	removedCell = _front;

	if (Empty())
		return;

	// update the map
	// Average O(1)
	_map.erase(removedCell->GetIndex());

	// O(1)
	_size--;
	_front = _front->next;
	if (_front != NULL)
		_front->previous = NULL;
	delete removedCell;
}

// O(1)
void Queue::Push(int index, int value)
{
	QueueCell* newCell;
	newCell = new QueueCell(value, index);
	if (_back != NULL)
		_back->next = newCell;
	if (_front == NULL)
		_front = newCell;
	newCell->previous = _back;
	_back = newCell;
	_size++;

	// update the map
	_map[index] = newCell;
}

// Average O(1)
std::pair<int, int> Queue::RemoveAt(int index)
{
	std::unordered_map<int, QueueCell*>::const_iterator finder;
	QueueCell* removedCell;
	std::pair<int, int> tuple(-1, -1);

	// Average O(1)
	finder = _map.find(index);
	if (finder != _map.end())
	{
		removedCell = finder->second;
		// update the map
		// Average O(1)
		_map.erase(index);
		_size--;

		if (removedCell->previous != NULL)
			removedCell->previous->next = removedCell->next;
		if (removedCell->next != NULL)
			removedCell->next->previous = removedCell->previous;

		if (_front == removedCell)
			_front = removedCell->next;
		if (_back == removedCell)
			_back = removedCell->previous;

		tuple.first = removedCell->GetIndex();
		tuple.second = removedCell->GetValue();

		delete removedCell;
	}

	return tuple;
}

void Queue::Print()
{
	QueueCell* current(_front);
	while (current != NULL)
	{
		std::cout << current->GetIndex() << ":" << current->GetValue() << " ";
		current = current->next;
	}
	std::cout << "\n";
}