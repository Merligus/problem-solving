#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k)
    {
        // 1st
        // k % nums.size() => shift
        // for i = [0 to nums.size() - 1]:
        //   out[i] = nums[(i - shift) % nums.size()]
        int shift = k % nums.size();
        vector<int> out;
        for (int index = 0; index < nums.size(); index++)
        {
            int temp = (nums.size() + index - shift) % nums.size();
            out.push_back(nums[temp]);
        }

        for (int index = 0; index < nums.size(); index++)
            nums[index] = out[index];

        // 3rd
        // out = vector with nums.size() + k
        // out[0:k - 1] = nums[nums.size() - k:nums.size() - 1] if k > 0
        // out[k:nums.size() + k - 1] = nums
        // nums[0:nums.size()-1] = out[0:nums.size()-1]
    }
};

int main_ShiftRightArray()
{
    int test[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
    vector<int> nums(test, test + sizeof(test) / sizeof(int));
    int k = 24;
    Solution s;

    s.rotate(nums, k);
    for (int& n : nums)
        cout << n << " ";
    cout << "\n";

    return 0;
}