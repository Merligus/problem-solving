// 1210
#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

#define INF numeric_limits<int>::max()

class Position
{
public:
    int r, c;
    bool horizontal;
    int moves;

    Position(int ri, int ci, bool h);
};

Position::Position(int ri, int ci, bool h)
{
    r = ri;
    c = ci;
    horizontal = h;

    moves = 0;
}

bool CanMoveRight(vector<vector<int>> grid, Position p)
{
    if (p.horizontal)
    {
        if (p.c + 2 < grid[0].size())
            if (grid[p.r][p.c + 2] != 1)
                return true;
    }
    else
    {
        if (p.c + 1 < grid[0].size())
            if (grid[p.r][p.c + 1] != 1 && grid[p.r + 1][p.c + 1] != 1)
                return true;
    }
    return false;
}

void MoveRight(Position& p)
{
    p.c++;
    p.moves++;
}

bool CanMoveDown(vector<vector<int>> grid, Position p)
{
    if (p.horizontal)
    {
        if (p.r + 1 < grid.size())
            if (grid[p.r + 1][p.c] != 1 && grid[p.r + 1][p.c + 1] != 1)
                return true;
    }
    else
    {
        if (p.r + 2 < grid.size())
            if (grid[p.r + 2][p.c] != 1)
                return true;
    }
    return false;
}

void MoveDown(Position& p)
{
    p.r++;
    p.moves++;
}

bool CanRotateClockwise(vector<vector<int>> grid, Position p)
{
    if (p.horizontal)
        if (p.r + 1 < grid.size()) // valid
            if (grid[p.r + 1][p.c] != 1 && grid[p.r + 1][p.c + 1] != 1) // are empty
                return true;
    return false;
}

bool CanRotateCounterClockwise(vector<vector<int>> grid, Position p)
{
    if (!p.horizontal)
        if (p.c + 1 < grid.size()) // valid
            if (grid[p.r][p.c + 1] != 1 && grid[p.r + 1][p.c + 1] != 1) // are empty
                return true;
    return false;
}

void Rotate(Position& p)
{
    p.horizontal = !p.horizontal;
    p.moves++;
}

bool Reached(int n, Position p)
{
    int r1(p.r), c1(p.c), r2, c2;
    if (p.horizontal)
    {
        r2 = p.r;
        c2 = p.c + 1;
    }
    else
    {
        r2 = p.r + 1;
        c2 = p.c;
    }

    if (r1 == n - 1)
        if (r2 == n - 1)
            if (c1 == n - 2)
                if (c2 == n - 1)
                    return true;
    return false;
}

