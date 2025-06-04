#include <bits/stdc++.h>
using namespace std;

#define N 4000005
const double PI = 3.141592653589793238;

typedef struct{
	double r, v;
}Point;


Point A[N], B[N], C[N];
int R[N] = {0};

inline Point operator + (const Point &a, const Point &b)
{
	return {a.r + b.r, a.v + b.v};
}

inline Point operator - (const Point &a, const Point &b)
{
	return {a.r - b.r, a.v - b.v};
}

inline Point operator * (const Point &a, const Point &b)
{
	return {a.r * b.r - a.v * b.v, a.r * b.v + a.v * b.r};
}

void FFT(Point* A, int n, int op);
void change(int n);

int main()
{
	int n, m;
	cin >> n >> m;

	for(int i = 0; i <= n; i++) scanf("%lf", &A[i].r);
	for(int i = 0; i <= m; i++) scanf("%lf", &B[i].r);
	for(m = n + m, n = 1; n <= m; n <<= 1);

	change(n);
	FFT(A, n, 1);
	FFT(B, n, 1);
	for(int i = 0; i < n; i++) C[i] = A[i] * B[i];
	FFT(C, n, -1);

	for(int i = 0; i <= m; i++) printf("%d ", (int)(C[i].r / n + 0.5));
	return 0;
}

void FFT(Point* A, int n, int op)
{
	for(int i = 0; i < n; i++){
		if(i < R[i]) swap(A[i], A[R[i]]);
	}

	for(int k = 2; k <= n; k <<= 1){
		Point w1 = {cos(2.0 * PI / k),  sin(2.0 * PI / k) * op};
		for(int i = 0; i < n; i += k){
			Point wk = {1, 0};
			for(int j = 0; j < k / 2; j++){
				Point x = A[i + j], y = A[i + j + k / 2] * wk;
				A[i + j] = x + y;
				A[i + j + k / 2] = x - y;
				wk = wk * w1;
			}
		}
	}
}

void change(int n)
{
	for(int i = 0; i < n; i++){
		R[i] = ((R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0));
	}
}