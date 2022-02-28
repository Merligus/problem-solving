#pragma once
#include <iostream>
#include <cmath>
#include <queue>

class TreeCell
{
public:
	TreeCell* parent;
	TreeCell* left;
	TreeCell* right;

	TreeCell(int k);
	void SetKey(int k);
	int GetKey();
	void SetHeight(int h);
	int GetHeight();

private:
	int height;
	int key;
};


class Tree
{
public:
	Tree();
	~Tree();

	// BINARY TREE
	void Print(std::string s);
	void Add(int num);
	void Clear();
	TreeCell* Root();

	// BALANCED TREE
	int GetHeight(TreeCell* cell);
	int GetBalance(TreeCell* cell);
	void AddAVL(int num);
	void Balance(TreeCell* cell, int num);
	TreeCell* LeftRotate(TreeCell* cell);
	TreeCell* RightRotate(TreeCell* cell);

	// DEBUG
	void PreOrder(TreeCell* cell);
	void PostOrder(TreeCell* cell);

private:
	TreeCell* _root;
};
