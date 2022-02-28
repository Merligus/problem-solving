#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

#define INF numeric_limits<int>::max()

class Solution
{
public:

    void findAllSumCombinations(vector<vector<double>>& combinations, vector<int> arr, int index, double sum, int k)
    {
        if (k <= arr.size())
            combinations[k].push_back(sum);
        if (index < arr.size())
        {
            findAllSumCombinations(combinations, arr, index + 1, sum + arr[index], k + 1);
            findAllSumCombinations(combinations, arr, index + 1, sum, k);
        }
    }

    int minimumDifference(vector<int>& nums)
    {
        vector<int> arr1(nums.begin(), nums.begin() + nums.size() / 2);
        vector<int> arr2(nums.begin() + nums.size() / 2, nums.end());

        double sumNums(0);
        for (int& value : nums)
            sumNums += value;

        double target = sumNums / 2.0f;

        vector<double> empty1, empty2;
        vector<vector<double>> sumArr1Selecting(1 + nums.size() / 2, empty1);
        vector<vector<double>> sumArr2Selecting(1 + nums.size() / 2, empty2);
        findAllSumCombinations(sumArr1Selecting, arr1, 0, 0, 0);
        findAllSumCombinations(sumArr2Selecting, arr2, 0, 0, 0);
        for (int k = 0; k <= nums.size() / 2; k++)
            sort(sumArr2Selecting[k].begin(), sumArr2Selecting[k].end());

        double closestSum(sumArr1Selecting.front()[0] + sumArr2Selecting.back()[0]);
        for (int k1 = 0; k1 <= nums.size() / 2; k1++)
        {
            int k2 = nums.size() / 2 - k1;

            for (double& sum1 : sumArr1Selecting[k1])
            {
                vector<double>::iterator closestFinded = upper_bound(sumArr2Selecting[k2].begin(), sumArr2Selecting[k2].end(), target - sum1);
                double sum2;
                if (closestFinded != sumArr2Selecting[k2].begin())
                    sum2 = *(--closestFinded);
                else
                    sum2 = *(closestFinded);
                if (abs(sum1 + sum2 - target) < abs(closestSum - target))
                    closestSum = sum1 + sum2;
            }
        }

        return abs(sumNums - closestSum - closestSum);
    }
};

int main_MinimumSumDiff()
{
    cout << fixed;

    vector<int> nums({ 576540, -3804995, -7884720, 1363877, 4631024, -6361235, -5803805, 9968336, 1771260, -6043832, -8313199, 3567219, 8162122, 7708575, 5505806, 7109884, 580515, 6177912, -3940512, 9603688, 1289170, -5222647, 8552243, -9574299, -4174878, -1695857, 932929, 438464, -5095053, 9328205 });
    // vector<int> nums({ -7016943,0,2205243,-794066,-6795006,5322408,9699476,6544247,6992622,7272161,5469637,4806999,-8562708,-5242263,9037593,-2746735,8072395,-1386148,4745179,3801334,-4086041,0,555427,-9249908,5045948,-7943170,1665466,9514306,7960606,-142676 });
    // vector<int> nums({ 1959941,-5672472,-6781570,-3636632,776424,1064006,-5831186,-4521402,-8288384,-1397822,6807065,-4717862,5869167,-6661141,0,8636400,-7185563,-6538523,2792508,-5201312,6217227,-3481403,-4440803,-2456281,-9116647,-5539229,2643059,1672385,-8878387,-1306203 });
    Solution s;

    cout << s.minimumDifference(nums);

    return 0;
}