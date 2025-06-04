#include <bits/stdc++.h>
using namespace std;

#define eps 1e-6

struct Point{
	double x, y;
}p[505];

struct Line{
	Point s, e;
}A[505], q[505];

int cnt = 0;

inline Point operator - (Point a, Point b)
{
	return Point(a.x - b.x, a.y - b.y);
}

inline double operator & (Point a, Point b)
{
	return a.x * b.y - a.y * b.x;
}

inline Point operator + (Point a, Point b)
{
	return Point(a.x + b.x, a.y + b.y);
}

inline Point operator * (double t, Point a)
{
	return Point(t * a.x, t * a.y);
}

double angle(Line a)
{
	return atan2((a.e.y - a.s.y), (a.e.x - a.s.x));
}

bool cmp(Line a, Line b)
{
	double A = angle(a), B = angle(b);
	return fabs(A - B) > eps ? A < B : ((a.e - a.s) & (b.e - a.s)) < 0;
}

Point cross(Line a, Line b)
{
	Point u = a.e - a.s, v = b.e - b.s;
	double t = ((a.s - b.s) & v) / (v & u);
	return a.s + t * u;
}

bool right(Line a, Line b, Line c)
{
	Point p = cross(b, c);
	return ((a.e - a.s) & (p - a.s)) < 0;
}

void halfPlan(int n);

int main()
{
	int n, m;
	cin >> n;

	while(n--){
		cin >> m;
		for(int i = 0; i < m; i++) cin >> p[i].x >> p[i].y;
		for(int i = 0; i < m - 1; i++) A[cnt++] = {p[i], p[i + 1]};
		A[cnt++] = {p[m - 1], p[0]};
	}

	halfPlan(cnt);
	return 0;
}

void halfPlan(int n)
{
	sort(A, A + n, cmp);

	int l = 0, r = 0;
	q[0] = A[0];

	for(int i = 1; i < n; i++){
		if(fabs(angle(A[i]) - angle(A[i - 1])) < eps) continue;
		while(l < r && right(A[i], q[r], q[r - 1])) r--;
		while(l < r && right(A[i], q[l], q[l + 1])) l++;
		q[++r] = A[i];
	}
	while(l < r && right(q[l], q[r], q[r - 1])) r--;
	q[++r] = q[l];

	int sz = 0;
	for(int i = l; i < r; i++){
		p[sz++] = cross(q[i], q[i + 1]);
	}

	double ans = 0;
	for(int i = 1; i < sz - 1; i++){
		ans += ((p[i] - p[0]) & p[i + 1] - p[0]);
	}

	printf("%.3f", ans / 2);
}