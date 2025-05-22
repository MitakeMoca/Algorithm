/*
    二维前缀和
    sum[i][j] 表示从 (1, 1) 到 (i, j) 这片矩形区域中所有数字之和
    初始化：O(n * m)
    查询 (i1, j1) 到 (i2, j2) 的前缀和：O(1)
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 3005;
int sum[N][N], a[N][N];

void init(int n, int m) {
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + a[i][j];
}

int getArea(int i1, int j1, int i2, int j2) {
	return sum[i2][j2] - sum[i1 - 1][j2] - sum[i2][j1 - 1] + sum[i1 - 1][j1 - 1];
}