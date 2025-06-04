#include <bits/stdc++.h>
using namespace std;

struct Point{
	double x, y;
}stk[100005], pt[100005];

inline double operator & (Point a, Point b)
{
	return a.x * b.y - a.y * b.x;
}

inline Point operator - (Point a, Point b)
{
	return Point(a.x - b.x, a.y - b.y);
}

double Andrew(int n);
double dis(Point a, Point b);

int main()
{
	int n;
	cin >> n;

	for(int i = 0; i < n; i++){
		cin >> pt[i].x >> pt[i].y;
	}

	printf("%.2f", Andrew(n));
	return 0;
}

double Andrew(int n)
{
	sort(pt, pt + n, [&](Point a, Point b){
		return a.x != b.x ? a.x < b.x : a.y < b.y;
	});

	int top = 0;
	for(int i = 0; i < n; i++){
		while(top > 1 && ((stk[top - 1] - stk[top - 2]) & (pt[i] - stk[top - 2])) <= 0) top--;
		stk[top++] = pt[i];
	}

	int t = top;
	for(int i = n - 2; i >= 0; i--){
		while(top > t && ((stk[top - 1] - stk[top - 2]) & (pt[i] - stk[top - 2])) <= 0) top--;
		stk[top++] = pt[i];
	}

	double ans = 0;
	for(int i = 1; i < top; i++){
		ans += dis(stk[i], stk[i - 1]);
	}
	return ans;
}
double dis(Point a, Point b)
{
	double tmp = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	return sqrt(tmp);
}