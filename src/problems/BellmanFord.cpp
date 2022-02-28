#include "../lib/Graph.hpp"

int main()
{

 /*5 10
 0 1 6
 0 2 7
 1 2 8
 1 3 5
 1 4 -4
 2 3 -3
 2 4 9
 3 1 -2
 4 3 7
 4 0 2*/

	int n, e;
	std::cin >> n >> e;
	
	Graph g(n);
	for (int i = 0; i < e; i++)
	{
		int u, v, val;
		std::cin >> u >> v >> val;
		g.AddWeight(u, v, val, true);
	}
	
	if (g.BellmanFord(0))
	{
		std::cout << "No negative loop\n";
		for (int d = 0; d < g.Size(); d++)
		{
			std::cout << "To " << d << " = " << g.GetDistance(d) << "\n";
			g.PrintPath(d);
		}

	}
	else
		std::cout << "There is a negative loop\n";

	return 0;
}