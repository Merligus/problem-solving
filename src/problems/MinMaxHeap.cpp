#include <iostream>
#include <vector>
#include <algorithm> 
#include <random>

class KthLargestNumberInStream
{
public:
	KthLargestNumberInStream(std::vector<int> v, int k);
	int add(int num);
	void Print(std::string s);

private:
	std::vector<int> _array;
	int k;

	int PopMaxMax();
	void UpdateHeapMax(int index);
	void UpdateHeapUpMax(int index);

	int PopMaxMin();
	void UpdateHeapMin(int index);
	void UpdateHeapUpMin(int index);
};

KthLargestNumberInStream::KthLargestNumberInStream(std::vector<int> v, int k)
{
	// Make a min heap with the largest numbers and store the k
	for (int i = 0; i < k; i++)
	{
		_array.push_back(v[i]);
		UpdateHeapUpMin(i);
		Print("Push back: ");
	}
	for (int i = k; i < v.size(); i++)
		add(v[i]);
	this->k = k;
}

// O(lgk)
int KthLargestNumberInStream::add(int num)
{
	if (_array[0] < num)
	{
		_array[0] = num;
		UpdateHeapMin(0);
	}

	Print("Add: ");

	return _array[0];
}

// O(lgn)
int KthLargestNumberInStream::PopMaxMax()
{
	int max;
	// pop the max number of the array
	max = _array[0];
	_array[0] = _array[_array.size() - 1];
	_array[_array.size() - 1] = max;
	_array.pop_back();
	// update the heap
	UpdateHeapMax(0);
	return max;
}

// O(lgn)
void KthLargestNumberInStream::UpdateHeapMax(int index)
{
	int l = 2 * index + 1;
	int r = 2 * (index + 1);
	// find the largest between index, left and right son in the heap
	int largest = index;
	if (r < _array.size() && _array[r] > _array[index])
		largest = r;
	if (l < _array.size() && _array[l] > _array[largest])
		largest = l;
	// if the largest is not the index, then...
	if (largest != index)
	{
		// update the largest to be the parent
		int aux;
		aux = _array[index];
		_array[index] = _array[largest];
		_array[largest] = aux;
		// update the heap
		UpdateHeapMax(largest);
	}
}

// O(lgn)
void KthLargestNumberInStream::UpdateHeapUpMax(int index)
{
	int p = (index - 1)/ 2;
	if (p >= 0 && _array[p] < _array[index])
	{
		int aux;
		aux = _array[index];
		_array[index] = _array[p];
		_array[p] = aux;
		UpdateHeapUpMax(p);
	}
}

// O(lgn)
int KthLargestNumberInStream::PopMaxMin()
{
	int max;
	// pop the max number of the array
	max = _array[0];
	_array[0] = _array[_array.size() - 1];
	_array[_array.size() - 1] = max;
	_array.pop_back();
	// update the heap
	UpdateHeapMin(0);
	return max;
}

// O(lgn)
void KthLargestNumberInStream::UpdateHeapMin(int index)
{
	int l = 2 * index + 1;
	int r = 2 * (index + 1);
	// find the largest between index, left and right son in the heap
	int smallest = index;
	if (r < _array.size() && _array[r] < _array[index])
		smallest = r;
	if (l < _array.size() && _array[l] < _array[smallest])
		smallest = l;
	// if the smallest is not the index, then...
	if (smallest != index)
	{
		// update the smallest to be the parent
		int aux;
		aux = _array[index];
		_array[index] = _array[smallest];
		_array[smallest] = aux;
		// update the heap
		UpdateHeapMin(smallest);
	}
}

// O(lgn)
void KthLargestNumberInStream::UpdateHeapUpMin(int index)
{
	int p = (index - 1) / 2;
	if (p >= 0 && _array[p] > _array[index])
	{
		int aux;
		aux = _array[index];
		_array[index] = _array[p];
		_array[p] = aux;
		UpdateHeapUpMin(p);
	}
}

void KthLargestNumberInStream::Print(std::string s)
{
	std::cout << s;
	for (int i = 0 ; i < _array.size(); i++)
		std::cout << _array[i] << " ";
	std::cout << "\n";
}

int main_MinMaxHeap()
{
	int test[] = { 3, 1, 5, 12, 2, 11, };
	std::vector<int> test_vec(test, test + sizeof(test) / sizeof(int));
	KthLargestNumberInStream obj(test_vec, 4);

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, 1000);

	for (int i = 0; i < 15; i++)
	{
		int num(distribution(generator));
		std::cout << "Number: " << num << std::endl;
		std::cout << obj.add(num) << std::endl;
	}

	return 0;
}