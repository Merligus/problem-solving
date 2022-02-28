#include <iostream>
#include <vector>
#include <list>

class Rectangle
{
public:
	Rectangle(int ls, int le, int cs, int ce);

	bool Valid()
	{
		if (ls > le || cs > ce)
			return false;
		else
			return true;
	}

	void Print()
	{
		std::cout << ls << " " << le << " " << cs << " " << ce << std::endl;
	}

	int ls, le, cs, ce;
	int area;
};

Rectangle::Rectangle(int ls, int le, int cs, int ce)
{
	this->ls = ls;
	this->le = le;
	this->cs = cs;
	this->ce = ce;
	area = (le - ls + 1) * (ce - cs + 1);
}

int MaxRectangle(std::vector<std::vector<int>>& A)
{
	std::vector<std::list<Rectangle>> ones;

	for (int i = 0; i < A.size(); i++)
	{
		std::list<Rectangle> ones_l;
		bool during(false);
		int start_c;
		for (int j = 0; j < A[i].size(); j++)
		{
			if (during)
			{
				if (A[i][j] == 0)
				{
					during = false;
					Rectangle r(i, i, start_c, j - 1);
					ones_l.push_back(r);
				}
			}
			else
			{
				if (A[i][j] == 1)
				{
					during = true;
					start_c = j;
				}
			}
		}
		if (during)
		{
			Rectangle r(i, i, start_c, A[i].size() - 1);
			ones_l.push_back(r);
		}
		during = false;
		ones.push_back(ones_l);
	}

	Rectangle best(0, 0, 0, 0);
	Rectangle default_r(0, 0, 0, A[0].size() - 1);
	Rectangle holded(0, 0, 0, 0);
	std::list<Rectangle> hold, hold_aux;
	best.area = 0;

	for (int i = 0; i < ones.size(); i++)
	{
		std::list<Rectangle> o = ones[i];
		default_r.ls = i;
		hold.push_back(default_r);
		hold_aux.clear();
		while (!hold.empty())
		{
			holded = hold.front();
			hold.pop_front();
			// holded.Print();
			for (auto& next : o)
			{
				Rectangle aux(holded.ls, next.le, std::max(holded.cs, next.cs), std::min(holded.ce, next.ce));
				if (aux.Valid())
				{
					if (aux.area > best.area)
						best = aux;
					hold_aux.push_back(aux);
				}
			}
		}
		hold.swap(hold_aux);
		// std::cout << "************************ Holded:\n";
		// for (auto& h : hold)
		// 	h.Print();
		// std::cout << "************************\n";
	}

	return best.area;
}

int maximalRectangle(std::vector<std::vector<int>>& A)
{
	return MaxRectangle(A);
}

int main_MaxRectangle()
{
//3 3 
//0 0 1
//1 0 0
//0 1 0
	int l, c;

	while (true)
	{
		std::cin >> l >> c;
		std::vector<int> aux(c, 0);
		std::vector<std::vector<int>> A(l, aux);

		for (int i = 0; i < l; i++)
			for (int j = 0; j < c; j++)
				std::cin >> A[i][j];

		std::cout << maximalRectangle(A) << std::endl;

		for (int i = 0; i < l; i++)
		{
			for (int j = 0; j < c; j++)
				std::cout << A[i][j] << " ";
			std::cout << std::endl;
		}
	}

	return 0;
}