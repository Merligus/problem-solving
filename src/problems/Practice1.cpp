#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

int solutionPractice1(vector<int> A)
{
    std::vector<int> rows;
    bool shouldCreateRow;
    int indexA, indexRow;

    if (A.size() > 0)
    {
        rows.push_back(A[0]);
    }
    else
    {
        return 0;
    }

    for (indexA = 1; indexA < A.size(); indexA++)
    {
        shouldCreateRow = true;
        for (indexRow = 0; indexRow < rows.size() && shouldCreateRow; indexRow++)
        {
            if (rows[indexRow] > A[indexA])
            {
                rows[indexRow] = A[indexA];
                shouldCreateRow = false;
            }
        }

        if (shouldCreateRow)
        {
            rows.push_back(A[indexA]);
        }
    }

    return rows.size();
}

//vector<int> toIntVector(string str)
//{
//    std::vector<int> out;
//    std::string i;
//    std::istringstream tokenStream(str);
//    while (std::getline(tokenStream, i, ','))
//    {
//        out.push_back(atoi(i.c_str()));
//    }
//    return out;
//}

int main_Practice()
{
    // Read in from stdin, solve the problem, and write answer to stdout.
    string AS;
    int test[] = { 5, 4, 3, 6, 1, 7, 2, 9, 16, 18, 17, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    std::vector<int> A(test, test + sizeof(test) / sizeof(int));
    // cin >> AS;
    // vector<int> A = toIntVector(AS);
    cout << solutionPractice1(A);

    return 0;
}