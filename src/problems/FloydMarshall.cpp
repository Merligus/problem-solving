#include "../lib/Graph.hpp"

int main_FloydMarshall()
{

//5 9
//0 1 3
//0 2 8
//0 4 -4
//1 3 1
//1 4 7
//2 1 4
//3 0 2
//3 2 -5
//4 3 6


	int n, e;
	std::cin >> n >> e;

	Graph g(n);
	for (int i = 0; i < e; i++)
	{
		int u, v, val;
		std::cin >> u >> v >> val;
		g.AddWeight(u, v, val, true);
	}

	g.FloydMarshall();
	for (int s = 0; s < g.Size(); s++)
	{
		std::cout << "From " << s << "\n";
		for (int d = 0; d < g.Size(); d++)
		{
			std::cout << "\tto " << d << " = " << g.GetDistance(s, d) << " ";
			g.PrintPath(s, d);
		}
	}

	return 0;
}