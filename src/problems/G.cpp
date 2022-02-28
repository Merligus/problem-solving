#include <iostream>
#include <vector>

std::string Joga(int n)
{
	std::string pontuador;
	std::vector<int> sets(2, 0), pontos(2, 0);
	while (n-- > 0)
	{
		std::cin >> pontuador;
		if (pontuador.length() == 1)
			pontos[0]++; // L
		else
			pontos[1]++; // Kira

		if (std::abs(pontos[1] - pontos[0]) >= 2 && std::max(pontos[0], pontos[1]) >= 4)
		{
			if (pontos[0] > pontos[1])
			{
				sets[0]++;
			}
			else
			{
				sets[1]++;
			}
			pontos[0] = pontos[1] = 0;
		}
	}

	if (sets[0] > sets[1])
		return "L eh melhor que Kira!!!";
	else
		return "Kira eh melhor que L!!!";
}

int main_G()
{
	int n;
	std::cin >> n;
	std::cout << Joga(n) << std::endl;

	return 0;
}