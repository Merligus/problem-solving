#include <iostream>
#include <vector>

class InterleavingFlattener
{
private:
	int _iteratorsEnded;
	int _currentIterator;
	std::vector<std::vector<int>::iterator> _iterList;
	std::vector<std::vector<int>::iterator> _endIterList;

public:

	InterleavingFlattener(std::vector<std::vector<int>::iterator> IterList, std::vector<std::vector<int>::iterator> EndIterList)
	{
		_currentIterator = 0;
		_iteratorsEnded = 0;
		for (int index = 0; index < IterList.size(); index++)
		{
			_iterList.push_back(IterList[index]);
			_endIterList.push_back(EndIterList[index]);
			if (IterList[index] == EndIterList[index])
				_iteratorsEnded++;
		}

		int maxLoop(_iterList.size());
		while (_iterList[_currentIterator] == _endIterList[_currentIterator] && maxLoop-- != 0)
			_currentIterator = ++_currentIterator % _iterList.size();
	}

	bool hasNext()
	{
		return _iteratorsEnded < _iterList.size();
	}

	int next()
	{
		std::vector<int>::iterator it = _iterList[_currentIterator]++;
		if (_iterList[_currentIterator] == _endIterList[_currentIterator])
			_iteratorsEnded++;

		int maxLoop(_iterList.size());
		do
			_currentIterator = ++_currentIterator % _iterList.size();
		while (_iterList[_currentIterator] == _endIterList[_currentIterator] && maxLoop-- != 0);

		return *it;
	}
};

int main_InterleavingIterator()
{
	std::vector<int> arr1({ 1, 2});
	std::vector<int> arr2({  });
	std::vector<int> arr3({ 1 });
	std::vector<int>::iterator a(arr1.begin());
	std::vector<int>::iterator b(arr2.begin());
	std::vector<int>::iterator c(arr3.begin());
	std::vector<std::vector<int>::iterator> iterList{a, b, c};
	std::vector<std::vector<int>::iterator> endIterList{ arr1.end(), arr2.end(), arr3.end() };
	InterleavingFlattener itf1(iterList, endIterList);
	while (itf1.hasNext())
	{
		std::cout << itf1.next() << " ";
	}
	return 0;
}
