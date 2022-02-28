#include <iostream>
#include <vector>

int FindIndexPrefix(std::string a, std::string b)
{
	int index(0);
	for (; index < a.length() && index < b.length(); index++)
		if (a[index] != b[index])
			break;
	return index - 1;
}

std::string longestCommonPrefix(std::vector<std::string>& A)
{
	int prefixIndex;
	std::string prefix;

	if (A.size() > 0)
	{
		prefix = A[0];
		for (int index = 1; index < A.size(); index++)
		{
			prefixIndex = FindIndexPrefix(prefix, A[index]);
			prefix = prefix.substr(0, prefixIndex + 1);
		}
	}
	return prefix;
}


int main_LongestCommonPrefix()
{
	int n;
	std::string s;
	std::cin >> n;
	std::vector<std::string> A(n, s);
	for (int i = 0; i < n; i++)
		std::cin >> A[i];

	s = longestCommonPrefix(A);

	std::cout << s << std::endl;

	return 0;
}