#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

int Find(std::vector<int> A, std::vector<bool> checkListProcesses, int processesLoaded, int diff, int& bestDiff)
{
    if (processesLoaded == A.size() - 1)
    {
        for (int i = 0; i < A.size(); i++)
        {
            if (!checkListProcesses[i])
            {
                if (diff > 0)
                    diff -= A[i];
                else
                    diff += A[i];
                break;
            }
        }
        return diff;
    }
    else if (processesLoaded == A.size())
        return diff;
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = i + 1; j < A.size(); j++)
        {
            if (!checkListProcesses[i] && !checkListProcesses[j])
            {
                checkListProcesses[i] = true;
                checkListProcesses[j] = true;
                int diffAux = diff;
                if (diffAux > 0)
                    diffAux = diffAux + std::min(A[i], A[j]) - std::max(A[i], A[j]);
                else
                    diffAux = diffAux + std::max(A[i], A[j]) - std::min(A[i], A[j]);
                diffAux = Find(A, checkListProcesses, processesLoaded + 2, diffAux, bestDiff);
                if (std::abs(diffAux) < std::abs(bestDiff) )
                    bestDiff = diffAux;

                checkListProcesses[i] = false;
                checkListProcesses[j] = false;
            }
        }
    }
    return bestDiff;
}

int solutionPractice2(vector<int> A)
{
    std::vector<bool> checkListProcesses(A.size(), false);
    int diff(std::numeric_limits<int>::max());
    
    Find(A, checkListProcesses, 0, 0, diff);

    return std::abs(diff);
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

int main_Practice2()
{
    // Read in from stdin, solve the problem, and write answer to stdout.
    int test[] = { 1, 3, 20, 1, 17, 4 };
    // int test[] = { 4, 2, 1, 3, 5 };
    std::vector<int> A(test, test + sizeof(test) / sizeof(int));
    cout << solutionPractice2(A);

    return 0;
}