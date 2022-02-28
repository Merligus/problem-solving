#include <iostream>
#include <vector>
#include "../lib/BinaryTree.hpp"


// O(n)
std::vector<int> HasPath(TreeCell* root, std::vector<int> path, int sum)
{
	std::vector<int> out;
	if (root != NULL)
	{
		// O(1)
		path.push_back(root->GetKey());
		// O(1)
		if (sum - root->GetKey() == 0)
			return path;
		else
			sum -= root->GetKey();
		if (root->left != NULL)
		{
			// O(n') n'= nodes in tree root->left
			out = HasPath(root->left, path, sum);
			if (!out.empty())
				return out;
		}

		if (root->right != NULL)
		{
			// O(n') n'= nodes in tree root->right
			out = HasPath(root->right, path, sum);
			if (!out.empty())
				return out;
		}
		return out;
	}
	else
		return out;
}

int main_PathSum()
{
	int test[] = { 5, 4, 8, 11, 0, 13, 4, 7, 2, 0, 0, 0, 0, 0, 1 };
	std::vector<int> out;
	Tree tree;

	for (auto& integer : test)
		tree.Add(integer);

	tree.Print("Fim Add");

	out = HasPath(tree.Root(), out, 18);
	if (out.empty())
		std::cout << "No path";
	else
		for (auto& integer : out)
			std::cout << integer << " ";
	std::cout << "\n";

	return 0;
}
