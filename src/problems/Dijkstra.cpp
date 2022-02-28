#include "../lib/Graph.hpp"

int main_Dijkstra()
{

//5 10
//0 1 10
//0 2 5
//1 2 2
//1 3 1
//2 1 3
//2 3 9
//2 4 2
//3 4 4
//4 3 6
//4 0 7


	int n, e;
	std::cin >> n >> e;

	Graph g(n);
	for (int i = 0; i < e; i++)
	{
		int u, v, val;
		std::cin >> u >> v >> val;
		g.AddWeight(u, v, val, true);
	}

	g.Dijkstra(0);
	for (int d = 0; d < g.Size(); d++)
	{
		std::cout << "To " << d << " = " << g.GetDistance(d) << "\n";
		g.PrintPath(d);
	}

	return 0;
}
