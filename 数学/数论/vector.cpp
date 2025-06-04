#include <bits/stdc++.h>
using namespace std;

struct Point{
	double x, y;
};

inline Point operator + (const Point a, const Point b)
{
	return Point(a.x + b.x, a.y + b.y);
}

inline Point operator - (const Point a, const Point b)
{
	return Point(a.x - b.x, a.y - b.y);
}

inline Point operator * (const double t, const Point a)
{
	return Point(t * a.x, t * a.y);
}

inline double operator & (const Point a, const Point b)
{
	return a.x * b.y - a.y * b.x;
}

inline double operator * (const Point a, const Point b)
{
	return a.x * b.x + a.y * b.y;
}

inline double len(Point a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}

inline double angle(Point a, Point b)
{
	return acos(a * b / len(a) / len(b));
}

inline Point getNode(Point a, Point u, Point b, Point v)
{
	double t = ((a - b) & v) / (v & u);
	return a + t * u;
}

inline rotate(Point a, double b)
{
	return Point(a.x * cos(b) - a.y * sin(b), a.x * sin(b) + a.y * cos(b));
}

int main()
{
	Point a, b;
	cin >> a.x >> a.y >> b.x >> b.y;

	cout << a * b << endl << (a & b);
	return 0;
}