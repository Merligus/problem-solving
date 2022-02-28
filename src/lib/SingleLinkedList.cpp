#include "SingleLinkedList.hpp"

SingleLinkedListCell::SingleLinkedListCell(int k)
{
	next = NULL;
	arbitrary = NULL;
	SetKey(k);
}

void SingleLinkedListCell::SetKey(int k)
{
	key = k;
}

int SingleLinkedListCell::GetKey()
{
	return key;
}

// ************************************************
// ************************************************
// ************************************************
// ************************************************
// ************************************************
// ************************************************
// ************************************************

SingleLinkedList::SingleLinkedList()
{
	_head = NULL;
	_back = NULL;
}

SingleLinkedList::~SingleLinkedList()
{
	Clear();
}

void SingleLinkedList::PushFront(int value)
{
	SingleLinkedListCell* newCell;
	newCell = new SingleLinkedListCell(value);
	if (_head != NULL)
		newCell->next = _head;
	else
		_back = newCell;
	_head = newCell;
}

void SingleLinkedList::Push(int value)
{
	SingleLinkedListCell* newCell;
	newCell = new SingleLinkedListCell(value);
	if (_back != NULL)
		_back->next = newCell;
	else
		_head = newCell;
	_back = newCell;
}

void SingleLinkedList::Clear()
{
	SingleLinkedListCell* current;
	while (_head != NULL)
	{
		current = _head;
		// std::cout << current->GetKey() << " ";
		_head = current->next;
		delete current;
	}
	// std::cout << " Cleared\n";
}

int SingleLinkedList::PopFront()
{
	SingleLinkedListCell* removedCell;
	if (_head != NULL)
	{
		int num;
		removedCell = _head;
		if (_back == _head)
			_back = NULL;
		_head = _head->next;
		num = removedCell->GetKey();
		delete removedCell;
		return num;
	}
	else
		return 0;
}

bool SingleLinkedList::Empty()
{
	if (_head == NULL)
		return true;
	else
		return false;
}

void SingleLinkedList::Print()
{
	SingleLinkedListCell* current;
	current = _head;
	while (current != NULL)
	{
		std::cout << current->GetKey() << ":";
		if (current->arbitrary != NULL)
			std::cout << current->arbitrary->GetKey() << " ";
		else
			std::cout << "NULL ";
		current = current->next;
	}
	std::cout << "\n";
}

SingleLinkedListCell* SingleLinkedList::Front()
{
	return _head;
}

SingleLinkedListCell* SingleLinkedList::Back()
{
	return _back;
}