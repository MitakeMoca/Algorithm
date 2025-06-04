#include <bits/stdc++.h>
using namespace std;

long long c[300005] = {0};
long long t[300005] = {0};
long long f[300005] = {0};

struct Point{
	long long x, y;
}pt[300005], q[300005];

inline Point operator - (Point a, Point b)
{
	return Point(a.x - b.x, a.y - b.y);
}

inline long long operator & (Point a, Point b)
{
	return a.x * b.y - a.y * b.x;
}

int find(int l, int r, int i)
{
	int mid, ans = r;
	while(l <= r){
		mid = l + r >> 1;
		if(pt[mid + 1].y - pt[mid].y > t[i] * (pt[mid + 1].x - pt[mid].x)){
			r = mid - 1, ans = mid;
		}
		else l = mid + 1;
	}
	return ans;
}

int main()
{
	int n, s;
	cin >> n >> s;

	for(int i = 1; i <= n; i++){
		cin >> t[i] >> c[i];
	}

	for(int i = 1; i <= n; i++) t[i] += t[i - 1], c[i] += c[i - 1];

	int l = 0, r = 1;
	for(int i = 1; i <= n; i++){
		int m = find(l, r - 1, i);
		f[i] = pt[m].y - t[i] * pt[m].x + t[i] * c[i] + s * c[n];
		Point tmp = {c[i], f[i] - s * c[i]};
		while(l + 1 < r && (pt[r - 1] - pt[r - 2] & tmp - pt[r - 1]) <= 0) r--;
		pt[r++] = tmp;
	}

	cout << f[n];
	return 0;
}