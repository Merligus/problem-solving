#include <deque>
#include <iostream>
#include <vector>

#define MOD 1000000007

using namespace std;

class Solution
{
public:
    int dieSimulator(int n, vector<int>& rollMax)
    {
        vector<long long> allComb(6, 1);
        vector<deque<long long>> combConsecutive;

        for (int& rollMaxi : rollMax)
        {
            deque<long long> startingCombs(rollMaxi, 0);
            startingCombs[0] = 1;
            combConsecutive.push_back(startingCombs);
        }

        for (int ni = 1; ni < n; ni++)
        {
            vector<long long> newAllComb(allComb);

            for (int num = 0; num < 6; num++)
            {
                newAllComb[num] = (newAllComb[num] - combConsecutive[num].back()) % MOD;
                combConsecutive[num].pop_back();
                long long sum = 0;
                for (int num2 = 0; num2 < 6; num2++)
                    if (num != num2)
                        sum = (sum + allComb[num2]) % MOD;

                newAllComb[num] = (newAllComb[num] + sum) % MOD;
                combConsecutive[num].push_front(sum);
            }

            allComb.swap(newAllComb);
        }

        int count = 0;
        for (int num = 0; num < 6; num++)
            count = (count + allComb[num]) % MOD;

        return count;
    }
};

int main_DiceRollSimulation()
{
    //vector<int> test({ 1, 1, 1, 2, 2, 3 });
    //int n = 3;
    //vector<int> test({ 1, 1, 1, 1, 1, 1 });
    //int n = 2;
    vector<int> test({ 1, 1, 2, 2, 2, 3 });
    int n = 2;
    Solution s;

    cout << s.dieSimulator(n, test) << endl;

    return 0;
}
