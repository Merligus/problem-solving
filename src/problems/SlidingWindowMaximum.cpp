#include <iostream>
#include <vector>
#include <queue>
#include "../lib/Heap.hpp"

std::vector<int> slidingMaximum(const std::vector<int>& A, int B)
{
	Heap h(false);
	std::vector<int> C;

	for (int i = 0; i < B && i < A.size(); i++)
		h.Add(i, A[i]);
	C.push_back(h.Front());

	for (int i = B; i < A.size(); i++)
	{
		h.Delete(i - B);
		h.Add(i, A[i]);
		C.push_back(h.Front());
	}

	return C;
}

int main_SlidingWindowMaximum()
{
	// int test[] = { 1, 3, -1, -3, 5, 3, 6, 7 };
	// int test[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
	// int test[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int test[] = { 90, 943, 777, 658, 742, 559, 623, 263, 880, 176, 354, 434, 699, 501, 551, 821, 563, 974, 701, 479, 238, 87, 61, 910, 204, 534, 369, 845, 566, 19, 939, 87, 708, 323, 662, 32, 655, 835, 67, 360, 550, 173, 488, 420, 680, 805, 630, 48, 791, 991, 791, 819, 772, 228, 123, 303, 642, 780, 115, 89, 919, 830, 271, 853, 588, 249, 20, 940, 851, 749, 340, 587, 235, 106, 125, 32, 319, 590, 354, 751, 761, 564, 484, 51, 202, 370, 216, 130, 146, 632};
	std::vector<int> A(test, test + sizeof(test) / sizeof(int)), C;

	C = slidingMaximum(A, 6);
	for (auto& c : C)
		std::cout << c << " ";

	return 0;
}
