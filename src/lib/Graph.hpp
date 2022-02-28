#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <limits>
#include <algorithm>
#include "Heap.hpp"
#include "Set.hpp"
#include "SingleLinkedList.hpp"

class EdgeCell
{
public:
	int source, destiny;
	int weight;

	EdgeCell(int s, int d, int w);

};

class Graph
{
public:
	Graph(int n);

	int GetWeight(int a, int b);
	void AddWeight(int a, int b, int value, bool direct = false);
	int Size();

	// SHORTEST PATH ONE SOURCE
	void SetSource(int s);
	bool Relax(int a, int b);
	bool BellmanFord(int s);
	int GetDistance(int d);
	void PrintPath(int d);
	void Dijkstra(int s);

	// SHORTEST PATH ALL PAIRS
	void FloydMarshall();
	int GetDistance(int s, int d);
	void PrintPath(int s, int d);

	// MINIMUM SPANNING TREE
	std::list<EdgeCell> Kruskal();

	// DEBUG
	void PrintEdges();

private:
	std::vector<std::vector<int>> _weights;
	std::vector<EdgeCell> _edges;
	std::vector<std::list<int>> _adj;

	// SHORTEST PATH ONE SOURCE
	std::vector<int> _distances;
	std::vector<int> _pi;

	// SHORTEST PATH ALL PAIRS
	std::vector<std::vector<int>> _distancesAllPairs;
	std::vector<std::vector<int>> _piAllPairs;
	int _n;

	void SetWeight(int a, int b, int value);
	void SetDirectWeight(int a, int b, int value);

	// SHORTEST PATH ALL PAIRS
	bool ValidEdge(int a, int b);
	int AlternateWay(int i, int k, int j);

	// MINIMUM SPANNING TREE
	static bool EdgeCompare(EdgeCell& x, EdgeCell& y);
};