class Solution
{
public:
    int minimumMoves(vector<vector<int>>& grid)
    {
        vector<vector<pair<int, int>>> visited;
        queue<Position> BFS;
        Position current(0, 0, true);

        BFS.push(current);

        vector<pair<int, int>> row;
        for (int i = 0; i < grid[0].size(); i++)
            row.push_back({ INF, INF });

        for (int i = 0; i < grid.size(); i++)
            visited.push_back(row);

        visited[0][0].first = 0;

        while (!BFS.empty())
        {
            current = BFS.front();
            BFS.pop();

            if (Reached(grid.size(), current))
                return current.moves;
            else
            {
                bool bCanMoveRight(false);
                if (current.horizontal)
                {
                    if (current.c + 2 < grid[0].size())
                        if (grid[current.r][current.c + 2] != 1)
                            bCanMoveRight = true;
                }
                else
                {
                    if (current.c + 1 < grid[0].size())
                        if (grid[current.r][current.c + 1] != 1 && grid[current.r + 1][current.c + 1] != 1)
                            bCanMoveRight = true;
                }
                if (bCanMoveRight)
                {
                    Position nextPosition(current);
                    MoveRight(nextPosition);

                    if (nextPosition.horizontal)
                    {
                        if (visited[nextPosition.r][nextPosition.c].first == INF)
                        {
                            visited[nextPosition.r][nextPosition.c].first = nextPosition.moves;
                            BFS.push(nextPosition);
                        }
                    }
                    else
                    {
                        if (visited[nextPosition.r][nextPosition.c].second == INF)
                        {
                            visited[nextPosition.r][nextPosition.c].second = nextPosition.moves;
                            BFS.push(nextPosition);
                        }
                    }
                }

                bool bCanMoveDown(false);
                if (current.horizontal)
                {
                    if (current.r + 1 < grid.size())
                        if (grid[current.r + 1][current.c] != 1 && grid[current.r + 1][current.c + 1] != 1)
                            bCanMoveDown = true;
                }
                else
                {
                    if (current.r + 2 < grid.size())
                        if (grid[current.r + 2][current.c] != 1)
                            bCanMoveDown = true;
                }
                if (bCanMoveDown)
                {
                    Position nextPosition(current);
                    MoveDown(nextPosition);
                    
                    if (nextPosition.horizontal)
                    {
                        if (visited[nextPosition.r][nextPosition.c].first == INF)
                        {
                            visited[nextPosition.r][nextPosition.c].first = nextPosition.moves;
                            BFS.push(nextPosition);
                        }
                    }
                    else
                    {
                        if (visited[nextPosition.r][nextPosition.c].second == INF)
                        {
                            visited[nextPosition.r][nextPosition.c].second = nextPosition.moves;
                            BFS.push(nextPosition);
                        }
                    }
                }

                if (current.horizontal)
                    if (current.r + 1 < grid.size()) // valid
                        if (grid[current.r + 1][current.c] != 1 && grid[current.r + 1][current.c + 1] != 1) // are empty
                        {
                            Position nextPosition(current);
                            Rotate(nextPosition);
                    
                            if (nextPosition.horizontal)
                            {
                                if (visited[nextPosition.r][nextPosition.c].first == INF)
                                {
                                    visited[nextPosition.r][nextPosition.c].first = nextPosition.moves;
                                    BFS.push(nextPosition);
                                }
                            }
                            else
                            {
                                if (visited[nextPosition.r][nextPosition.c].second == INF)
                                {
                                    visited[nextPosition.r][nextPosition.c].second = nextPosition.moves;
                                    BFS.push(nextPosition);
                                }
                            }
                        }

                if (!current.horizontal)
                    if (current.c + 1 < grid.size())
                        if (grid[current.r][current.c + 1] != 1 && grid[current.r + 1][current.c + 1] != 1) // can rotate counter clockwise
                        {
                            Position nextPosition(current);
                            Rotate(nextPosition);
                    
                            if (nextPosition.horizontal)
                            {
                                if (visited[nextPosition.r][nextPosition.c].first == INF)
                                {
                                    visited[nextPosition.r][nextPosition.c].first = nextPosition.moves;
                                    BFS.push(nextPosition);
                                }
                            }
                            else
                            {
                                if (visited[nextPosition.r][nextPosition.c].second == INF)
                                {
                                    visited[nextPosition.r][nextPosition.c].second = nextPosition.moves;
                                    BFS.push(nextPosition);
                                }
                            }
                        }
            }
        }
        
        return -1;
    }
};

int main_SnakeGrid()
{
//[[0, 0, 0, 0, 0, 1],
//[1, 1, 0, 0, 1, 0],
//[0, 0, 0, 0, 1, 1],
//[0, 0, 1, 0, 1, 0],
//[0, 1, 1, 0, 0, 0],
//[0, 1, 1, 0, 0, 0]]
    vector<vector<int>> grid;
    Solution s;

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        vector<int> row(m, 0);
        grid.push_back(row);
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];
    }

    cout << s.minimumMoves(grid);

    //for (int i = 0; i < n; i++)
    //{
    //    for (int j = 0; j < m; j++)
    //        cout << freq[i][j] << " ";
    //    cout << "\n";
    //}
    return 0;
}