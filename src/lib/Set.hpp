#pragma once
#include <iostream>
#include <unordered_map>

class SetCell
{
private:
	int _value;
	int _rank;

public:
	SetCell* parent;

	SetCell(int value, int rank);

	void SetValue(int value);
	int GetValue();
	void SetRank(int rank);
	int GetRank();
};

class Set
{
public:
	Set();
	~Set();

	// DISJOINT SET OPERATIONS
	void MakeSet(int value);
	void Union(int xi, int yi);
	SetCell* FindSet(int value);

private:
	std::unordered_map<int, SetCell*> _map;

	void Link(SetCell* x, SetCell* y);
	SetCell* FindSet(SetCell* x);
};
