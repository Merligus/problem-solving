#include <iostream>
#include <vector>
#include <random>
#include <stdlib.h>

class Matrix
{ 
public:
	int rows, cols;
	Matrix();

	void resize(int rows, int cols); 

	void incrementIfNotMine(int r, int c);
	bool putMines(int nMines, int r, int c);
	void reveal(int r, int c);
	void show();
	bool lost();
	bool won();

private:
	std::vector<std::vector<int>> _matrix;
	std::vector<std::vector<bool>> _hidden;
	bool bLost;
	int countRevealed;
	int mines;
};

Matrix::Matrix()
{
	rows = 0;
	cols = 0;
	countRevealed = 0;
	bLost = false;
}


void Matrix::resize(int rows, int cols)
{
	_matrix.clear();
	_hidden.clear();
	this->rows = rows;
	this->cols = cols;

	std::vector<int> matrixRow;
	std::vector<bool> hiddenRow;
	for (int c = 0; c < cols; c++)
	{
		matrixRow.push_back(0);
		hiddenRow.push_back(true);
	}

	for (int r = 0; r < rows; r++)
	{
		_matrix.push_back(matrixRow);
		_hidden.push_back(hiddenRow);
	}
}

void Matrix::incrementIfNotMine(int r, int c)
{
	if (r >= 0 && r < rows)
		if (c >= 0 && c < cols)
			if (_matrix[r][c] < 9)
				_matrix[r][c]++;
}

bool Matrix::putMines(int nMines, int r, int c)
{
	if (nMines <= 0 || nMines > rows * cols)
		return false;

	if (r < 0 || r >= rows || c < 0 || c >= cols)
		return false;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, (rows - 1) * (cols - 1));

	mines = nMines;
	int minesAlreadyPlaced(0);
	while (minesAlreadyPlaced < nMines)
	{
		int number = distribution(generator);
		int row = (int)(number / (cols - 1));
		int col = number % (cols - 1);
		// not a mine and not close to the first revelation
		if (_matrix[row][col] < 9 && abs(row - r) > 1 && abs(col - c) > 1)
		{
			minesAlreadyPlaced++;
			_matrix[row][col] = 9;

			incrementIfNotMine(row - 1, col - 1);
			incrementIfNotMine(row - 1, col);
			incrementIfNotMine(row - 1, col + 1);

			incrementIfNotMine(row, col - 1);
			incrementIfNotMine(row, col + 1);

			incrementIfNotMine(row + 1, col - 1);
			incrementIfNotMine(row + 1, col);
			incrementIfNotMine(row + 1, col + 1);
		}
	}
	return true;
}

void Matrix::reveal(int r, int c)
{
	if (r >= 0 && r < rows)
		if (c >= 0 && c < cols)
			if (_hidden[r][c])
			{
				_hidden[r][c] = false;
				countRevealed++;
				if (_matrix[r][c] == 9)
					bLost = true;
				else if (_matrix[r][c] == 0)
				{
					reveal(r - 1, c - 1);
					reveal(r - 1, c);
					reveal(r - 1, c + 1);

					reveal(r, c - 1);
					reveal(r, c + 1);

					reveal(r + 1, c - 1);
					reveal(r + 1, c);
					reveal(r + 1, c + 1);
				}
			}
}

void Matrix::show()
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (!_hidden[r][c])
				std::cout << _matrix[r][c] << '\t';
			else
				std::cout << '-' << '\t';
		}
		std::cout << '\n';
	}
}

bool Matrix::lost()
{
	return bLost;
}

bool Matrix::won()
{
	if (bLost)
		return false;
	else
		return (countRevealed + mines) == (rows * cols);
}

int main_Minesweeper()
{
	Matrix Mine;

	std::cin >> Mine.rows >> Mine.cols;
	Mine.resize(Mine.rows, Mine.cols);
	Mine.show();

	int r, c;
	std::cin >> r >> c;
	while (!Mine.putMines(5, r, c))
		std::cin >> r >> c;
	Mine.reveal(r, c);

	while(!(Mine.lost() || Mine.won()))
	{
		Mine.show();
		std::cin >> r >> c;
		Mine.reveal(r, c);
	}
	
	Mine.show();
	if (Mine.lost())
		std::cout << "GAME OVER!\n";
	else
		std::cout << "CONGRATULATIONS!\n";

	return 0;
}
