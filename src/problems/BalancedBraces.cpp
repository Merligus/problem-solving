#include <iostream>
#include <queue>

void Close(std::string braces, int toBeClosed, int toBeOpened);
void Open(std::string braces, int toBeClosed, int toBeOpened);

void Close(std::string braces, int toBeClosed, int toBeOpened)
{
	braces += ")";
	toBeClosed--;

	if (toBeClosed == 0 && toBeOpened == 0)
		std::cout << braces << "\n";
	else
	{
		if (toBeOpened > 0)
			Open(braces, toBeClosed, toBeOpened);
		if (toBeClosed > 0)
			Close(braces, toBeClosed, toBeOpened);
	}
}

void Open(std::string braces, int toBeClosed, int toBeOpened)
{
	braces += "(";
	toBeClosed++;
	toBeOpened--;

	if (toBeOpened > 0)
		Open(braces, toBeClosed, toBeOpened);
	if (toBeClosed > 0)
		Close(braces, toBeClosed, toBeOpened);
}

void PrintBalancedBraces(int num)
{
	std::string braces("");
	Open(braces, 0, num);
}

int main_BalancedBraces()
{
	int num(4);

	PrintBalancedBraces(num);

	return 0;
}