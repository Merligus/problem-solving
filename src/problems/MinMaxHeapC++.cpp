#include <iostream>
#include <queue>

class CustomObject
{
public:
	int value;
	int index;

	CustomObject(int v, int index);

};

CustomObject::CustomObject(int index, int value)
{
	this->value = value;
	this->index = index;
}

class CustomOperator
{
	bool minHeap;

public:
	CustomOperator(const bool& minHeapParam = false)
	{
		minHeap = minHeapParam;
	}

	bool operator() (const CustomObject& lhs, const CustomObject& rhs) const
	{
		if (minHeap)
			return (lhs.value > rhs.value);
		else
			return (lhs.value < rhs.value);
	}
};

int main_MinMaxHeapC()
{
	int arr[] = { 10, 40, 60, 50 };
	typedef std::priority_queue<CustomObject, std::vector<CustomObject>, CustomOperator> HeapType;
	HeapType maxHeap(CustomOperator(false));
	HeapType minHeap(CustomOperator(true));

	for (int index = 0; index < 4; index++)
	{
		maxHeap.push(CustomObject(index, arr[index]));
		minHeap.push(CustomObject(index, arr[index]));
	}

	maxHeap.pop();
	std::cout << maxHeap.empty() << " " << maxHeap.size() << " " << maxHeap.top().value << " ";
	maxHeap.push(CustomObject(0, 5));
	maxHeap.push(CustomObject(0, 65));
	std::cout << maxHeap.top().value << "\n";

	minHeap.pop();
	std::cout << minHeap.empty() << " " << minHeap.size() << " " << minHeap.top().value << " ";
	minHeap.push(CustomObject(0, 5));
	maxHeap.push(CustomObject(0, 65));
	std::cout << minHeap.top().value << "\n";

	return 0;
}