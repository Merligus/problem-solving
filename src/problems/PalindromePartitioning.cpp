#include <iostream>
#include <vector>

bool VerifyPalindrome(std::string A)
{
	for (int i = 0; i < A.length() / 2; i++)
		if (A[i] != A[A.length() - i - 1])
			return false;
	return true;
}

int PalindromeCut(std::string A, std::vector<std::vector<int>>& D, int s, int e)
{
	if (D[s][e] != -1)
		return D[s][e];
	else if (VerifyPalindrome(A.substr(s, e - s + 1)))
		return 0;
	else
	{
		D[s][e] = std::numeric_limits<int>::max();
		for (int i = s; i < e; i++)
		{
			if (D[s][i] == -1)
				D[s][i] = PalindromeCut(A, D, s, i);
			if (D[i + 1][e] == -1)
				D[i + 1][e] = PalindromeCut(A, D, i + 1, e);

			D[s][e] = std::min(D[s][e], 1 + D[s][i] + D[i + 1][e]);
		}
		return D[s][e];
	}
}

int minCut(std::string A)
{
	std::vector<int> aux(A.length(), -1);
	std::vector<std::vector<int>> D(A.length(), aux);
	for (int i = 0; i < A.length(); i++)
		D[i][i] = 0;

	return PalindromeCut(A, D, 0, A.length() - 1);
}

int main_PalindromePartitioning()
{
	// std::string A("babbbbaabbaabaabaabaaabaababaaaabbbbbabbaabbabbbbababaabbabbbabbbaaabaababaaaababbbbabbbbbbaaaabaaabaabbbaaaabaaabbbaabababbbaaaabbabbbabaaabbbabaaabbbaaaaaabaabbabbaabbbbbaababbbbabbabbaabbbabaababaaaabbaabbbaabaabbbbbbaabbbaaaabbaaaaaabaabbaababbbabbbbbbaabbaabbbabbbaabbbaaaabbbaaaabbbabbaababaaabbababbaabbabbabaabbbbaaaabbaababababbbbbabbbbabbaaabbaabaaaaabbaaaaaaaaaaababaaabbbaababbbbbbbabbababbaabbaaaababbbabbaaabbbbbabbbaabbaaaaabbbbbbabbbbbabbabbbabbabbababbabaabaabbabababbababaababbaababbabaabbaaaabbbaa");
	std::vector<std::string> B({ "bbba", "aaaa", "abaa", "aba", "aabaaa", "baabbaab", "bbbabbbaaa", "abaabbbbba", "abaa", "aba", "bbabbbbabb", "aab", "baaabbbaaa", "b", "baba", "aaba", "baaba", "abb", "aaaa", "baaabbbaa", "ab" });

	std::string A("dVGAaVO25EmT6W3zSTEA0k12i64Kkmmli09Kb4fArlF4Gc2PknrlkevhROxUg");
	std::cout << minCut(A);

	return 0;
}