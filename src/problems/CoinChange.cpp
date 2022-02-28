#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

int coinChangeDynamic(vector<int>& coins, int ithCoin, int amount, int nCoins)
{
    if (ithCoin < 0)
        return (amount != 0) ? -1 : nCoins;

    int maxCoins;

    maxCoins = amount / coins[ithCoin];

    int nCoinsSpecific, bestChange(-1);
    for (nCoinsSpecific = maxCoins; nCoinsSpecific >= 0; nCoinsSpecific--)
    {
        int newAmount = amount - nCoinsSpecific * coins[ithCoin];
        int change = coinChangeDynamic(coins, ithCoin - 1, newAmount, nCoins + nCoinsSpecific);

        if (change != -1)
        {
            bestChange = change;
            break;
        }
    }
    
    return bestChange;
}

class Solution {
public:
    int coinChange(vector<int>& coins, int amount)
    {
        sort(coins.begin(), coins.end());

        return coinChangeDynamic(coins, coins.size() - 1, amount, 0);
    }
};

int main_CoinChange()
{
    int test[] = { 1, 2, 5 };
    std::vector<int> arr(test, test + sizeof(test) / sizeof(int));
    Solution s;

    cout << s.coinChange(arr, 11);

    return 0;

}