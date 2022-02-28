#include <iostream>
#include <vector>

void StartPath(std::vector<std::vector<char>>& A, int lin, int col)
{
	if (A[lin][col] == 'O')
	{
		A[lin][col] = 'K';
		if (col - 1 >= 0)
			StartPath(A, lin, col - 1);
		if (col + 1 < A[0].size())
			StartPath(A, lin, col + 1);
		if (lin - 1 >= 0)
			StartPath(A, lin - 1, col);
		if (lin + 1 < A.size())
			StartPath(A, lin + 1, col);
	}
}

void solve(std::vector<std::vector<char>>& A)
{
	for (int col = 0; col < A[0].size(); col++)
	{
		StartPath(A, 0, col);
		StartPath(A, A.size() - 1, col);
	}

	for (int lin = 0; lin < A.size(); lin++)
	{
		StartPath(A, lin, 0);
		StartPath(A, lin, A[0].size() - 1);
	}

	for (int lin = 0; lin < A.size(); lin++)
	{
		for (int col = 0; col < A[0].size(); col++)
		{
			if (A[lin][col] == 'O')
				A[lin][col] = 'X';
			else if (A[lin][col] == 'K')
				A[lin][col] = 'O';
		}
	}
}


int main_2DTable()
{
	// char test[][4] = {
	// 					{'X', 'X', 'X', 'X'},
	// 					{'X', 'O', 'O', 'X'},
	// 					{'X', 'X', 'O', 'X'},
	// 					{'X', 'O', 'X', 'X'}
	// 				};
	char test[][7] = {
						{'O', 'O', 'O', 'X', 'X', 'X', 'O'},
						{'X', 'X', 'X', 'O', 'X', 'O', 'O'},
						{'X', 'X', 'O', 'X', 'O', 'X', 'O'},
						{'O', 'X', 'O', 'X', 'O', 'X', 'O'},
						{'X', 'X', 'O', 'X', 'O', 'X', 'X'},
						{'X', 'O', 'O', 'O', 'X', 'X', 'O'},
						{'O', 'X', 'X', 'O', 'X', 'O', 'O'},
						{'O', 'X', 'O', 'O', 'X', 'O', 'X'}
					};
	std::vector<std::vector<char>> A;
	for (auto& line : test)
	{
		std::vector<char> a(line, line + sizeof(line) / sizeof(char));
		A.push_back(a);
	}

	for (auto& line : A)
	{
		for (auto& num : line)
			std::cout << num << " ";
		std::cout << "\n";
	}

	solve(A);
	std::cout << A.size() << " " << A[0].size() << "\n";

	for (auto& line : A)
	{
		for (auto& num : line)
			std::cout << num << " ";
		std::cout << "\n";
	}

	return 0;
}