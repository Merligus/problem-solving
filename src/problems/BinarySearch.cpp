#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void find_closest_element(std::vector<int> arr, int k, int x)
{
	std::vector<int> out;
	std::vector<int>::iterator first_it;
	// O(lgn)
	first_it = std::lower_bound(arr.begin(), arr.end(), x);
	int first_index = first_it - arr.begin();

	// valid
	if (first_index < arr.size())
	{
		int left = first_index - 1;
		int right = first_index;
		int diff_l, diff_r;
		bool copy_right(false), copy_left(false);
		int i;

		// O(k)
		for (i = 0; i < k; i++)
		{
			if (left > -1)
				diff_l = std::abs(x - arr[left]);
			else
			{
				copy_right = true;
				break;
			}
			if (right < arr.size())
				diff_r = std::abs(x - arr[right]);
			else
			{
				copy_left = true;
				break;
			}

			// left is closer to x
			if (diff_l < diff_r)
				left--;
			else // right is closer to x
				right++;
		}

		if (copy_right)
			right += k - i;
		if (copy_left)
			left -= k - i;

		for (i = left + 1; i < right; i++)
			std::cout << arr[i] << " ";
	}
	else // x is higher than the max number in arr, so..
	{
		std::cout << "Output: ";
		for (int i = arr.size() - k; i < arr.size(); i++)
			std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int main_BinarySearch()
{
	int test[] = { 0, 10, 20, 30, 40, 50, 60 };
	std::vector<int> test_vec(test, test + sizeof(test) / sizeof(int));
	find_closest_element(test_vec, 4, 21);

	return 0;
}