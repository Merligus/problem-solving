#include <iostream>
#include <vector>
#include <unordered_map>

int WordSegmented(std::string A, std::vector<std::string>& B, std::vector<int>& D)
{
	if (A.size() == 0)
		return 1;
	else if (D[A.size()] == 0)
		return 0;
	else
	{
		std::unordered_map<std::string, bool> dict;
		for (auto& b : B)
		{
			std::unordered_map<std::string, bool>::const_iterator finder;
			finder = dict.find(b);
			if (finder == dict.end())
			{
				dict[b] = true;

				std::string s(A.substr(0, b.size()));
				if (s.compare(b) == 0) // there is in the dictionary
				{
					D[A.size() - b.size()] = WordSegmented(A.substr(b.size(), A.size() - b.size()), B, D);
					if (D[A.size() - b.size()] == 1)
						return 1;
				}
			}
		}
		return 0;
	}
}

int wordBreak(std::string A, std::vector<std::string>& B)
{
	std::vector<int> D(A.size() + 1, -1);
	return WordSegmented(A, B, D);
}

int main_WordSegmented()
{
	std::string A("babbbbaabbaabaabaabaaabaababaaaabbbbbabbaabbabbbbababaabbabbbabbbaaabaababaaaababbbbabbbbbbaaaabaaabaabbbaaaabaaabbbaabababbbaaaabbabbbabaaabbbabaaabbbaaaaaabaabbabbaabbbbbaababbbbabbabbaabbbabaababaaaabbaabbbaabaabbbbbbaabbbaaaabbaaaaaabaabbaababbbabbbbbbaabbaabbbabbbaabbbaaaabbbaaaabbbabbaababaaabbababbaabbabbabaabbbbaaaabbaababababbbbbabbbbabbaaabbaabaaaaabbaaaaaaaaaaababaaabbbaababbbbbbbabbababbaabbaaaababbbabbaaabbbbbabbbaabbaaaaabbbbbbabbbbbabbabbbabbabbababbabaabaabbabababbababaababbaababbabaabbaaaabbbaa");
	std::vector<std::string> B({ "bbba", "aaaa", "abaa", "aba", "aabaaa", "baabbaab", "bbbabbbaaa", "abaabbbbba", "abaa", "aba", "bbabbbbabb", "aab", "baaabbbaaa", "b", "baba", "aaba", "baaba", "abb", "aaaa", "baaabbbaa", "ab" });
	/*std::string A("myinterviewproblema");
	std::vector<std::string> B({ "interview", "problem", "my", "a"});*/
	if (wordBreak(A, B) == 1)
		std::cout << "Yes\n";
	else
		std::cout << "No\n";

	return 0;
}