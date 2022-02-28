#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int mainTest()
{
	int arrayTest[] = { 1, 1, 3, 5, 7, 7 };
	vector<int> nums(arrayTest, arrayTest + sizeof(arrayTest) / sizeof(int));
	vector<int> arr1(nums.begin(), nums.begin() + nums.size() / 2), arr2(nums.begin() + nums.size() / 2, nums.end());


	long long s = 999088232;
	long long mod = 1000000007;

	// cout << (s - (s + 1)) % mod;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;

	int index = 0;
	for (int& num : nums)
		heap.push({ num, index++ });

	while (!heap.empty())
	{
		cout << heap.top().first << "," << heap.top().second << endl;
		heap.pop();
	}

	return 0;
}
