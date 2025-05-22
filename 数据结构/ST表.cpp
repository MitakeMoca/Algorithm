/*
    可以用来求解 RMQ 问题
    f[i][j] 表示区间 [i, i + 2^j - 1] 里的最大值
    预处理：O(nlogn)
    查询：O(1)
*/

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int a[N], f[N][30], n;

void ST_init() {
    for(int i = 1; i <= n; i++)
        f[i][0] = a[0];
    int t = log(n) / log(2) + 1;
    for(int j = 1; j < t; j++)
        for(int i = 1; i <= n - (1 << j) + 1; i++)
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
}

int ST_query(int l, int r) {
    int k = log(r - l + 1) / log(2);
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}