#include <bits/stdc++.h>
using namespace std;

struct Point{
	long long x, y;
	bool operator < (const Point &th) const
	{
		return x != th.x ? x < th.x : y < th.y;
	}
}stk[50005], pt[50005];
int top = 0;

inline long long operator & (Point a, Point b)
{
	return a.x * b.y - a.y * b.x;
}

inline Point operator - (Point a, Point b)
{
	return Point(a.x - b.x, a.y - b.y);
}

inline long long dis(Point a, Point b)
{
	return (a.x - b. x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void Andrew(int n);
void rotatingCaliper(int n);

int main()
{
	int n;
	cin >> n;

	for(int i = 0; i < n; i++){
		cin >> pt[i].x >> pt[i].y;
	}

	Andrew(n);
	rotatingCaliper(top - 1);
	return 0;
}

void Andrew(int n)
{
	sort(pt, pt + n);

	for(int i = 0; i < n; i++){
		while(top > 1 && ((stk[top - 1] - stk[top - 2]) & (pt[i] - stk[top - 2])) <= 0) top--;
		stk[top++] = pt[i];
	}

	int t = top;
	for(int i = n - 2; i >= 0; i--){
		while(top > t && ((stk[top - 1] - stk[top - 2]) & (pt[i] - stk[top - 2])) <= 0) top--;
		stk[top++] = pt[i];
	}
}

void rotatingCaliper(int n)
{
	long long ans = 0;
	for(int i = 0, j = 1; i < n; i++){
		while(((stk[i + 1] - stk[i]) & (stk[j] - stk[i])) < ((stk[i + 1] - stk[i]) & (stk[j + 1] - stk[i]))) j = (j + 1) % n;
		ans = max(ans, max(dis(stk[j], stk[i]), dis(stk[j], stk[i + 1])));
	}
	cout << ans;
}