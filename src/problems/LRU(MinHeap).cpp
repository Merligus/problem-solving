#include "../lib/Queue.hpp"
#include <iostream>

class LRUCache
{
public:
	LRUCache(int capacity);
	~LRUCache();

	void Put(int index, int value);
	int Get(int index);

	void Print()
	{
		_lru.Print();
	}

private:
	int _capacity;
	Queue _lru;
};

LRUCache::LRUCache(int capacity)
{
	_capacity = capacity;
}

LRUCache::~LRUCache()
{
	while (!_lru.Empty())
		_lru.Pop();
}

// O(1)
void LRUCache::Put(int index, int value)
{
	if (_lru.Size() >= _capacity)
		_lru.Pop();
	_lru.Push(index, value);
	Print();
}

// Average O(1)
int LRUCache::Get(int index)
{
	std::pair<int, int> tuple;
	tuple = _lru.RemoveAt(index);
	if (tuple.first != -1)
	{
		_lru.Push(tuple.first, tuple.second);
		std::cout << tuple.second << " ";
		Print();
		return tuple.second;
	}
	else
		return -1;
}

int main_LRU()
{
	LRUCache cache(2);

	cache.Put(16, 160);
	cache.Put(14, 140);
	cache.Put(15, 150);
	cache.Get(15);
	cache.Get(14);
	cache.Get(16);
	cache.Put(1, 10);
	cache.Put(9, 90);
	cache.Put(2, 20);
	cache.Get(15);
	cache.Get(14);
	cache.Get(1);
	cache.Get(9);
	cache.Get(2);
	
	return 0;
}