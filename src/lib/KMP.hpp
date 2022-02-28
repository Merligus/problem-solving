#include <iostream>
#include <vector>

std::vector<int> ComputePrefixFunction(std::string P)
{
	int m = P.length();
	std::vector<int> pi;
	pi.push_back(0);
	int k = 0;
	for (int q = 1; q < P.length(); q++)
	{
		while (k > 0 && P[k] != P[q])
			k = pi[k];
		if (P[k] == P[q])
			k++;
		pi.push_back(k);
	}
	return pi;
}

void KMP(std::string T, std::string P)
{
	int n = T.length();
	int m = P.length();
	std::vector<int> pi = ComputePrefixFunction(P);
	std::cout << P;
	for (int& p : pi)
		std::cout << p << " ";
	std::cout << "\n";
	int q = 0;
	for (int index = 0; index < n; index++)
	{
		while (q > 0 && P[q] != T[index])
			q = pi[q];
		if (P[q] == T[index])
			q++;
		if (q == m)
		{
			std::cout << "Pattern at shift " << index + 1 - m << '\n';
			q = pi[q - 1.0];
		}
	}
}

int test()
{
	std::string T("aababacababacacababacababaca");
	std::string P("ababaca");

	KMP(T, P);

	return 0;
}