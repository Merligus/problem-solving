#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <unordered_map>

class Graph
{
public:
	Graph(std::string s, std::vector<std::string> d, std::string e);

	std::vector<std::string> vertices;
	std::vector<std::list<int>> adj;

	int destiny;
	int lowestDistance;
	std::vector<std::vector<std::string>> paths;

private:
	std::unordered_map<std::string, int> _alreadyCreated;

	int Compare(std::string s1, std::string s2)
	{
		int diff(0);
		for (int i = 0; i < s1.size(); i++)
			if (s1[i] != s2[i])
				diff++;
		return diff;
	}
};

Graph::Graph(std::string s, std::vector<std::string> d, std::string e)
{
	std::unordered_map<std::string, int>::const_iterator finder;
	std::list<int> emptyList;
	int counter(0);
	lowestDistance = std::numeric_limits<int>::max();

	_alreadyCreated[s] = counter++;
	vertices.push_back(s);
	adj.push_back(emptyList);
	for (auto& s : d)
	{
		finder = _alreadyCreated.find(s);
		if (finder == _alreadyCreated.end())
		{
			_alreadyCreated[s] = counter++;
			vertices.push_back(s);
			adj.push_back(emptyList);
		}
	}
	finder = _alreadyCreated.find(e);
	if (finder != _alreadyCreated.end())
	{
		destiny = finder->second;
	}
	else
	{
		vertices.push_back(e);
		adj.push_back(emptyList);
		destiny = vertices.size() - 1;
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		for (int j = i + 1; j < vertices.size(); j++)
		{
			if (Compare(vertices[i], vertices[j]) == 1)
			{
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
	}
}

void FindPath(Graph& g, int vertice, std::vector<bool> visited, int distance, std::vector<std::string> path)
{
	visited[vertice] = true; // visited
	path.push_back(g.vertices[vertice]);
	if (vertice == g.destiny && distance <= g.lowestDistance)
	{
		if (distance < g.lowestDistance)
		{
			g.paths.clear();
			g.lowestDistance = distance;
		}
		g.paths.push_back(path);
	}
	else
	{
		for (auto& neighbor : g.adj[vertice])
		{
			if (!visited[neighbor]) // not visited
				FindPath(g, neighbor, visited, distance + 1, path);
		}
	}
}

std::vector<std::vector<std::string>> findLadders(std::string start, std::string end, std::vector<std::string>& dict)
{
	Graph g(start, dict, end);
	std::vector<bool> visited(dict.size() + 2, false);
	std::vector<std::string> path;

	FindPath(g, 0, visited, 0, path);
	return g.paths;
}

int main_WordLadder()
{
	std::string s, start, end;
	std::vector<std::string> dict;
	std::vector<std::vector<std::string>> paths;
	int n;

	std::cin >> n;
	for (int i = 0; i < n - 2; i++)
	{
		std::cin >> s;
		dict.push_back(s);
	}
	std::cin >> start;
	std::cin >> end;

	paths = findLadders(start, end, dict);

	for (auto& path : paths)
	{
		for (auto& s : path)
			std::cout << s << " ";
		std::cout << "\n";
	}

	return 0;
}