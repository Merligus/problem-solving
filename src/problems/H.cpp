#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Posicao
{
public:
	Posicao(std::string paiso, int o, int p, int b);

	void AtualizaMedalha(int m);

	int o, p, b;
	std::string pais;
};

Posicao::Posicao(std::string paiso, int oo, int po, int bo)
{
	o = oo;
	p = po;
	b = bo;
	pais = paiso;
}

void Posicao::AtualizaMedalha(int m)
{
	if (m == 1)
		o++;
	else if (m == 2)
		p++;
	else
		b++;
}

bool comparador(Posicao i, Posicao j)
{
	if (i.o > j.o)
		return true;
	else
	{
		if (j.o > i.o)
			return false;
		else
		{
			if (i.p > j.p)
				return true;
			else
			{
				if (j.p > i.p)
					return false;
				else
				{
					if (i.b > j.b)
						return true;
					else
					{
						if (j.b > i.b)
							return false;
						else
						{
							int ordem = i.pais.compare(j.pais);
							if (ordem < 0)
								return false;
							else
								return true;
						}
					}
				}
			}
		}
	}
}

void Tabela()
{
	int n, q;
	std::cin >> n >> q;

	std::vector<Posicao> tabela;
	std::unordered_map<std::string, int> colocacao;
	std::string pais;
	int o, p, b;
	for (int ni = 0; ni < n; ni++)
	{
		std::cin >> pais >> o >> p >> b;
		tabela.push_back(Posicao(pais, o, p, b));
	}
	std::sort(tabela.begin(), tabela.end(), comparador);

	for (int ni = 0; ni < 2; ni++)
		std::cout << tabela[ni].pais << " ";
	std::cout << tabela[2].pais << "\n";

	for (int ni = 0; ni < n; ni++)
		colocacao[tabela[ni].pais] = ni;

	int m;
	for (int qi = 0; qi < q; qi++)
	{
		std::cin >> pais >> m;
		int ni = colocacao[pais];
		tabela[ni].AtualizaMedalha(m);
		int index(ni - 1);
		while (index >= 0)
		{
			if (!comparador(tabela[index], tabela[index + 1]))
			{
				Posicao aux(tabela[index]);
				tabela[index] = tabela[index + 1];
				tabela[index + 1] = aux;

				colocacao[tabela[index + 1].pais] = index + 1;
				colocacao[tabela[index].pais] = index;
			}
			else
				break;
			index--;
		}

		for (ni = 0; ni < 2; ni++)
			std::cout << tabela[ni].pais << " ";
		std::cout << tabela[2].pais << "\n";
	}
}

int main_H()
{
	Tabela();
	return 0;
}