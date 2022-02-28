#include <iostream>
#include <vector>
#include <unordered_map>

bool find_sum_of_two(std::vector<int> A, int val)
{
	std::unordered_map<int, unsigned> number_set;
	std::unordered_map<int, unsigned>::const_iterator key_in;

	for (auto& num : A)
	{
		key_in = number_set.find(num);
		if (key_in != number_set.end())
			++number_set.at(num);
		else
			number_set.insert({ num, 1 });
	}
	for (auto& num : A)
	{
		// key_in = number_set.find(num);
		// std::cout << key_in->first << ":" << key_in->second << std::endl;
		--number_set.at(num);
		key_in = number_set.find(val - num);
		if (key_in != number_set.end())
			if (key_in->second > 0)
				return true;
		++number_set.at(num);
	}

	return false;
}

int main_Hash()
{
	int test[] = { 2, 7, 11, 15, 2, 15};
	std::vector<int> test_vec(test, test + sizeof(test) / sizeof(int));

	std::string result;
	for (int i = 0; i <= 30; i++)
	{
		std::cout << "Val: " << i << " ";
		if (find_sum_of_two(test_vec, i))
			result = "Yes\n";
		else
			result = "No\n";

		std::cout << result;
	}
	return 0;
}
