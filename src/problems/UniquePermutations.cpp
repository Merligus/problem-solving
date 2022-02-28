#include <iostream>
#include <vector>
#include <unordered_map>

int UpdateCode(std::vector<int>& A, int i, int j, int old)
{
	int num1, num2;

	num1 = A[i];
	num2 = A[j];

	old -= std::pow(10, i) * num1;
	old -= std::pow(10, j) * num2;
	old += std::pow(10, i) * num2;
	old += std::pow(10, j) * num1;

	A[i] = num2;
	A[j] = num1;

	return old;
}

void FindPermutations(std::vector<int>& A, std::vector<std::vector<int>>& B, std::unordered_map<int, bool>& checkList, int index, int code)
{
	std::unordered_map<int, bool>::const_iterator finder;
	for (int j = 0; j < A.size(); j++)
	{
		if (index != j)
		{
			code = UpdateCode(A, index, j, code);
			finder = checkList.find(code);
			if (finder == checkList.end()) // not in
			{
				checkList[code] = true;
				B.push_back(A);
				FindPermutations(A, B, checkList, index, code);
			}
			code = UpdateCode(A, index, j, code); // turn it back
		}
	}
}

std::vector<std::vector<int>> permute(std::vector<int>& A)
{
	std::unordered_map<int, bool> checkList;
	std::vector<std::vector<int>> B;
	int n(0), dec(1);
	for (auto& num : A)
	{
		n += dec * num;
		dec *= 10;
	}
	B.push_back(A);
	checkList[n] = true;

	FindPermutations(A, B, checkList, 0, n);

	return B;
}

int main_UniquePermutations()
{
	int test[] = { 0, 0, 0, 1, 9 };
	std::vector<int> v(test, test + 5);

	std::vector<std::vector<int>> A;
	A = permute(v);
	for (auto& row : A)
	{
		for (auto& r : row)
			std::cout << r << " ";
		std::cout << "\n";
	}

	return 0;
}
