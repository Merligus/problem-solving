#include "../lib/Graph.hpp"

bool myfunction(std::pair<int, int> i, std::pair<int, int> j) { return (i.first < j.first); }

int main_Kruskal()
{

//9 14
//0 1 4
//0 2 8
//1 2 11
//1 3 8
//2 4 7
//2 5 1
//3 4 2
//3 8 4
//3 6 7
//4 5 6
//5 8 2
//6 7 9
//6 8 14
//7 8 10

	std::pair<int, int> arr[] = { {32, 1},{71, 2},{12, 3},{45, 4},{26, 1},{80, 1},{53, 1}, {33, 1} };
	std::vector<std::pair<int, int>> v(arr, arr + 8);

	int n, e;
	std::cin >> n >> e;
	Graph g(n);

	for (int i = 0; i < e; i++)
	{
		int v1, v2, weight;
		std::cin >> v1 >> v2 >> weight;
		g.AddWeight(v1, v2, weight);
	}

	std::list<EdgeCell> l = g.Kruskal();
	for (auto& li : l)
		std::cout << li.source << ":" << li.destiny << "=" << li.weight << " ";
	std::cout << "\n";

	std::sort(v.begin(), v.end(), myfunction);

	for (auto& vi : v)
		std::cout << vi.first << ":" << vi.second << " ";
	std::cout << std::endl;

	return 0;
}