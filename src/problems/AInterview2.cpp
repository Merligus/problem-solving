#include <iostream>
#include <vector>

using namespace std;

bool Verify(std::vector<int> A, int i, int j)
{
	return std::abs(i - j) == std::abs(A[i] - A[j]);
}

int Find(std::vector<int> A, int s, int e, std::vector<std::vector<int>>& D)
{
	if (D[s][e] != -1)
		return D[s][e];
	else if (s <= e)
	{
		if (Verify(A, s, e))
			D[s][e] = std::abs(s - e);
		else
		{
			int maxAux1(-1), maxAux2(-1), maxAux3(-1);
			if (s + 1 <= e)
				maxAux1 = Find(A, s + 1, e, D);
			if (s <= e - 1)
				maxAux2 = Find(A, s, e - 1, D);
			if (s + 1 <= e - 1)
				maxAux3 = Find(A, s + 1, e - 1, D);
			D[s][e] = std::max(std::max(maxAux1, maxAux2), maxAux3);
		}
		return D[s][e];
	}

	return 0;
}

int solution(vector<int> A) {
	std::vector<int> aux(A.size(), -1);
	std::vector<std::vector<int>> D(A.size(), aux);

	return Find(A, 0, A.size() - 1, D);
}


int main_AInterview2()
{
	int test1[] = { 2, 2, 2, 1 };
	int test2[] = { 2, 4, 6, 7, 4, 7, 2 };
	int test3[] = { 100, 100, 100 };
	int test4[] = { 1000000000 };

	std::vector<int> test_v1(test1, test1 + sizeof(test1) / sizeof(int));
	std::vector<int> test_v2(test2, test2 + sizeof(test2) / sizeof(int));
	std::vector<int> test_v3(test3, test3 + sizeof(test3) / sizeof(int));
	std::vector<int> test_v4(test4, test4 + sizeof(test4) / sizeof(int));

	std::cout << solution(test_v1) << std::endl;
	std::cout << solution(test_v2) << std::endl;
	std::cout << solution(test_v3) << std::endl;
	std::cout << solution(test_v4) << std::endl;

	return 0;
}