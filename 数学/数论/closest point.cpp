#include <bits/stdc++.h>
using namespace std;

struct Point{
	double x, y;
}A[200005], B[200005];

bool cmp(Point a, Point b);
double divide(int l, int r);
double dis(Point a, Point b);

int main()
{
	int n;
	cin >> n;

	for(int i = 0; i < n; i++){
		cin >> A[i].x >> A[i].y;
	}

	sort(A, A + n, cmp);

	printf("%.4f", divide(0, n - 1));
	return 0;
}

bool cmp(Point a, Point b)
{
	return a.x != b.x ? a.x < b.x : a.y < b.y;
}

double divide(int l, int r)
{
	if(l == r) return 2e9;

	int mid = l + r >> 1;
	Point tmp = A[mid];
	double d = min(divide(l, mid), divide(mid + 1, r));
	

	int i = l, j = mid + 1, k = 0;
	while(i <= mid && j <= r){
		if(A[i].y <= A[j].y) B[k++] = A[i++];
		else B[k++] = A[j++];
	}
	while(i <= mid) B[k++] = A[i++];
	while(j <= r) B[k++] = A[j++];
	for(int i = l, t = 0; i <= r; i++, t++) A[i] = B[t];

	k = 0;
	for(int i = l; i <= r; i++){
		if(fabs(tmp.x - A[i].x) < d) B[k++] = A[i];
	}

	for(int i = 0; i < k; i++){
		for(j = i + 1; j < k && B[j].y - B[i].y < d; j++){
			d = min(d, dis(B[i], B[j]));
		}
	}

	return d;
}

double dis(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}