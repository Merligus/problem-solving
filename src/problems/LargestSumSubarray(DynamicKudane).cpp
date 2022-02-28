#include <iostream>
#include <vector>
#include <algorithm>

void FindLargestSubarray(std::vector<int> in_vec)
{
	int local, global, start_l, start, end;
	std::vector<int> global_vec;

	local = global = in_vec[0];
	start = start_l = end = 0;
	for (int i = 1; i < in_vec.size(); i++)
	{
		if (local > 0)
			local += in_vec[i];
		else
		{
			local = in_vec[i];
			start_l = i;
		}

		if (local > global)
		{
			global = local;
			start = start_l;
			end = i;
		}
	}

	for (int i = start; i <= end; i++)
		std::cout << in_vec[i] << " ";
	std::cout << "\n";
}

int main_LargestSumSubarray()
{
	int test[] = { 8, -6, 1, 4, -1, 2, 1, -5, 4 };
	std::vector<int> in_vec, out;
	for (auto& num : test)
		in_vec.push_back(num);

	FindLargestSubarray(in_vec);

	return 0;
}
