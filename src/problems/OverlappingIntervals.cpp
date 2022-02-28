#include <iostream>
#include <vector>

std::vector<std::pair<int, int>> Merge(std::vector<std::pair<int, int>> intervals)
{
	std::vector<std::pair<int, int>> out;
	for (auto& interval : intervals)
	{
		if (!out.empty() && out.back().second >= interval.first)
			out.back().second = interval.second;
		else
			out.push_back(interval);
	}
	return out;
}

int main_OverlappingIntervals()
{
	std::vector<std::pair<int, int>> test({ {1, 4}, {4, 5}, {4, 6}, {6, 10}, {15, 18} });
	std::vector<std::pair<int, int>> out;

	out = Merge(test);
	for (auto& interval : out)
		std::cout << interval.first << ":" << interval.second << " ";
	std::cout << "\n";
	return 0;
}