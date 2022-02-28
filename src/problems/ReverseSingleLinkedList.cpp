#include <iostream>
#include "../lib/SingleLinkedList.hpp"

// O(n)
void ReverseLinkedList(SingleLinkedList* list, SingleLinkedList* out)
{
	// O(n)
	while (!list->Empty())
		out->PushFront(list->PopFront()); // O(1)
}

int main_ReverseSingleLinkedList()
{
	int test[] = { 1, 1, 2, 4, 3, 5 };
	SingleLinkedList list, outList;
	for (auto& num : test)
		list.Push(num);

	list.Print();

	ReverseLinkedList(&list, &outList);
	outList.Print();

	return 0;
}