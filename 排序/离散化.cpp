/*
    离散化：O(nlogn)
    查询：O(logn)
*/

#include <bits/stdc++.h>
using namespace std;
const int N = 1005;

int a[N], b[N];
int n, m;

void discrete() {
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i++)
        if(i == 1 || a[i] != a[i - 1])
            b[++m] = a[i];
}

int query(int x) {
    return lower_bound(b + 1, b + m + 1, x) - b;
}