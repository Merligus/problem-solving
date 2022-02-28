#include <iostream>
#include <cmath>

int Play(int n)
{
	int games(n - 1);
	int max = (int)std::sqrt(n);
	for (int k = 2; k <= max; k++)
	{
		if (n % k == 1)
		{
			games--;
			if ((n - 1) / k != k)
				games--;
		}
	}
	return games;
}

int main_J()
{
	int n;
	std::cin >> n;
	std::cout << Play(n) << std::endl;

	return 0;
}
