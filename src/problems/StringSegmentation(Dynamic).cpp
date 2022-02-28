#include <iostream>
#include <unordered_map>

// need to backtrack
bool Verify(std::string s, std::unordered_map<std::string, bool> dictionary)
{
	bool bReturn;
	std::string word;
	std::unordered_map<std::string, bool>::const_iterator found;
	if (s.size() > 0)
	{
		for (int i = 1; i <= s.size(); i++)
		{
			word = s.substr(0, i);
			found = dictionary.find(word);
			if (found != dictionary.end())
			{
				bReturn = Verify(s.substr(i, s.size() - i), dictionary);
				if (bReturn)
					return true;
			}
		}
		return false;
	}
	else
		return true;
}

int main_StringSegmentation()
{
	std::string s("applerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenappleapplerpenapplerpenrpenapple");
	std::string test[] = { "apple", "appler", "rpenapple", "pen", "penr", "applerpen", "applerpenapple", "applerpena"};
	std::unordered_map<std::string, bool> dictionary;

	for (auto& word : test)
		dictionary[word] = true;

	for (auto& tuple : dictionary)
		std::cout << tuple.first << ":" << tuple.second << " ";

	if (Verify(s, dictionary))
		std::cout << "Yes\n";
	else
		std::cout << "No\n";

	return 0;
}
