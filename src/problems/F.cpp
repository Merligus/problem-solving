#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

void Fila()
{
	int n, m, q;
	std::cin >> n >> m >> q;

	std::deque<int> emptyDeque;
	std::vector<std::deque<int>> fila(m + 1, emptyDeque);
	int pais;
	for (int ni = 1; ni <= n; ni++)
	{
		std::cin >> pais;
		fila[pais - 1].push_back(ni);
	}

	int s(1), e(n);
	int op, lugar, interval1, interval2;
	int si, ei;
	for (int qi = 0; qi < q; qi++)
	{
		// for (int ni = 0; ni < n; ni++)
		// {
		// 	std::cout << ni << ": ";
		// 	for (auto& pos : fila[ni])
		// 		std::cout << pos << " ";
		// 	std::cout << "\n";
		// }
		// std::cout << "FILA\n";

		std::cin >> op;
		if (op == 1)
		{
			std::cin >> lugar >> pais;
			if (lugar == -1)
				fila[pais - 1].push_front(--s);
			else
				fila[pais - 1].push_back(++e);
		}
		else
		{
			std::cin >> interval1 >> interval2 >> pais;

			si = interval1 - (1 - s);
			ei = interval2 - (1 - s);

			for (auto& v : fila[pais - 1])
				std::cout << v << " ";
			std::cout << ":\n";

			std::cout << std::upper_bound(fila[pais- 1].begin(), fila[pais- 1].end(), ei) - std::lower_bound(fila[pais- 1].begin(), fila[pais- 1].end(), si) << std::endl;
		}
	}
}

int main_F()
{
	Fila();
	return 0;
}