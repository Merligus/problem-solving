#include <iostream>
#include <string>
#include <unordered_map>
#include <list>

int solution2(std::string S)
{
	std::list<std::list<char>::iterator> SL_Bs;
	std::list<char> SL;
	std::list<char>::iterator SL_it;
	std::unordered_map<std::string, int> verified;
	int sumBs(0), index(0);
	// SL_it = SL.begin();
	for (auto& c : S)
	{
		SL.push_back(c);
		if (c == 'b')
		{
			SL_Bs.push_back(SL.end());
			sumBs += 1;
		}
		// SL_it++;
		index++;
	}

	for (auto& sl : SL)
		std::cout << sl << " ";
	std::cout << "\nSL\n";

	for (auto& sl : SL_Bs)
		std::cout << *sl << " ";
	std::cout << "\nSL_Bs\n";

	return 0;
}

int Find(std::string S, int remaining, int cost, std::unordered_map<std::string, int>& verified)
{
	std::unordered_map<std::string, int>::const_iterator finder;
	finder = verified.find(S);
	if (finder != verified.end()) // already done
	{
		return verified[S];
	}
	else if (remaining > 0)
	{
		verified[S] = std::numeric_limits<int>::max();
		int auxRemaining(remaining), auxCost(cost);

		// only front
		std::string auxS1(S);
		auxRemaining = remaining;
		if (S[0] == 'b')
		{
			auxRemaining--;
		}
		auxS1.erase(auxS1.begin());
		auxCost = Find(auxS1, auxRemaining, 1 + cost, verified);
		if (auxCost < verified[S])
			verified[S] = auxCost;

		// only back
		std::string auxS2(S);
		auxRemaining = remaining;
		if (S[S.size() - 1] == 'b')
			auxRemaining--;
		auxS2.erase(auxS2.begin() + S.size() - 1);
		auxCost = Find(auxS2, auxRemaining, 1 + cost, verified);
		if (auxCost < verified[S])
			verified[S] = auxCost;

		for (int i = 1; i < S.size() - 1; i++)
		{
			std::string auxS3(S);
			if (S[i] == 'b')
			{
				auxS3.erase(auxS3.begin() + i);
				auxCost = Find(auxS3, remaining - 1, 2 + cost, verified);
				if (auxCost < verified[S])
					verified[S] = auxCost;
			}
		}
		return verified[S];
	}
	else
		return cost;
}

int solution(std::string S)
{
	std::unordered_map<std::string, int> verified;
	int sumBs(0), index(0);
	for (auto& c : S)
	{
		if (c == 'b')
		{
			sumBs += 1;
		}
		
		index++;
	}

	return Find(S, sumBs, 0, verified);
}

int main_AInterview1()
{
	std::cout << solution2("aabaa") << std::endl;
	std::cout << solution2("abbaaba") << std::endl;
	std::cout << solution2("bbb") << std::endl;
	std::cout << solution2("abbbaabaabbba") << std::endl;
	std::cout << solution2("abbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbbaabbbaabaabbba") << std::endl;

	return 0;
}