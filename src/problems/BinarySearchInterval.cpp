#include <iostream>
#include <algorithm>
#include <vector>

// O(3lgn)
std::pair<int, int> FindLowHighIndex(std::vector<int> arr, int value)
{
	std::pair<int, int> tuple(-1, -1);
	std::vector<int>::iterator left, right;

	// O(lgn)
	if (std::binary_search(arr.begin(), arr.end(), value))
	{
		// O(lgn)
		left = std::lower_bound(arr.begin(), arr.end(), value);
		tuple.first = left - arr.begin();

		// O(lgn)
		right = std::upper_bound(arr.begin(), arr.end(), value);
		tuple.second = right - arr.begin() - 1;
	}
	return tuple;
}

int main_BinarySearchInterval()
{
	int test[] = { 5, 7, 7, 8, 8, 10 };
	std::vector<int> test_v(test, test + sizeof(test) / sizeof(int));
	std::pair<int, int> tuple(-1, -1);
	
	for (int key = 0; key <= 11; key++)
	{
		tuple = FindLowHighIndex(test_v, key);
		std::cout << key << " " << tuple.first << ":" << tuple.second << std::endl;
	}
	return 0;
}