#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int getMaxLen(vector<int>& nums)
    {
        vector<vector<int>> subnums;
        vector<int> negQtties;

        vector<int> numsAux;
        int negQtty(0);

        for (int& n : nums)
        {
            if (n == 0)
            {
                negQtties.push_back(negQtty);
                negQtty = 0;

                subnums.push_back(numsAux);
                numsAux.clear();
            }
            else
            {
                numsAux.push_back(n);
                if (n < 0)
                    negQtty++;
            }
        }
        negQtties.push_back(negQtty);
        subnums.push_back(numsAux);

        int index = 0;
        //for (vector<int>& v : subnums)
        //{
        //    for (int& n : v)
        //        cout << n << " ";
        //    if (index < negQtties.size())
        //        cout << " ->" << negQtties[index++] << "\n";
        //    else
        //        cout << "\n";
        //}

        index = 0;
        int maxLen = 0;
        for (vector<int>& v : subnums)
        {
            if (negQtties[index] % 2 == 1)
            {
                int shift = 0;
                while (shift < v.size() - 1 - shift)
                {
                    if (v[shift] < 0)
                        break;
                    else if (v[v.size() - 1 - shift] < 0)
                        break;

                    shift++;
                }

                if (maxLen < v.size() - shift - 1)
                    maxLen = v.size() - shift - 1;
            }
            else // even number of negatives = all subarray has positive multiply
                if (maxLen < v.size())
                    maxLen = v.size();
            index++;
        }

        return maxLen;
    }
};

int main_SubarrayPositiveMultiply()
{
    int test[] = { 2, -3, -4, -5, 6, 7, 8, 9, 10, -1, 12, 0, 1, -1, 5, 0 };
    // int test[] = { 0, 1, -2, -3, -4 };
    vector<int> arr(test, test + sizeof(test) / sizeof(int));
    Solution s;

    cout << s.getMaxLen(arr);

    return 0;
}
