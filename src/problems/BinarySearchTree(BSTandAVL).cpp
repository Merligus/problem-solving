#include <random>
#include "../lib/BinaryTree.hpp"
#include "../lib/SingleLinkedList.hpp"

Tree* sortedListToBST(SingleLinkedList* A)
{
	SingleLinkedListCell* a;
	Tree* T;
	T = new Tree();

	a = A->Front();
	while (a != NULL)
	{
		T->AddAVL(a->GetKey());
		a = a->next;
	}

	return T;
}

int main_BinarySearchTree()
{
	Tree* T;
	SingleLinkedList A;
	int test[] = { 1, 3, 5, 7, 9, 11, 13, 15, 16 };
	for (auto& num : test)
		A.Push(num);

	A.Print();

	T = sortedListToBST(&A);
	T->PreOrder(T->Root());
	T->PostOrder(T->Root());
	delete T;
	return 0;
}