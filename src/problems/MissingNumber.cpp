#include <iostream>
#include <vector>

int Missing(std::vector<int> arr)
{
	int sum(0);
	for (auto& num : arr)
		sum += num;

	return arr.size() * (arr.size() + 1) / 2 - sum;
}

int main_MissingNumber()
{
	int test[] = {0, 2, 3, 1};
	std::vector<int> arr(test, test + sizeof(test) / sizeof(int));
	std::cout << Missing(arr) << "\n";

	return 0;
}