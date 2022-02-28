#include <iostream>
#include <limits>

int main_DiameterGraph()
{
	int testCases;
	int n, m, k;
	int diameter;
	std::cin >> testCases;
	for (int i = 0; i < testCases; i++)
	{
		std::cin >> n >> m >> k;
		if (m < n - 1)
			diameter = std::numeric_limits<int>::max();
		else if (m < n * (n - 1) / 2)
			diameter = 2;
		else
			diameter = 1;

		if (diameter < k - 1)
			std::cout << "Yes\n";
		else
			std::cout << "No\n";
	}

	return 0;
}