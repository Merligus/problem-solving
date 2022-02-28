// Treino1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.


#include <iostream>
#include <queue>
#include "../lib/BinaryTree.hpp"

void Print(TreeCell* root, std::string s)
{
	TreeCell* left, * right, * current;
	std::queue<TreeCell*> queue;
	queue.push(root);
	while (!queue.empty())
	{
		current = queue.front();
		left = current->left;
		right = current->right;
		std::cout << current->GetKey() << " ";
		if (left != NULL)
			queue.push(left);
		if (right != NULL)
			queue.push(right);
		queue.pop();
	}
	std::cout << s << "\n";
}

void Clear(TreeCell* root)
{
	TreeCell* left, * right, * current;
	std::queue<TreeCell*> queue;
	queue.push(root);
	while (!queue.empty())
	{
		current = queue.front();
		left = current->left;
		right = current->right;
		std::cout << current->GetKey() << " ";
		delete current;
		if (left != NULL)
			queue.push(left);
		if (right != NULL)
			queue.push(right);
		queue.pop();
	}
	std::cout << "\n";
}

void Swap(TreeCell* node)
{
	if (node != NULL)
	{
		Swap(node->left);
		Swap(node->right);
		// swap
		TreeCell* aux;
		aux = node->left;
		node->left = node->right;
		node->right = aux;
	}
}

TreeCell* Add(TreeCell* root, TreeCell* new_cell)
{
	TreeCell* current;
	std::pair<TreeCell*, TreeCell*> son_parent;
	std::queue<std::pair<TreeCell*, TreeCell*>> queue;
	if (root == NULL)
		root = new_cell;
	else
	{
		queue.push({ root, NULL });

		while (queue.size() != 0)
		{
			son_parent = queue.front();
			current = son_parent.first;
			if (current == NULL)
			{
				if (son_parent.second != NULL)
				{
					if (son_parent.second->left == NULL)
						son_parent.second->left = new_cell;
					else
						son_parent.second->right = new_cell;
				}
				break;
			}
			else
			{
				queue.push({ current->left, current });
				queue.push({ current->right, current });
				queue.pop();
			}
		}
	}
	return root;
}

bool VerifyEqual(TreeCell* root1, TreeCell* root2)
{
	if (root1 != NULL)
	{
		if (root2 != NULL)
		{
			bool bCurrent = root1->GetKey() == root2->GetKey();
			if (bCurrent)
			{
				bool bLeft = VerifyEqual(root1->left, root2->left);
				if (bLeft)
					return VerifyEqual(root1->right, root2->right);
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
	{
		if (root2 == NULL)
			return true;
		else
			return false;
	}
}


int main_BinaryTreeMirror()
{
	int test1[] = { 40, 100, 400, 150, 50, 300, 600 };
	int test2[] = { 40, 100, 400, 150, 50, 300, 600 };
	TreeCell* tree1(NULL), * tree2(NULL), *new_cell;

	for (auto& num : test1)
	{
		new_cell = new TreeCell(num);

		tree1 = Add(tree1, new_cell);
	}
	Print(tree1, "After adding 1");

	for (auto& num : test2)
	{
		new_cell = new TreeCell(num);

		tree2 = Add(tree2, new_cell);
	}
	Print(tree2, "After adding 2");

	Swap(tree1);
	Print(tree1, "After swap");

	if (VerifyEqual(tree1, tree2))
		std::cout << "Equal!\n";
	else
		std::cout << "Not Equal!\n";

	Clear(tree1);
	Clear(tree2);
	return 0;
}