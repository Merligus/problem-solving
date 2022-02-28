#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <algorithm>

#define PI 3.14159265

struct Point
{
	double x, y;
	double angle;

	bool operator<(const Point& phs)
	{
		if (this->angle == phs.angle)
		{
			if (this->y == phs.y)
				return this->x < phs.x;
			else
				return this->y < phs.y;
		}
		else
			return this->angle < phs.angle;
	}

	bool operator>(const Point& phs)
	{
		return this->angle > phs.angle;
	}

	bool operator==(const Point& phs)
	{
		return this->angle == phs.angle;
	}
};


double Norm(Point vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

double CalculateAngle(Point p0, Point p1, Point p2)
{
	Point vec_20, vec_10;
	vec_20.x = p2.x - p0.x;
	vec_20.y = p2.y - p0.y;
	vec_10.x = p1.x - p0.x;
	vec_10.y = p1.y - p0.y;

	return acos((vec_10.x * vec_20.x + vec_10.y * vec_20.y) / (Norm(vec_20) * Norm(vec_10))) * 180.0 / PI;
}

double Direction(Point p0, Point p1, Point p2)
{
	Point vec_20, vec_10;
	vec_20.x = p2.x - p0.x;
	vec_20.y = p2.y - p0.y;
	vec_10.x = p1.x - p0.x;
	vec_10.y = p1.y - p0.y;

	return vec_10.x * vec_20.y - vec_10.y * vec_20.x;
}

double Distance(Point pf, Point p0)
{
	return sqrt( pow<double>(pf.x - p0.x, 2.0) + pow<double>(pf.y - p0.y, 2.0));
}

std::vector<Point> GrahamScan_ConvexHull(std::vector<Point> Q)
{
	Point p0;
	int minIndex(0);
	for (int index = 1; index < Q.size(); index++)
	{
		if (Q[index].y < Q[minIndex].y)
			minIndex = index;
		else if (Q[index].y == Q[minIndex].y)
			if (Q[index].x < Q[minIndex].x)
				minIndex = index;
	}

	p0 = Q[minIndex];
	Point pAux(p0);
	pAux.x += 1;
	for (Point& p : Q)
		if (p.x != p0.x && p.y != p0.y)
			p.angle = CalculateAngle(p0, p, pAux);

	// O(nlgn)
	std::sort(Q.begin(), Q.end());
	std::list<Point> Points;
	Points.push_back(Q[1]);
	for (int index = 2; index < Q.size(); index++)
	{
		if (Q[index].angle == Points.back().angle)
		{
			if (Distance(Q[index], p0) > Distance(Points.back(), p0))
				Points.back() = Q[index];
		}
		else
			Points.push_back(Q[index]);
	}

	std::vector<Point> S;
	S.push_back(p0);
	S.push_back(Points.front());
	Points.pop_front();
	S.push_back(Points.front());
	Points.pop_front();

	for (Point& p : Points)
	{
		Point top = S.back();
		Point nextTop = S[S.size() - 2];
		// std::cout << "Analyze p: " << p.x << "," << p.y << "\n";
		// std::cout << "\t" << top.x << "," << top.y << " - " << nextTop.x << "," << nextTop.y << "\n";
		while (Direction(nextTop, top, p) < 0)
		{
			S.pop_back();
			top = S.back();
			nextTop = S[S.size() - 2];
			// std::cout << "\t" << top.x << "," << top.y << " - " << nextTop.x << "," << nextTop.y << "\n";
		}
		S.push_back(p);
	}

	return S;
}

int main_ConvexHull()
{
	std::pair<int, int> Ps[] = { {3, 2}, {16, 4}, {16, 5}, {19, 7}, {16, 7}, {15, 8}, {12, 9}, {10, 8}, {8, 6}, {6, 8}, {5, 14}, {4, 8}, {1, 6} };
	std::vector<Point> Q, CH;

	for (int index = 0; index < 13; index++)
	{
		Point point;
		point.x = Ps[index].first;
		point.y = Ps[index].second;
		point.angle = -1.0;
		Q.push_back(point);
	}


	for (int y = 14; y >= 0; y--)
	{
		std::cout << y << "\t";
		for (int x = 0; x <= 19; x++)
		{
			bool found = false;
			for (int index = 0; index < Q.size(); index++)
				if (Q[index].x == x && Q[index].y == y)
				{
					std::cout << index << " \t";
					found = true;
					break;
				}
			if (!found)
				std::cout << "   \t";
		}
		std::cout << "\n";
	}
	std::cout << "\t";
	for (int x = 0; x <= 19; x++)
		std::cout << x << "\t";
	std::cout << "\n";

	CH = GrahamScan_ConvexHull(Q);
	for (Point& p : CH)
		std::cout << p.x << " " << p.y << '\n';

	return 0;
}