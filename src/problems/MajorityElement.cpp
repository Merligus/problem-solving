#include <iostream>
#include <unordered_map>
#include <vector>

// elemento que mais aparece
int majorityElement(const std::vector<int>& A)
{
	std::pair<int, int> best(-1, -1);
	std::unordered_map<int, int> qtty;
	std::unordered_map<int, int>::const_iterator finder;
	for (auto& a : A)
	{
		finder = qtty.find(a);
		if (finder != qtty.end()) // already in
		{
			qtty[a] += 1;
		}
		else
			qtty[a] = 1;
		if (qtty[a] > best.first)
		{
			best.first = qtty[a];
			best.second = a;
		}
	}

	return best.second;
}

int main_MajorityElement()
{
	int test[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	std::vector<int> A(test, test + 8);
	std::cout << majorityElement(A) << std::endl;

	return 0;
}