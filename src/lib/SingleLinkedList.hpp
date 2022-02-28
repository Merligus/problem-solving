#pragma once
#include <iostream>

class SingleLinkedListCell
{
public:
	SingleLinkedListCell* next;
	SingleLinkedListCell* arbitrary;

	SingleLinkedListCell(int k);
	void SetKey(int k);
	int GetKey();

private:

	int key;
};

class SingleLinkedList
{
public:
	SingleLinkedList();
	~SingleLinkedList();

	void PushFront(int value);
	void Push(int value);
	void Clear();
	int PopFront();
	bool Empty();
	SingleLinkedListCell* Front();
	SingleLinkedListCell* Back();

	void Print();

private:
	SingleLinkedListCell* _head, * _back;

};
