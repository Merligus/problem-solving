#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

void PreProcess(std::unordered_map<char, std::vector<int>>& letter_ToPossibleWords, std::vector<std::string> words, std::pair<int, int> interval)
{
	// iterate through words of the same length
	for (int index = interval.first; index <= interval.second; index++)
	{
		if (letter_ToPossibleWords.find(words[index][0]) == letter_ToPossibleWords.end()) // not in
		{
			// create
			std::vector<int> wordIndexesVector;
			wordIndexesVector.push_back(index); // add the index of the word
			letter_ToPossibleWords[words[index][0]] = wordIndexesVector;
		}
		else // already in
		{
			letter_ToPossibleWords[words[index][0]].push_back(index); // add the index of the word to the existing options
		}
	}
}

bool CompareLength(const std::string& a, const std::string& b)
{
	return a.length() < b.length();
}

void FindMatchingWords(std::unordered_map<char, std::vector<int>> letter_ToPossibleWords,
					   std::vector<std::vector<std::string>>& wordSquares, 
					   std::vector<std::string> aWordSquare,
					   std::vector<std::string> words,
					   std::unordered_set<int> usedWords)
{
	if (aWordSquare[0].length() == aWordSquare.size())
	{
		wordSquares.push_back(aWordSquare);
	}
	else
	{
		int ithWord = aWordSquare.size();
		if (letter_ToPossibleWords.find(aWordSquare[0][ithWord]) == letter_ToPossibleWords.end())
			return; // there are no words starting with the letter of the first word
		std::vector<int> possibleWords = letter_ToPossibleWords[aWordSquare[0][ithWord]];
		for (int index : possibleWords)
		{
			if (usedWords.find(index) != usedWords.end()) // already used
				continue;

			bool bMatch(true);
			// 0th already checked by letter_ToPossibleWords
			for (int charIndex = 1; charIndex < ithWord && bMatch; charIndex++)
				if (words[index][charIndex] != aWordSquare[charIndex][ithWord])
					bMatch = false;

			if (bMatch)
			{
				aWordSquare.push_back(words[index]);
				usedWords.insert(index);

				FindMatchingWords(letter_ToPossibleWords, wordSquares, aWordSquare, words, usedWords);

				usedWords.erase(index);
				aWordSquare.pop_back();
			}
		}
	}
}

std::vector<std::vector<std::string>> WordSquares(std::vector<std::string> words)
{
	std::vector<std::vector<std::string>> wordSquares;
	// corner case
	if (words.size() == 0)
		return wordSquares;

	std::vector<std::pair<int, int>> wordsIntervalsLength;
	std::unordered_map<char, std::vector<int>> letter_ToPossibleWords;

	std::sort(words.begin(), words.end(), CompareLength);

	wordsIntervalsLength.push_back({0, 0});
	wordsIntervalsLength.back().first = 0;
	for (int index = 1; index < words.size(); index++)
	{
		if (words[index - 1].length() != words[index].length()) // increased
		{
			wordsIntervalsLength.back().second = index - 1;
			wordsIntervalsLength.push_back({index, index});
		}
	}
	wordsIntervalsLength.back().second = words.size() - 1;

	// for (std::string word : words)
	// 	std::cout << word << " ";
	// std::cout << "\n";

	for (std::pair<int, int> interval : wordsIntervalsLength)
	{
		// std::cout << interval.first << "-" << interval.second << "\n";
		PreProcess(letter_ToPossibleWords, words, interval);
		// int position = 0;
		// for (std::unordered_map<char, std::vector<int>>& positionLookup: letter_ToPossibleWords)
		// {
		// 	std::cout << position++ << " position\n";
		// 	for (auto letterToWord = positionLookup.begin(); letterToWord != positionLookup.end(); letterToWord++)
		// 	{
		// 		std::cout << letterToWord->first << "->\n";
		// 		for (auto& wordIndex : letterToWord->second)
		// 			std::cout << '\t' << words[wordIndex] << '\n';
		// 	}
		// }
		// std::cout << '\n';
		std::vector<std::string> aWordSquare;
		for (int index = interval.first; index <= interval.second; index++)
		{
			std::unordered_set<int> usedWords;
			usedWords.insert(index);
			aWordSquare.push_back(words[index]);

			FindMatchingWords(letter_ToPossibleWords, wordSquares, aWordSquare, words, usedWords);

			usedWords.clear();
			aWordSquare.clear();
		}

		letter_ToPossibleWords.clear();
	}

	return wordSquares;
}

int main_WordSquare()
{

//13
//AREA
//BALL
//DEAR
//ARE
//LADY
//LEAD
//YARD
//BA
//AB
//A
//CAL
//B
//LEY



	std::vector<std::string> words;
	std::vector<std::vector<std::string>> wordSquares;

	int n;
	std::cin >> n;
	for (int indexIn = 0; indexIn < n; indexIn++)
	{
		std::string word;
		std::cin >> word;
		words.push_back(word);
	}

	wordSquares = WordSquares(words);

	for (std::vector<std::string>& wordSquare : wordSquares)
	{
		for (std::string word : wordSquare)
			std::cout << word << "\n";
		std::cout << "\n";
	}
	return 0;
}
