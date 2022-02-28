#include <iostream>
#include <vector>
#include <unordered_map>

void Radix(std::vector<std::string>& arr)
{
	int maxLength(0);
	for (std::string s : arr)
		maxLength = (s.length() > maxLength) ? s.length() : maxLength;

	std::vector<std::string> arrAux(arr.size(), "");
	std::unordered_map<char, int> charFreq;
	for (int pos = maxLength - 1; pos >= 0; pos--)
	{
		for (char c = 'a'; c <= 'z'; c++)
			charFreq[c] = 0;
		charFreq['0'] = 0;

		for (std::string& s : arr)
		{
			if (pos < s.length())
				charFreq[s[pos]]++;
			else
				charFreq['0']++;
		}

		charFreq['a'] += charFreq['0'];
		for (char c = 'b'; c <= 'z'; c++)
			charFreq[c] += charFreq[c - 1];

		for (int index = arr.size() - 1; index >= 0; index--)
		{
			if (pos < arr[index].length())
			{
				arrAux[charFreq[arr[index][pos]] - 1] = arr[index];
				charFreq[arr[index][pos]]--;
			}
			else
			{
				arrAux[charFreq['0'] - 1] = arr[index];
				charFreq['0']--;
			}
		}

		arr.swap(arrAux);
	}
}

int main_RadixString()
{
	std::string test[] = { "aaa", "aab", "aa", "a", "ba", "baa", "bab", "bba", "bbb", "aaaaaaaa", "", "c" };
	std::vector<std::string> arrStr(test, test + sizeof(test) / sizeof(std::string));

	for (std::string& s : arrStr)
		std::cout << s << ":\n";
	std::cout << "\n";

	Radix(arrStr);

	for (std::string& s : arrStr)
		std::cout << s << ":\n";
	std::cout << "\n";

	return 0;
}