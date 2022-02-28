#include "BinaryTree.hpp"

TreeCell::TreeCell(int k)
{
	parent = NULL;
	left = NULL;
	right = NULL;
	SetHeight(1);
	SetKey(k);
}

void TreeCell::SetKey(int k)
{
	key = k;
}

int TreeCell::GetKey()
{
	return key;
}

void TreeCell::SetHeight(int h)
{
	height = h;
}

int TreeCell::GetHeight()
{
	return height;
}

// **************************************
// **************************************
// **************************************
// **************************************
// **************************************
// **************************************

Tree::Tree()
{
	_root = NULL;
}

Tree::~Tree()
{
	Clear();
}

void Tree::Print(std::string s)
{
	TreeCell* left, * right, * current;
	std::queue<TreeCell*> queue;
	queue.push(_root);
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

void Tree::Clear()
{
	TreeCell* left, * right, * current;
	std::queue<TreeCell*> queue;
	queue.push(_root);
	while (!queue.empty())
	{
		current = queue.front();
		left = current->left;
		right = current->right;
		// std::cout << current->GetKey() << " ";
		delete current;
		if (left != NULL)
			queue.push(left);
		if (right != NULL)
			queue.push(right);
		queue.pop();
	}
	// std::cout << "\n";
}

void Tree::Add(int num)
{
	TreeCell* current, * new_cell;
	std::pair<TreeCell*, TreeCell*> son_parent;
	std::queue<std::pair<TreeCell*, TreeCell*>> queue;

	new_cell = new TreeCell(num);
	if (_root == NULL)
		_root = new_cell;
	else
	{
		queue.push({ _root, NULL });

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
}

TreeCell* Tree::Root()
{
	return _root;
}

int Tree::GetHeight(TreeCell* cell)
{
	if (cell == NULL)
		return 0;
	return cell->GetHeight();
}

int Tree::GetBalance(TreeCell* cell)
{
	if (cell == NULL)
		return 0;
	return GetHeight(cell->left) - GetHeight(cell->right);
}

// O(lgn)
void Tree::AddAVL(int num)
{
	TreeCell* previous, * current, * new_cell;
	new_cell = new TreeCell(num);

	previous = NULL;
	current = _root;
	// O(lgn)
	while (current != NULL)
	{
		previous = current;
		if (num < current->GetKey())
			current = current->left;
		else
			current = current->right;
	}
	new_cell->parent = previous;
	if (previous == NULL)
		_root = new_cell;
	else
	{
		if (num < previous->GetKey())
			previous->left = new_cell;
		else
			previous->right = new_cell;
		previous->SetHeight(1 + std::max(GetHeight(previous->left), GetHeight(previous->right)));
	}
	new_cell->left = new_cell->right = NULL;
	// O(lgn)
	Balance(previous, num);
}

// O(lgn)
void Tree::Balance(TreeCell* cell, int num)
{
	TreeCell* p;

	// O(lgn)
	while (GetBalance(cell) != 0)
	{
		p = cell->parent;
		if (p != NULL)
		{
			p->SetHeight(1 + std::max(GetHeight(p->left), GetHeight(p->right)));

			if (GetBalance(p) > 1)
			{
				if (cell->GetKey() <= num)
					cell = LeftRotate(cell); // O(1)
				p = RightRotate(p); // O(1)
			}
			else if (GetBalance(p) < -1)
			{
				if (cell->GetKey() > num)
					cell = RightRotate(cell); // O(1)
				p = LeftRotate(p); // O(1)
			}
		}
		cell = cell->parent;
	}
}

// O(1)
TreeCell* Tree::LeftRotate(TreeCell* cell)
{
	TreeCell* aux;
	aux = cell->right;
	cell->right = aux->left;
	if (aux->left != NULL)
		aux->left->parent = cell;
	aux->parent = cell->parent;
	if (cell->parent == NULL)
		_root = aux;
	else if (cell == cell->parent->left)
		cell->parent->left = aux;
	else
		cell->parent->right = aux;
	aux->left = cell;
	cell->parent = aux;

	cell->SetHeight(1 + std::max(GetHeight(cell->left), GetHeight(cell->right)));
	aux->SetHeight(1 + std::max(GetHeight(aux->left), GetHeight(aux->right)));
	return aux;
}

// O(1)
TreeCell* Tree::RightRotate(TreeCell* cell)
{
	TreeCell* aux;
	aux = cell->left;
	cell->left = aux->right;
	if (aux->right != NULL)
		aux->right->parent = cell;
	aux->parent = cell->parent;
	if (cell->parent == NULL)
		_root = aux;
	else if (cell == cell->parent->right)
		cell->parent->right = aux;
	else
		cell->parent->left = aux;
	aux->right = cell;
	cell->parent = aux;

	cell->SetHeight(1 + std::max(GetHeight(cell->left), GetHeight(cell->right)));
	aux->SetHeight(1 + std::max(GetHeight(aux->left), GetHeight(aux->right)));
	return aux;
}

// O(n)
void Tree::PreOrder(TreeCell* cell)
{
	if (cell != NULL)
	{
		std::cout << cell->GetKey() << " ";
		PreOrder(cell->left);
		PreOrder(cell->right);
	}
	if (cell == _root)
		std::cout << "\n";
}

// O(n)
void Tree::PostOrder(TreeCell* cell)
{
	if (cell != NULL)
	{
		PostOrder(cell->left);
		PostOrder(cell->right);
		cell->SetHeight(1 + std::max(GetHeight(cell->left), GetHeight(cell->right)));
		if (std::abs(GetBalance(cell)) >= 2)
			std::cout << "\n\n\nERROR\n\n\n";
		std::cout << cell->GetKey() << " ";
	}
	if (cell == _root)
		std::cout << "\n";
}