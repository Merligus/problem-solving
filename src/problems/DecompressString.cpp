#include <iostream>
#include <cctype>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <cmath>

// O (sum*strLength)
std::vector<char> DecompressString(std::string str, int& startingIndex)
{
	std::vector<char> decompressed_str;
	int index(startingIndex);
	for (; index < str.length() && str[index] != ']'; index++)
	{
		if (isdigit(str[index]))
		{
			// find the [string]
			char number_c[10];
			int index_number_c(0);
			do
			{
				number_c[index_number_c++] = str[index++];
			} while (isdigit(str[index]));
			number_c[index_number_c] = '\0';
			// after do while, '['
			index++;
			int number(atoi(number_c));

			std::vector<char> decompressed_str_rec;
			decompressed_str_rec = DecompressString(str, index);

			for (int time = 1; time <= number; time++)
				for (char c : decompressed_str_rec)
					decompressed_str.push_back(c);
		}
		else if (isalpha(str[index]))
		{
			// append the character
			decompressed_str.push_back(str[index]);
		}
	}
	startingIndex = index;
	return decompressed_str;
}

int main_DecompressString()
{
	int initialIndex(0);
	std::string input_str;
	std::vector<char> output_str;

	std::cin >> input_str;
	output_str = DecompressString(input_str, initialIndex);
	for (char c : output_str)
		std::cout << c;
	std::cout << "\n";

	return 0;
}