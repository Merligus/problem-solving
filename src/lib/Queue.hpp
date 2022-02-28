#pragma once
#include <iostream>
#include <unordered_map>

class QueueCell
{
public:
	QueueCell* previous, * next;

	QueueCell(int value, unsigned index);
	~QueueCell();

	void SetValue(int value);
	int GetValue();

	void SetIndex(unsigned index);
	unsigned GetIndex();

private:
	int _value;
	unsigned _index;
};


class Queue
{
public:
	Queue();
	~Queue();

	int Size();
	bool Empty();
	void Pop();
	void Push(int index, int value);
	std::pair<int, int> RemoveAt(int index);

	void Print();

private:
	QueueCell* _front, * _back;
	std::unordered_map<int, QueueCell*> _map;
	int _size;
};

