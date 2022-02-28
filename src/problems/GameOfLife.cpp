#include <iostream>
#include <vector>

using namespace std;

int gameOfLifeRec(vector<vector<int>>& board, vector<vector<int>>& oldBoard, int row, int col)
{
    if (row >= 0 && row < board.size())
    {
        if (col >= 0 && col < board[0].size())
        {
            if (oldBoard[row][col] == -1)
            {
                oldBoard[row][col] = board[row][col];

                int count(0);

                count += gameOfLifeRec(board, oldBoard, row - 1, col - 1);
                count += gameOfLifeRec(board, oldBoard, row - 1, col);
                count += gameOfLifeRec(board, oldBoard, row - 1, col + 1);

                count += gameOfLifeRec(board, oldBoard, row, col - 1);
                count += gameOfLifeRec(board, oldBoard, row, col + 1);

                count += gameOfLifeRec(board, oldBoard, row + 1, col - 1);
                count += gameOfLifeRec(board, oldBoard, row + 1, col);
                count += gameOfLifeRec(board, oldBoard, row + 1, col + 1);
                if (board[row][col] == 1)
                {
                    if (count < 2)
                    {
                        board[row][col] = 0;
                    }
                    else if (count < 4)
                    {
                        board[row][col] = 1;
                    }
                    else
                    {
                        board[row][col] = 0;
                    }
                }
                else if (count == 3)
                    board[row][col] = 1;

            }
            return oldBoard[row][col];
        }
        else
            return 0;
    }
    else
        return 0;
}

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board)
    {
        // -1 if not row,col not updated in board
        // 0, 1 if board is already updated
        vector<vector<int>> oldBoard;
        for (int i = 0; i < board.size(); i++)
        {
            vector<int> empty(board[0].size(), -1);
            oldBoard.push_back(empty);
        }

        gameOfLifeRec(board, oldBoard, 0, 0);
    }
};

int main_GameOfLife()
{

//4 3
//0 1 0
//0 0 1
//1 1 1
//0 0 0

    std::vector<std::vector<int>> board;
    Solution s;

    int m, n;
    std::cin >> m >> n;
    for (int i = 0; i < m; i++)
    {
        board.push_back(std::vector<int>(n, -1));
        for (int j = 0; j < n; j++)
            std::cin >> board[i][j];
    }

    s.gameOfLife(board);

    for (auto& row : board)
    {
        for (auto& value : row)
            std::cout << value << " ";
        std::cout << "\n";
    }

    return 0;
}
