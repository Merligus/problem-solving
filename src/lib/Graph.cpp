#include "Graph.hpp"

EdgeCell::EdgeCell(int sour, int dest, int weig)
{
	source = sour;
	destiny = dest;
	weight = weig;
}

// ****************************************
// ****************************************
// ****************************************
// ****************************************
// ****************************************
// ****************************************
// ****************************************
// ****************************************

/*
// TOPOLOGICAL SORT

from collections import deque

def top_sort(graph):
	sorted_nodes, visited = deque(), set()
	for node in graph.keys():
		if node not in visited:
		   dfs(graph, node, visited, sorted_nodes)
	return list(sorted_nodes)

def dfs(graph, start_node, visited, sorted_nodes):
	visited.add(start_node)
	if start_node in graph:
		neighbors = graph[start_node]
		for neighbor in neighbors:
			if neighbor not in visited:
				dfs(graph, neighbor, visited, sorted_nodes)
	sorted_nodes.appendleft(start_node)
*/

Graph::Graph(int n)
{
	std::list<int> emptyList;
	for (int i = 0; i < n; i++)
	{
		std::vector<int> aux(n, std::numeric_limits<int>::max());
		aux[i] = 0;
		_weights.push_back(aux);
		_adj.push_back(emptyList);
	}

	_n = n;
}

int Graph::GetWeight(int a, int b)
{
	return _weights[a][b];
}

void Graph::SetWeight(int a, int b, int value)
{
	_weights[a][b] = value;
	_weights[b][a] = value;
}

void Graph::SetDirectWeight(int a, int b, int value)
{
	_weights[a][b] = value;
}

void Graph::AddWeight(int a, int b, int value, bool direct)
{
	if (direct)
	{
		SetDirectWeight(a, b, value);
		_adj[a].push_back(b);
	}
	else
	{
		SetWeight(a, b, value);
		_adj[a].push_back(b);
		_adj[b].push_back(a);
	}
	_edges.push_back(EdgeCell(a, b, value));
}

int Graph::Size()
{
	return _n;
}

// O(v)
void Graph::SetSource(int s)
{
	_distances.clear();
	for (int i = 0; i < _n; i++)
	{
		_distances.push_back(std::numeric_limits<int>::max());
		_pi.push_back(-1);
	}
	_distances[s] = 0;
}

// O(1)
bool Graph::Relax(int a, int b)
{
	if (_distances[b] > _distances[a] + _weights[a][b])
	{
		_distances[b] = _distances[a] + _weights[a][b];
		_pi[b] = a;
		return true;
	}
	return false;
}

// O(v*v)
bool Graph::BellmanFord(int s)
{
	// O(v)
	SetSource(s);

	// O(v*v)
	for (int i = 0; i < _n; i++)
		for (auto& e : _edges)
			Relax(e.source, e.destiny);

	// O(v)
	for (auto& e : _edges)
		if (_distances[e.destiny] > _distances[e.source] + _weights[e.source][e.destiny])
			return false;

	return true;
}

int Graph::GetDistance(int d)
{
	return _distances[d];
}

void Graph::PrintPath(int d)
{
	std::list<int> path;
	int vertice(d);
	while (vertice != -1)
	{
		path.push_front(vertice);
		vertice = _pi[vertice];
	}
	vertice = path.back();
	path.pop_back();
	for (auto& v : path)
		std::cout << v << "->";
	std::cout << vertice << "\n";
}

// O(v * v)
void Graph::Dijkstra(int s)
{
	// O(v)
	SetSource(s);

	std::set<int> path;
	Heap vertices(true);
	std::pair<int, int> p;

	// O(v)
	for (int i = 0; i < _n; i++)
		vertices.Add(i, _distances[i]);

	// Average O(v * v)
	while (!vertices.Empty())
	{
		// O(lgv)
		p = vertices.Pop();
		// O(lgv)
		path.insert(p.first);
		// O(v * lgv)
		for (auto& e : _adj[p.first])
			if (Relax(p.first, e))
				vertices.UpdateValue(e, _distances[e]);
	}
}

bool Graph::ValidEdge(int a, int b)
{
	return _distancesAllPairs[a][b] < std::numeric_limits<int>::max();
}

int Graph::AlternateWay(int i, int k, int j)
{
	if (ValidEdge(i, k) && ValidEdge(k, j))
		return _distancesAllPairs[i][k] + _distancesAllPairs[k][j];
	else
		return std::numeric_limits<int>::max();
}

// O(v**3)
void Graph::FloydMarshall()
{
	_distancesAllPairs.clear();
	for (auto& row : _weights)
		_distancesAllPairs.push_back(row);

	_piAllPairs.clear();
	for (int i = 0; i < Size(); i++)
	{
		std::vector<int> aux(Size(), -1);
		_piAllPairs.push_back(aux);
		for (int j = 0; j < Size(); j++)
			if (i != j && _weights[i][j] < std::numeric_limits<int>::max())
				_piAllPairs[i][j] = i;
	}

	int val;
	for (int k = 0; k < Size(); k++)
		for (int i = 0; i < Size(); i++)
			for (int j = 0; j < Size(); j++)
			{
				val = AlternateWay(i, k, j);
				if (val < _distancesAllPairs[i][j])
				{
					_distancesAllPairs[i][j] = val;
					_piAllPairs[i][j] = _piAllPairs[k][j];
				}
			}
}

int Graph::GetDistance(int s, int d)
{
	return _distancesAllPairs[s][d];
}

void Graph::PrintPath(int s, int d)
{
	if (s != d)
	{
		std::list<int> path;
		int i(d);

		do
		{
			path.push_front(i);
			i = _piAllPairs[s][i];
		} while (i != s);
		path.push_front(i);

		for (auto& v : path)
			if (v != path.back())
				std::cout << v << "->";
		std::cout << path.back() << "";
	}
	std::cout << "\n";
}

bool Graph::EdgeCompare(EdgeCell& x, EdgeCell& y)
{
	return x.weight < y.weight;
}

// O(e lgv)
std::list<EdgeCell> Graph::Kruskal()
{
	std::list<EdgeCell> A;
	Set S;

	// O(v)
	for (int v = 0; v < _weights.size(); v++)
		S.MakeSet(v);

	// O(elge) = O(e lgv)
	std::sort(_edges.begin(), _edges.end(), Graph::EdgeCompare);

	// O(e alpha(v)) = O(e lgv)
	for (auto& e : _edges)
		// O(alpha(v))
		if (S.FindSet(e.source) != S.FindSet(e.destiny))
		{
			A.push_back(e);
			// O(1)
			S.Union(e.source, e.destiny);
		}

	return A;
}

void Graph::PrintEdges()
{
	for (auto& e : _edges)
		std::cout << e.source << "->" << e.destiny << " = " << _weights[e.source][e.destiny] << "\n";
}