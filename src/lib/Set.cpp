#include "Set.hpp"

SetCell::SetCell(int value, int rank)
{
	_value = value;
	_rank = rank;
	parent = NULL;
}

void SetCell::SetValue(int value)
{
	_value = value;
}

int SetCell::GetValue()
{
	return _value;
}

void SetCell::SetRank(int rank)
{
	_rank = rank;
}

int SetCell::GetRank()
{
	return _rank;
}

// ****************************************
// ****************************************
// ****************************************
// ****************************************
// ****************************************
// ****************************************
// ****************************************
// ****************************************

Set::Set()
{

}

Set::~Set()
{
	for (auto it = _map.begin(); it != _map.end(); ++it)
		delete it->second;
}

// O(1)
void Set::MakeSet(int value)
{
	SetCell* newCell;
	newCell = new SetCell(value, 0);
	newCell->parent = newCell;
	_map[value] = newCell;
}

// O(1)
void Set::Union(int xi, int yi)
{
	// O(1)
	Link(FindSet(_map[xi]), FindSet(_map[yi]));
}

// O(1)
void Set::Link(SetCell* x, SetCell* y)
{
	if (x->GetRank() > y->GetRank())
		y->parent = x;
	else
	{
		x->parent = y;
		if (x->GetRank() == y->GetRank())
			y->SetRank(y->GetRank() + 1);
	}
}

// O(alpha(n))
SetCell* Set::FindSet(int value)
{
	return FindSet(_map[value]);
}

SetCell* Set::FindSet(SetCell* x)
{
	if (x != x->parent)
		x->parent = FindSet(x->parent);
	return x->parent;
}